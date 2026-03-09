// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include "WeatherSubsystem.generated.h"

UENUM(BlueprintType)
enum EWeatherType : uint8
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
	EWeatherType Weather;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDayOfWeek> DayOfWeek;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EMonthOfYear> Month;
	
	UPROPERTY(EditAnywhere)
	float Day;
	
	UPROPERTY(EditAnywhere)
	float Hours;
	
	UPROPERTY(EditAnywhere)
	float Minutes;
	
	UPROPERTY(EditAnywhere)
	float Seconds;
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
	
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return true; };
	
private:
	FWeatherTable CurrentWeatherTable;
	
protected:
	UPROPERTY(EditAnywhere, Category="Weather")
	class UVolumetricCloudComponent* CloudyComponent;
	
	UPROPERTY(EditAnywhere, Category="Weather")
	class UExponentialHeightFogComponent* FogComponent;

	UPROPERTY(EditAnywhere, Category="Weather")
	class UDirectionalLightComponent* SunLight;
	
	void UpdateSunRotation() const;
	void UpdateMonth();
};