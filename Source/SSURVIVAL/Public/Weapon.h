// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum EWeaponType : uint8
{
	Rifle   UMETA(DisplayName="Rifle"),
	Pistol  UMETA(DisplayName="Pistol"),
	Bow     UMETA(DisplayName="Bow"),
	Shotgun UMETA(DisplayName="Shotgun"),
	Unknown UMETA(DisplayName="Unknown")
};

UCLASS()
class SSURVIVAL_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	void Fire(const FVector& Start, const FVector& Direction);
	void Reload();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category="Weapon")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category="Weapon")
	float Range = 5000.f;

	UPROPERTY(EditAnywhere, Category="Weapon")
	int32 Ammo = 30;

	UPROPERTY(EditAnywhere, Category="Weapon")
	int32 ReserveAmmo = 90;

	UPROPERTY(EditAnywhere, Category="Weapon")
	int32 MaxAmmo = 30;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TEnumAsByte<EWeaponType> WeaponType = Unknown;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category="Weapon")
	FName SocketName = "WeaponSocket";

protected:
	virtual void BeginPlay() override;
	void DrawTracer(const FVector& End) const;
};