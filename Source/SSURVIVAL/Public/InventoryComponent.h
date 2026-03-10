// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SSURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	int MaxSlots = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TMap<FName, FItemData> ItemDatabase;

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryChanged OnInventoryChanged;

	bool AddItem(const FItemInstance& Item);
	bool RemoveItem(FName Id, int32 Amount);
	bool GetItem(FName Id, FItemInstance& OutItem) const;
	int32 GetItemAmount(FName Id) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<FInventorySlot> GetOccupiedSlots() const;

	const FItemData* GetItemData(FName Id) const;

protected:
	UPROPERTY()
	TArray<FInventorySlot> Slots;
};