// 2026 sabaka-chabaka

#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	WeaponType = Unknown;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::DrawTracer(const FVector& End) const
{
	const FVector Start = MeshComponent->GetSocketLocation("MuzzleFlashSocket");
	DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 0.1f, 0, 0.5f);
}

void AWeapon::Fire(const FVector& Start, const FVector& Direction)
{
	if (Ammo <= 0) return;
	Ammo--;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Direction * Range, ECC_Visibility);
	DrawTracer(Hit.bBlockingHit ? Hit.ImpactPoint : Start + Direction * Range);

	if (Hit.GetActor())
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, nullptr, this, DamageType);
	}
}

void AWeapon::Reload()
{
	if (Ammo == MaxAmmo || ReserveAmmo <= 0) return;

	int32 NewAmmo = FMath::Min(ReserveAmmo, MaxAmmo - Ammo);
	ReserveAmmo -= NewAmmo;
	Ammo += NewAmmo;

	UE_LOG(LogTemp, Log, TEXT("[Weapon] Reloaded +%d  |  Ammo: %d  |  Reserve: %d"), NewAmmo, Ammo, ReserveAmmo);
}
