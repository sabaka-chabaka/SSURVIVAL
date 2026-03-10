// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "WorldItem.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM()
enum EWeaponType : uint8
{
	Rifle,
	Pistol,
	Bow,
	Shotgun,
	Unknown
};

UCLASS()
class SSURVIVAL_API AWeapon : public AWorldItem
{
	GENERATED_BODY()

public:
	AWeapon();
	
	void Fire(const FVector& Start, const FVector& Direction);
	void Reload();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;
	void DrawTracer(const FVector& End) const;

public:
	UPROPERTY(EditAnywhere)
	float Damage;
	
	UPROPERTY(EditAnywhere)
	float Range;
	
	UPROPERTY(EditAnywhere)
	int Ammo;
	
	UPROPERTY(EditAnywhere)
	int ReserveAmmo;
	
	UPROPERTY(EditAnywhere)
	int MaxAmmo;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EWeaponType> WeaponType;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDamageType> DamageType;
	
	UPROPERTY(EditAnywhere)
	FName SocketName;
};