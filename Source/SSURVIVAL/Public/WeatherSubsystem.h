// 2026 sabaka-chabaka

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
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