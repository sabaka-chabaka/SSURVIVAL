// 2026 sabaka-chabaka

#include "WorldItem.h"

#include "InventoryComponent.h"
#include "SSCharacter.h"
#include "Components/SphereComponent.h"

AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(PickupRadius);
	InteractionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AWorldItem::OnOverlapBegin);
}

void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	InteractionSphere->SetSphereRadius(PickupRadius);
}

bool AWorldItem::TryPickup(ASSCharacter* Character)
{
	if (!Character) return false;

	UInventoryComponent* Inventory = Character->FindComponentByClass<UInventoryComponent>();
	if (!Inventory) return false;

	if (Inventory->AddItem(Item))
	{
		Destroy();
		return true;
	}

	return false;
}

void AWorldItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bAutoPickup) return;

	if (ASSCharacter* Character = Cast<ASSCharacter>(OtherActor))
	{
		TryPickup(Character);
	}
}