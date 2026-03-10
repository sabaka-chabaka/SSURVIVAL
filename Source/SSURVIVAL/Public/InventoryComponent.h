// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SSURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY()
	TArray<FInventorySlot> Slots;
	
	UPROPERTY(EditAnywhere)
	int MaxSlots;
	
	bool AddItem(FItemInstance Item);
};