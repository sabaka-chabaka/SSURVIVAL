// 2026 sabaka-chabaka

#include "BTTask_RangedAttack.h"

#include "EnemyCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_RangedAttack::UBTTask_RangedAttack()
{
	NodeName = TEXT("Ranged Attack");
}

EBTNodeResult::Type UBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Enemy) return EBTNodeResult::Failed;

	if (!Enemy->CanAttack()) return EBTNodeResult::Failed;

	Enemy->PerformRangedAttack();
	return EBTNodeResult::Succeeded;
}