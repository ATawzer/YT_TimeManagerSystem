#include "YT_TimeListenerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "YT_TimeManagerActor.h"
#include "YT_TimeManagerSystemSettings.h"
#include "YT_CalendarDataAsset.h"
#include "YT_TimeManagerSystemLog.h"

UYT_TimeListenerComponent::UYT_TimeListenerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UYT_TimeListenerComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedTimeManager = AYT_TimeManagerActor::Get(GetWorld());
	UE_LOG(LogYT_TimeManagerSystem, Log, TEXT("TimeListenerComponent %s BeginPlay: CachedTimeManager=%s"), *GetNameSafe(this), CachedTimeManager ? *CachedTimeManager->GetName() : TEXT("nullptr"));
}

int32 UYT_TimeListenerComponent::GetCurrentTime(FName UnitName) const
{
	if (!CachedTimeManager) return 0;
	return CachedTimeManager->GetCurrentTimeUnit(UnitName);
}

int32 UYT_TimeListenerComponent::GetCurrentTimeUnit(FName UnitName) const
{
	if (!CachedTimeManager) return 0;
	UYT_CalendarDataAsset* CalendarToUse = CalendarAsset;
	if (!CalendarToUse)
	{
		const UYT_TimeManagerSystemSettings* Settings = GetDefault<UYT_TimeManagerSystemSettings>();
		if (Settings && Settings->DefaultCalendarDataAsset.IsValid())
		{
			CalendarToUse = Settings->DefaultCalendarDataAsset.LoadSynchronous();
		}
	}
	int32 Value = CalendarToUse ? CalendarToUse->GetUnitValue(UnitName, CachedTimeManager->ProgressedSeconds) : 0;
	return Value;
}

TMap<FName, int32> UYT_TimeListenerComponent::GetAllCurrentTimeUnits() const
{
	if (!CachedTimeManager) return TMap<FName, int32>();
	UYT_CalendarDataAsset* CalendarToUse = CalendarAsset;
	if (!CalendarToUse)
	{
		const UYT_TimeManagerSystemSettings* Settings = GetDefault<UYT_TimeManagerSystemSettings>();
		if (Settings && Settings->DefaultCalendarDataAsset.IsValid())
		{
			CalendarToUse = Settings->DefaultCalendarDataAsset.LoadSynchronous();
		}
	}
	TMap<FName, int32> Result = CalendarToUse ? CalendarToUse->GetAllUnitValues(CachedTimeManager->ProgressedSeconds) : TMap<FName, int32>();
	return Result;
} 