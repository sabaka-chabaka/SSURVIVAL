// 2026 sabaka-chabaka

#include "EnemyCharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

bool AEnemyCharacter::CanAttack() const
{
	return (GetWorld()->GetTimeSeconds() - LastAttackTime) >= AttackCooldown;
}

void AEnemyCharacter::PerformMeleeAttack()
{
	if (!CanAttack()) return;
	LastAttackTime = GetWorld()->GetTimeSeconds();

	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(MeleeRadius);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->OverlapMultiByChannel(
		Overlaps,
		GetActorLocation(),
		FQuat::Identity,
		ECC_Pawn,
		Sphere,
		Params
	);

	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* Target = Overlap.GetActor();
		if (!Target) continue;

		UGameplayStatics::ApplyDamage(Target, MeleeDamage, GetController(), this, nullptr);
		UE_LOG(LogTemp, Log, TEXT("[Enemy] Melee hit: %s"), *Target->GetName());
	}
}

void AEnemyCharacter::PerformRangedAttack()
{
	if (!CanAttack()) return;
	if (!ProjectileClass) return;

	LastAttackTime = GetWorld()->GetTimeSeconds();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC || !PC->GetPawn()) return;

	const FVector Origin    = GetMesh()->GetSocketLocation("head");
	const FVector TargetLoc = PC->GetPawn()->GetActorLocation();
	const FRotator SpawnRot = (TargetLoc - Origin).Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner   = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, Origin, SpawnRot, SpawnParams);

	UE_LOG(LogTemp, Log, TEXT("[Enemy] Ranged attack fired"));
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	const float Actual = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health = FMath::Clamp(Health - Actual, 0.f, MaxHealth);

	UE_LOG(LogTemp, Log, TEXT("[Enemy] TakeDamage: %.1f  HP: %.1f/%.1f"), Actual, Health, MaxHealth);

	if (Health <= 0.f)
	{
		Die();
	}
	else
	{
		OnHit(Actual);
	}

	return Actual;
}

void AEnemyCharacter::Die()
{
	OnDeath(); 

	SetActorEnableCollision(false);
	if (AAIController* AIC = Cast<AAIController>(GetController()))
	{
		AIC->StopMovement();
		AIC->UnPossess();
	}

	SetLifeSpan(3.f);
}