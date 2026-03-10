// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataStructures.h"
#include "InventoryWidget.generated.h"

UCLASS()
class SSURVIVAL_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void InitInventory(class UInventoryComponent* InInventory, class ASSCharacter* InCharacter);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void OnSlotClicked(FName ItemId);

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void RefreshUI();

	UFUNCTION(BlueprintPure, Category="Inventory")
	TArray<FInventorySlot> GetSlots() const;

	UFUNCTION(BlueprintPure, Category="Inventory")
	bool GetItemData(FName ItemId, FItemData& OutData) const;

protected:
	virtual void NativeDestruct() override;

	UPROPERTY()
	class UInventoryComponent* InventoryComponent = nullptr;

	UPROPERTY()
	class ASSCharacter* Character = nullptr;

private:
	UFUNCTION()
	void OnInventoryChanged();
};
