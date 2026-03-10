// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.h"
#include "GameFramework/Actor.h"
#include "WorldItem.generated.h"

UCLASS()
class SSURVIVAL_API AWorldItem : public AActor
{
	GENERATED_BODY()

public:
	AWorldItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	FItemInstance Item;
};