// 2026 sabaka-chabaka

#include "WeatherSubsystem.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VolumetricCloudComponent.h"

void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentWeatherTable.Weather = EWeatherType::Clear;
	CurrentWeatherTable.DayOfWeek = 0; // Monday
	CurrentWeatherTable.Month = 6;     // July
	CurrentWeatherTable.Day = 1;
	CurrentWeatherTable.Hours = 12;
	CurrentWeatherTable.Minutes = 0;
	CurrentWeatherTable.Seconds = 0;
}

void UWeatherSubsystem::Tick(float DeltaTime)
{
	CurrentWeatherTable.Seconds += DeltaTime * 24;

	if (CurrentWeatherTable.Seconds >= 60)
	{
		CurrentWeatherTable.Seconds -= 60;
		CurrentWeatherTable.Minutes++;
	}

	if (CurrentWeatherTable.Minutes >= 60)
	{
		CurrentWeatherTable.Minutes = 0;
		CurrentWeatherTable.Hours++;
	}

	if (CurrentWeatherTable.Hours >= 24)
	{
		CurrentWeatherTable.Hours = 0;
		CurrentWeatherTable.Day++;

		CurrentWeatherTable.DayOfWeek = (CurrentWeatherTable.DayOfWeek + 1) % 7;

		UpdateMonth();
	}
	
	if (!CloudyComponent || !FogComponent)
	{
		return;
	}

	switch (CurrentWeatherTable.Weather)
	{
	case EWeatherType::Clear:
		CloudyComponent->SetVisibility(false);
		FogComponent->SetVisibility(true);
		FogComponent->SetFogDensity(0.05f);
		break;
	case EWeatherType::Cloudy:
		CloudyComponent->SetVisibility(true);
		FogComponent->SetVisibility(true);
		FogComponent->SetFogDensity(0.05f);
		break;
	case EWeatherType::Rain:
		CloudyComponent->SetVisibility(true);
		FogComponent->SetVisibility(true);
		FogComponent->SetFogDensity(1.0f);
		break;
	case EWeatherType::Fog:
		CloudyComponent->SetVisibility(false);
		FogComponent->SetVisibility(true);
		FogComponent->SetFogDensity(1.0f);
		break;
	default:
		break;
	}
}

TStatId UWeatherSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWeatherSubsystem, STATGROUP_Tickables);
}

void UWeatherSubsystem::UpdateSunRotation() const
{
	if (!SunLight)
	{
		return;
	}

	float TotalSeconds = (CurrentWeatherTable.Hours * 3600.0f) + (CurrentWeatherTable.Minutes * 60.0f) + CurrentWeatherTable.Seconds;
	
	float DayRatio = TotalSeconds / (24.0f * 3600.0f);
	
	float SunPitch = (DayRatio * 360.0f) + 90.0f;

	FRotator NewRotation = FRotator(SunPitch, 0.0f, 0.0f);
	SunLight->SetRelativeRotation(NewRotation);
}

void UWeatherSubsystem::UpdateMonth()
{
	static const uint8 DaysPerMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	const int32 DaysInMonth = DaysPerMonth[CurrentWeatherTable.Month % 12];

	if (CurrentWeatherTable.Day > DaysInMonth)
	{
		CurrentWeatherTable.Day = 1;
		CurrentWeatherTable.Month = (CurrentWeatherTable.Month + 1) % 12;
	}
}