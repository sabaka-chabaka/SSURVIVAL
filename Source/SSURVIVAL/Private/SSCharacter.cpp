// 2026 sabaka-chabaka

#include "SSURVIVAL/Public/SSCharacter.h"

#include "Camera/CameraComponent.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Weapon.h"
#include "WorldItem.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

ASSCharacter::ASSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
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
	PlayerInputComponent->BindAction("Jump",      IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire",      IE_Pressed, this, &ASSCharacter::Fire);
	PlayerInputComponent->BindAction("Reload",    IE_Pressed, this, &ASSCharacter::Reload);
	PlayerInputComponent->BindAction("Interact",  IE_Pressed, this, &ASSCharacter::TryPickupItem);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ASSCharacter::ToggleInventory);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",   this, &ASSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",      this, &ASSCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAtRate",  this, &ASSCharacter::TurnCamera);
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

void ASSCharacter::TryPickupItem()
{
	const FVector Start = CameraComponent->GetComponentLocation();
	const FVector End   = Start + CameraComponent->GetForwardVector() * InteractionDistance;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (!GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
		return;

	AWorldItem* WorldItem = Cast<AWorldItem>(HitResult.GetActor());
	if (WorldItem)
		WorldItem->TryPickup(this);
}

void ASSCharacter::EquipWeapon(FName ItemId)
{
	if (!InventoryComponent) return;

	const FItemData* Data = InventoryComponent->GetItemData(ItemId);
	if (!Data || Data->Type != IT_Weapon || !Data->WeaponClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SSCharacter] EquipWeapon: '%s' не является оружием или не задан WeaponClass"), *ItemId.ToString());
		return;
	}

	UnequipWeapon();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(Data->WeaponClass, FTransform::Identity, SpawnParams);
	if (!CurrentWeapon) return;

	CurrentWeapon->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		CurrentWeapon->SocketName
	);

	UE_LOG(LogTemp, Log, TEXT("[SSCharacter] Оружие '%s' взято в руки"), *ItemId.ToString());
}

void ASSCharacter::UnequipWeapon()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Destroy();
	CurrentWeapon = nullptr;
}

void ASSCharacter::ToggleInventory()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	if (!InventoryWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SSCharacter] InventoryWidgetClass не задан!"));
		return;
	}

	if (!InventoryWidget)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(PC, InventoryWidgetClass);
		if (!InventoryWidget) return;

		InventoryWidget->InitInventory(InventoryComponent, this);
	}

	bInventoryOpen = !bInventoryOpen;

	if (bInventoryOpen)
	{
		InventoryWidget->AddToViewport();
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}
	else
	{
		InventoryWidget->RemoveFromViewport();
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}
}
