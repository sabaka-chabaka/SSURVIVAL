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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FItemInstance Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* InteractionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float PickupRadius = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool bAutoPickup = false;

	bool TryPickup(class ASSCharacter* Character);
	
protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};