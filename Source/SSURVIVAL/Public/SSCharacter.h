// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSCharacter.generated.h"

UCLASS()
class SSURVIVAL_API ASSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASSCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	class UInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditAnywhere, Category="Interaction")
	float InteractionDistance = 250.f;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void EquipWeapon(FName ItemId);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void UnequipWeapon();

	UFUNCTION(BlueprintPure, Category="Weapon")
	class AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	UFUNCTION(BlueprintCallable, Category="UI")
	void ToggleInventory();

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void TurnCamera(float Value);
	void Fire();
	void Reload();
	void TryPickupItem();

	UPROPERTY()
	class AWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	class UInventoryWidget* InventoryWidget = nullptr;

	bool bInventoryOpen = false;
};