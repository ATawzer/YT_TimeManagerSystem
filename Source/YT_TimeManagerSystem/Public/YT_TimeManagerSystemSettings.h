#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "YT_TimeManagerSystemSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Time Manager System Settings"))
class YT_TIMEMANAGERSYSTEM_API UYT_TimeManagerSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UYT_TimeManagerSystemSettings();

	/** How many In Game Seconds progress for each real second. */
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category="Time Progression")
	float TimeSpeed = 1.0f;

    /** The Default Calendar Data Asset to use for the project.
     * This determines what units are used for the calendar.
     */
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, Category="Calendar")
	TSoftObjectPtr<UYT_CalendarDataAsset> DefaultCalendarDataAsset;

    // Default get for developer settings
    UFUNCTION(BlueprintCallable, Category="Time Manager System Settings")
    static UYT_TimeManagerSystemSettings* Get();
}; 