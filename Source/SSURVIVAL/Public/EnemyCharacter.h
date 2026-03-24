// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Melee   UMETA(DisplayName="Melee"),
	Ranged  UMETA(DisplayName="Ranged")
};

UCLASS()
class SSURVIVAL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	EEnemyType EnemyType = EEnemyType::Melee;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float MeleeDamage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float MeleeRadius = 150.f;

	UPROPERTY(EditAnywhere, Category="Enemy|Stats")
	TSubclassOf<class AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|AI")
	float DetectionRange = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|AI")
	float MeleeRange = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|AI")
	float AttackRange = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|AI")
	float AttackCooldown = 1.5f;

	UFUNCTION(BlueprintCallable, Category="Enemy")
	void PerformMeleeAttack();

	UFUNCTION(BlueprintCallable, Category="Enemy")
	void PerformRangedAttack();

	UFUNCTION(BlueprintPure, Category="Enemy")
	bool CanAttack() const;

	UFUNCTION(BlueprintPure, Category="Enemy")
	bool IsAlive() const { return Health > 0.f; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnHit(float DamageAmount);

private:
	float LastAttackTime = -999.f;

	void Die();
};