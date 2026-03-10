#pragma once

UENUM(BlueprintType)
enum EItemType : uint8
{
	None
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
	EItemType Type;
	
	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	int MaxStack;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
};

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FName ItemId;
	
	UPROPERTY(EditAnywhere)
	int Amount;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	bool bOccupied;
	
	UPROPERTY(EditAnywhere)
	FItemInstance Item;
};