// 2026 sabaka-chabaka

#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryComponent::AddItem(FItemInstance Item)
{
	for (FInventorySlot& Slot : Slots)
	{
		if (!Slot.bOccupied)
		{
			Slot.bOccupied = true;
			Slot.Item = Item;
			return true;
		}
	}

	return false;
}