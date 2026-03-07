// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
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
	
	UPROPERTY(EditAnywhere, Category="Camera")
	class UCameraComponent* CameraComponent;
	
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void TurnCamera(float Value);
	void Fire();
	void Reload();
	
	UPROPERTY(EditAnywhere)
	AWeapon* CurrentWeapon;
	
public:
	void PickupWeapon(AWeapon* Weapon);
};
