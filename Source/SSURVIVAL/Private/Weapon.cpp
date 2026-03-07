// 2026 sabaka-chabaka

#include "Weapon.h"

#include "SSCharacter.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Fire(const FVector& Start, const FVector& Direction)
{
	if (Ammo <= 0) return;
	
	Ammo--;
	
	FHitResult Hit;
	
	GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + Direction * Range, ECC_Visibility);
	
	if (Hit.GetActor())
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, nullptr, this, DamageType);
	}
}

void AWeapon::Reload()
{
	if (Ammo == MaxAmmo) return;
	
	if (ReserveAmmo <= 0) return;
	
	int NewAmmo = FMath::Min(ReserveAmmo, MaxAmmo - Ammo);
	
	ReserveAmmo -= NewAmmo;
	Ammo += NewAmmo;
	
	UE_LOG(LogTemp, Warning, TEXT("Reloaded: %d. Ammo: %d, Reserve: %d"), NewAmmo, Ammo, ReserveAmmo)
}

void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (ASSCharacter* SSChar = Cast<ASSCharacter>(OtherActor))
	{
		SSChar->PickupWeapon(this);
	}
}