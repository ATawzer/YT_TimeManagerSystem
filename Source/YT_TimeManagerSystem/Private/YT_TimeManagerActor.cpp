#include "YT_TimeManagerActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "YT_TimeManagerSystemLog.h"
#include "YT_TimeManagerSystemSettings.h"
#include "YT_TimeManagerSubsystem.h"
#include "YT_CalendarDataAsset.h"

AYT_TimeManagerActor::AYT_TimeManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AYT_TimeManagerActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogYT_TimeManagerSystem, Log, TEXT("TimeManagerActor BeginPlay: ProgressedSeconds=%lld"), ProgressedSeconds);
	TimeSubsystem = GetGameInstance() ? GetGameInstance()->GetSubsystem<UYT_TimeManagerSubsystem>() : nullptr;
	CacheSettings();
	LoadCurrentTime();
}

void AYT_TimeManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogYT_TimeManagerSystem, Log, TEXT("TimeManagerActor EndPlay: ProgressedSeconds=%lld"), ProgressedSeconds);
	if (TimeSubsystem)
	{
		TimeSubsystem->SaveTime(ProgressedSeconds);
	}
	Super::EndPlay(EndPlayReason);
}

void AYT_TimeManagerActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AdvanceTime(DeltaSeconds);
	UE_LOG(LogYT_TimeManagerSystem, Verbose, TEXT("Tick: ProgressedSeconds=%lld"), ProgressedSeconds);
}

void AYT_TimeManagerActor::SetProgressedSeconds(int64 NewSeconds)
{
	ProgressedSeconds = NewSeconds;
}

void AYT_TimeManagerActor::AdvanceTime(float DeltaSeconds)
{
	if (!CachedSettings) return;

	float TimeSpeed = CachedSettings->TimeSpeed;
	ProgressedSeconds += static_cast<int64>(DeltaSeconds * TimeSpeed);
}

void AYT_TimeManagerActor::CacheSettings()
{
	CachedSettings = GetDefault<UYT_TimeManagerSystemSettings>();
}

void AYT_TimeManagerActor::LoadCurrentTime()
{
	if (TimeSubsystem && TimeSubsystem->HasSavedTime())
	{
		ProgressedSeconds = TimeSubsystem->GetSavedTime();
	}
}

AYT_TimeManagerActor* AYT_TimeManagerActor::Get(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(World, AYT_TimeManagerActor::StaticClass(), Found);
	if (Found.Num() == 0) return nullptr;
	if (Found.Num() > 1)
	{
		UE_LOG(LogYT_TimeManagerSystem, Warning, TEXT("Multiple YT_TimeManagerActors found! Using the first."));
	}
	return Cast<AYT_TimeManagerActor>(Found[0]);
}

int32 AYT_TimeManagerActor::GetCurrentTimeUnit(FName UnitName) const
{
	UYT_CalendarDataAsset* CalendarToUse = CalendarAsset;
	if (!CalendarToUse)
	{
		const UYT_TimeManagerSystemSettings* Settings = GetDefault<UYT_TimeManagerSystemSettings>();
		if (Settings && Settings->DefaultCalendarDataAsset.IsValid())
		{
			CalendarToUse = Settings->DefaultCalendarDataAsset.LoadSynchronous();
		}
	}
	int32 Value = CalendarToUse ? CalendarToUse->GetUnitValue(UnitName, ProgressedSeconds) : 0;
	return Value;
}

TMap<FName, int32> AYT_TimeManagerActor::GetAllCurrentTimeUnits() const
{
	UYT_CalendarDataAsset* CalendarToUse = CalendarAsset;
	if (!CalendarToUse)
	{
		const UYT_TimeManagerSystemSettings* Settings = GetDefault<UYT_TimeManagerSystemSettings>();
		if (Settings && Settings->DefaultCalendarDataAsset.IsValid())
		{
			CalendarToUse = Settings->DefaultCalendarDataAsset.LoadSynchronous();
		}
	}
	TMap<FName, int32> Result = CalendarToUse ? CalendarToUse->GetAllUnitValues(ProgressedSeconds) : TMap<FName, int32>();
	return Result;
} 