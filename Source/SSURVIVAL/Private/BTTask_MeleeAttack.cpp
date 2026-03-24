// 2026 sabaka-chabaka

#include "BTTask_MeleeAttack.h"

#include "EnemyCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Enemy) return EBTNodeResult::Failed;

	if (!Enemy->CanAttack()) return EBTNodeResult::Failed;

	Enemy->PerformMeleeAttack();
	return EBTNodeResult::Succeeded;
}