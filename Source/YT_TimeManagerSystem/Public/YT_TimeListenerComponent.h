#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YT_TimeManagerActor.h"
#include "YT_TimeListenerComponent.generated.h"

// Logging: Uses LogYT_TimeManagerSystem for all logging.

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YT_TIMEMANAGERSYSTEM_API UYT_TimeListenerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UYT_TimeListenerComponent();

	UFUNCTION(BlueprintCallable, Category="Time")
	int32 GetCurrentTime(FName UnitName) const;

	/** Get the value for a calendar unit (e.g., "Hour", "Day", etc.) using the component's or default calendar asset. */
	UFUNCTION(BlueprintCallable, Category="Calendar")
	int32 GetCurrentTimeUnit(FName UnitName) const;

	/** Get a full breakdown of all unit values using the component's or default calendar asset. */
	UFUNCTION(BlueprintCallable, Category="Calendar")
	TMap<FName, int32> GetAllCurrentTimeUnits() const;

	/** Optional: The calendar asset to use for this component. If not set, will use the project settings default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Calendar")
	UYT_CalendarDataAsset* CalendarAsset = nullptr;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AYT_TimeManagerActor* CachedTimeManager;
}; 