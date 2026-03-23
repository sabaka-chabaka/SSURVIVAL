// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include "WeatherSubsystem.generated.h"

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	Clear,
	Cloudy,
	Rain,
	Fog
};

USTRUCT(BlueprintType)
struct FWeatherTable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EWeatherType Weather = EWeatherType::Clear;

	UPROPERTY(EditAnywhere, Meta=(ClampMin=0, ClampMax=6))
	uint8 DayOfWeek = 0;

	UPROPERTY(EditAnywhere, Meta=(ClampMin=0, ClampMax=11))
	uint8 Month = 6;

	UPROPERTY(EditAnywhere)
	int32 Day = 1;

	UPROPERTY(EditAnywhere)
	int32 Hours = 12;

	UPROPERTY(EditAnywhere)
	int32 Minutes = 0;

	UPROPERTY(EditAnywhere)
	float Seconds = 0.f;
};

UCLASS()
class SSURVIVAL_API UWeatherSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void ChangeWeatherTable(const FWeatherTable& NewTable) { CurrentWeatherTable = NewTable; }

	UFUNCTION(BlueprintCallable)
	FWeatherTable GetWeather() const { return CurrentWeatherTable; }
	
	UFUNCTION(BlueprintCallable, Category="Weather")
	void RegisterComponents(
		class UVolumetricCloudComponent* InCloud,
		class UExponentialHeightFogComponent* InFog,
		class UDirectionalLightComponent* InSun);

	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return true; }

private:
	FWeatherTable CurrentWeatherTable;

	TWeakObjectPtr<class UVolumetricCloudComponent>      CloudyComponent;
	TWeakObjectPtr<class UExponentialHeightFogComponent> FogComponent;
	TWeakObjectPtr<class UDirectionalLightComponent>     SunLight;

	void UpdateSunRotation() const;
	void UpdateMonth();
};