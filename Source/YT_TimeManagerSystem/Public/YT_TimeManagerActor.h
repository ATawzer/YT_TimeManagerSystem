#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YT_TimeManagerActor.generated.h"

class UYT_TimeManagerSubsystem;
class UYT_TimeManagerSystemSettings;
class UYT_CalendarDataAsset;

DECLARE_LOG_CATEGORY_EXTERN(LogYT_TimeManagerActor, Log, All);

UCLASS(Blueprintable)
class YT_TIMEMANAGERSYSTEM_API AYT_TimeManagerActor : public AActor
{
	GENERATED_BODY()
public:
	AYT_TimeManagerActor();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Total in-game seconds progressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	int64 ProgressedSeconds = 0;

	UFUNCTION(BlueprintCallable, Category="Time")
	void SetProgressedSeconds(int64 NewSeconds);

	/** Singleton accessor in a world context. */
	UFUNCTION(BlueprintCallable, Category="Time")
	static AYT_TimeManagerActor* Get(const UObject* WorldContextObject);

	/** Get the value for a calendar unit (e.g., "Hour", "Day", etc.) using the actor's or default calendar asset. */
	UFUNCTION(BlueprintCallable, Category="Calendar")
	int32 GetCurrentTimeUnit(FName UnitName) const;

	/** Get a full breakdown of all unit values using the actor's or default calendar asset. */
	UFUNCTION(BlueprintCallable, Category="Calendar")
	TMap<FName, int32> GetAllCurrentTimeUnits() const;

	/** Optional: The calendar asset to use for this actor. If not set, will use the project settings default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Calendar")
	UYT_CalendarDataAsset* CalendarAsset = nullptr;

protected:
	void AdvanceTime(float DeltaSeconds);
	void LoadCurrentTime();
	void CacheSettings();

	UYT_TimeManagerSubsystem* TimeSubsystem;
	const UYT_TimeManagerSystemSettings* CachedSettings = nullptr;
}; 