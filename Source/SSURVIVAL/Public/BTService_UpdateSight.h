// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateSight.generated.h"

UCLASS()
class SSURVIVAL_API UBTService_UpdateSight : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateSight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
