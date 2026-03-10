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
	
	UPROPERTY(EditAnywhere)
	int MaxSlots;
	
	bool AddItem(const FItemInstance& Item);
	bool GetItem(FName Id, FItemInstance& OutItem);
	bool RemoveItem(FName Id, int32 Amount);
	int32 GetItemAmount(FName Id);
	
protected:
	UPROPERTY()
	TArray<FInventorySlot> Slots;
	
	UPROPERTY(EditAnywhere)
	TMap<FName, FItemData> ItemDatabase;
};