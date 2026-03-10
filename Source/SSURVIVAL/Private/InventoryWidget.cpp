// 2026 sabaka-chabaka

#include "InventoryWidget.h"

#include "InventoryComponent.h"
#include "SSCharacter.h"

void UInventoryWidget::InitInventory(UInventoryComponent* InInventory, ASSCharacter* InCharacter)
{
	InventoryComponent = InInventory;
	Character = InCharacter;

	if (InventoryComponent)
	{
		InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryWidget::OnInventoryChanged);
	}

	RefreshUI();
}

void UInventoryWidget::OnSlotClicked(FName ItemId)
{
	if (!InventoryComponent || !Character) return;

	const FItemData* Data = InventoryComponent->GetItemData(ItemId);
	if (!Data) return;

	if (Data->Type == IT_Weapon)
	{
		Character->EquipWeapon(ItemId);
	}
}

TArray<FInventorySlot> UInventoryWidget::GetSlots() const
{
	if (!InventoryComponent) return {};
	return InventoryComponent->GetOccupiedSlots();
}

bool UInventoryWidget::GetItemData(FName ItemId, FItemData& OutData) const
{
	if (!InventoryComponent) return false;

	const FItemData* Data = InventoryComponent->GetItemData(ItemId);
	if (!Data) return false;

	OutData = *Data;
	return true;
}

void UInventoryWidget::OnInventoryChanged()
{
	RefreshUI();
}

void UInventoryWidget::NativeDestruct()
{
	if (InventoryComponent)
	{
		InventoryComponent->OnInventoryChanged.RemoveDynamic(this, &UInventoryWidget::OnInventoryChanged);
	}

	Super::NativeDestruct();
}