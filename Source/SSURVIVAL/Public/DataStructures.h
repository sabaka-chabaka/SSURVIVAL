// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.generated.h"

UENUM(BlueprintType)
enum EItemType : uint8
{
	IT_None    UMETA(DisplayName="None"),
	IT_Weapon  UMETA(DisplayName="Weapon"),
	IT_Ammo    UMETA(DisplayName="Ammo"),
	IT_Medical UMETA(DisplayName="Medical"),
	IT_Resource UMETA(DisplayName="Resource")
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Id;

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemType> Type = IT_None;

	UPROPERTY(EditAnywhere)
	float Weight = 0.f;

	UPROPERTY(EditAnywhere)
	int MaxStack = 1;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;
};

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName ItemId;

	UPROPERTY(EditAnywhere)
	int Amount = 0;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bOccupied = false;

	UPROPERTY(EditAnywhere)
	FItemInstance Item;
};