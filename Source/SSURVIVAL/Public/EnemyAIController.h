// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

namespace EnemyBBKeys
{
	const FName TargetActor      = TEXT("TargetActor");
	const FName LastKnownLocation = TEXT("LastKnownLocation");
	const FName bCanSeeTarget    = TEXT("bCanSeeTarget");
	const FName bIsInMeleeRange  = TEXT("bIsInMeleeRange");
	const FName bIsInAttackRange = TEXT("bIsInAttackRange");
}

UCLASS()
class SSURVIVAL_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category="AI")
	void UpdatePerception();

private:
	UPROPERTY()
	class UBlackboardComponent* BB = nullptr;

	FTimerHandle PerceptionTimerHandle;
};