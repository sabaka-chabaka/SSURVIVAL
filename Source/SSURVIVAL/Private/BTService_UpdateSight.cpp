// 2026 sabaka-chabaka

#include "BTService_UpdateSight.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTService_UpdateSight::UBTService_UpdateSight()
{
	NodeName = TEXT("Update Sight");
	Interval = 0.1f; 
	RandomDeviation = 0.05f;
}

void UBTService_UpdateSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AEnemyAIController* AIC = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		AIC->UpdatePerception();
	}
}