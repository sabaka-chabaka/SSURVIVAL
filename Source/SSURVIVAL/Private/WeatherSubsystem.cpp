// 2026 sabaka-chabaka

#include "WeatherSubsystem.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VolumetricCloudComponent.h"

void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentWeatherTable.Weather    = EWeatherType::Clear;
	CurrentWeatherTable.DayOfWeek  = 0; // Monday
	CurrentWeatherTable.Month      = 6; // July
	CurrentWeatherTable.Day        = 1;
	CurrentWeatherTable.Hours      = 12;
	CurrentWeatherTable.Minutes    = 0;
	CurrentWeatherTable.Seconds    = 0.f;
}

void UWeatherSubsystem::RegisterComponents(
	UVolumetricCloudComponent*      InCloud,
	UExponentialHeightFogComponent* InFog,
	UDirectionalLightComponent*     InSun)
{
	CloudyComponent = InCloud;
	FogComponent    = InFog;
	SunLight        = InSun;
}

void UWeatherSubsystem::Tick(float DeltaTime)
{
	CurrentWeatherTable.Seconds += DeltaTime * 24.f;

	if (CurrentWeatherTable.Seconds >= 60.f)
	{
		CurrentWeatherTable.Seconds -= 60.f;
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

	UpdateSunRotation();

	if (!CloudyComponent.IsValid() || !FogComponent.IsValid())
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
	if (!SunLight.IsValid())
	{
		return;
	}

	const float TotalSeconds = (CurrentWeatherTable.Hours   * 3600.f)
	                         + (CurrentWeatherTable.Minutes *   60.f)
	                         +  CurrentWeatherTable.Seconds;

	const float DayRatio = TotalSeconds / (24.f * 3600.f);
	const float SunPitch = DayRatio * 360.f - 90.f;

	SunLight->SetRelativeRotation(FRotator(SunPitch, 0.f, 0.f));
}

void UWeatherSubsystem::UpdateMonth()
{
	static const uint8 DaysPerMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	const int32 DaysInMonth = DaysPerMonth[CurrentWeatherTable.Month % 12];

	if (CurrentWeatherTable.Day > DaysInMonth)
	{
		CurrentWeatherTable.Day   = 1;
		CurrentWeatherTable.Month = (CurrentWeatherTable.Month + 1) % 12;
	}
}