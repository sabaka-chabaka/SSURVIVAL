// 2026 sabaka-chabaka

#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Slots.SetNum(MaxSlots);
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
					return true;
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
				return true;
		}
	}

	return false;
}

bool UInventoryComponent::GetItem(FName Id, FItemInstance& OutItem)
{
	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied && Slot.Item.ItemId == Id)
		{
			OutItem = Slot.Item;
			return true;
		}
	}
	
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
				return true;
			}
			else
			{
				Remaining -= Slot.Item.Amount;
				Slot.bOccupied = false;
				Slot.Item = FItemInstance();

				if (Remaining <= 0)
					return true;
			}
		}
	}

	return Remaining <= 0;
}

int32 UInventoryComponent::GetItemAmount(FName Id)
{
	int32 Total = 0;

	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.bOccupied && Slot.Item.ItemId == Id)
		{
			Total += Slot.Item.Amount;
		}
	}

	return Total;
}