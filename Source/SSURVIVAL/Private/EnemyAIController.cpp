// 2026 sabaka-chabaka

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BehaviorTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("[EnemyAIC] BehaviorTree не назначен!"));
		return;
	}

	if (UseBlackboard(BehaviorTree->BlackboardAsset, BB))
	{
		RunBehaviorTree(BehaviorTree);
	}

	UpdatePerception();
}

void AEnemyAIController::OnUnPossess()
{
	GetWorldTimerManager().ClearTimer(PerceptionTimerHandle);
	Super::OnUnPossess();
}

void AEnemyAIController::UpdatePerception()
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetPawn());
	if (!Enemy || !BB) return;

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return;

	const FVector EnemyLoc  = Enemy->GetActorLocation();
	const FVector PlayerLoc = Player->GetActorLocation();
	const float   Distance  = FVector::Dist(EnemyLoc, PlayerLoc);

	bool bSees = false;
	if (Distance <= Enemy->DetectionRange)
	{
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Enemy);

		const bool bBlocked = GetWorld()->LineTraceSingleByChannel(
			Hit, EnemyLoc, PlayerLoc, ECC_Visibility, Params);

		bSees = !bBlocked || (Hit.GetActor() == Player);
	}

	BB->SetValueAsObject(EnemyBBKeys::TargetActor, bSees ? Player : nullptr);
	BB->SetValueAsBool(EnemyBBKeys::bCanSeeTarget, bSees);

	if (bSees)
	{
		BB->SetValueAsVector(EnemyBBKeys::LastKnownLocation, PlayerLoc);
	}

	BB->SetValueAsBool(EnemyBBKeys::bIsInMeleeRange,  Distance <= Enemy->MeleeRange);
	BB->SetValueAsBool(EnemyBBKeys::bIsInAttackRange, Distance <= Enemy->AttackRange);
}