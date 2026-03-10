// 2026 sabaka-chabaka

#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Slots.SetNum(MaxSlots);
}

bool UInventoryComponent::AddItem(const FItemInstance& Item)
{
	const FItemData* Data = ItemDatabase.Find(Item.ItemId);
	if (!Data) return false;

	int32 Remaining = Item.Amount;

	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied && Slot.Item.ItemId == Item.ItemId)
		{
			int32 Space = Data->MaxStack - Slot.Item.Amount;
			if (Space > 0)
			{
				int32 ToAdd = FMath::Min(Space, Remaining);
				Slot.Item.Amount += ToAdd;
				Remaining -= ToAdd;
				if (Remaining <= 0)
				{
					OnInventoryChanged.Broadcast();
					return true;
				}
			}
		}
	}

	for (FInventorySlot& Slot : Slots)
	{
		if (!Slot.bOccupied)
		{
			int32 ToAdd = FMath::Min(Data->MaxStack, Remaining);
			Slot.bOccupied = true;
			Slot.Item.ItemId = Item.ItemId;
			Slot.Item.Amount = ToAdd;
			Remaining -= ToAdd;
			if (Remaining <= 0)
			{
				OnInventoryChanged.Broadcast();
				return true;
			}
		}
	}

	if (Remaining < Item.Amount)
		OnInventoryChanged.Broadcast();

	return false;
}

bool UInventoryComponent::RemoveItem(FName Id, int32 Amount)
{
	int32 Remaining = Amount;

	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied && Slot.Item.ItemId == Id)
		{
			if (Slot.Item.Amount > Remaining)
			{
				Slot.Item.Amount -= Remaining;
				Remaining = 0;
				break;
			}
			else
			{
				Remaining -= Slot.Item.Amount;
				Slot.bOccupied = false;
				Slot.Item = FItemInstance();
			}
		}
	}

	const bool bSuccess = Remaining <= 0;
	if (bSuccess)
		OnInventoryChanged.Broadcast();

	return bSuccess;
}

bool UInventoryComponent::GetItem(FName Id, FItemInstance& OutItem) const
{
	for (const FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied && Slot.Item.ItemId == Id)
		{
			OutItem = Slot.Item;
			return true;
		}
	}
	return false;
}

int32 UInventoryComponent::GetItemAmount(FName Id) const
{
	int32 Total = 0;
	for (const FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied && Slot.Item.ItemId == Id)
			Total += Slot.Item.Amount;
	}
	return Total;
}

TArray<FInventorySlot> UInventoryComponent::GetOccupiedSlots() const
{
	TArray<FInventorySlot> Result;
	for (const FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied)
			Result.Add(Slot);
	}
	return Result;
}

const FItemData* UInventoryComponent::GetItemData(FName Id) const
{
	return ItemDatabase.Find(Id);
}