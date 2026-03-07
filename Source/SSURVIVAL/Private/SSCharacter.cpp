// 2026 sabaka-chabaka

#include "SSURVIVAL/Public/SSCharacter.h"

#include "Camera/CameraComponent.h"

ASSCharacter::ASSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
}

void ASSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASSCharacter::Fire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASSCharacter::Reload);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASSCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &ASSCharacter::TurnCamera);
}

void ASSCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASSCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASSCharacter::LookUp(float Value)
{
	AddControllerYawInput(Value);
}

void ASSCharacter::TurnCamera(float Value)
{
	AddControllerPitchInput(Value);
}

void ASSCharacter::Fire()
{
	if (!CurrentWeapon) return;	
	
	CurrentWeapon->Fire(CameraComponent->GetComponentLocation(), CameraComponent->GetForwardVector());
}

void ASSCharacter::Reload()
{
	if (!CurrentWeapon) return;	
	
	CurrentWeapon->Reload();
}

void ASSCharacter::PickupWeapon(AWeapon* Weapon)
{
	CurrentWeapon = Weapon;

	Weapon->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		Weapon->SocketName
	);
}
