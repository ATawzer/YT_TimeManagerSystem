#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "YT_TimeManagerSubsystem.generated.h"

UCLASS()
class YT_TIMEMANAGERSYSTEM_API UYT_TimeManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle persistence of time state between levels.
public:

	/** Save the current time in seconds. */
	UFUNCTION(BlueprintCallable, Category="Time")
	void SaveTime(int64 InSeconds);

	/** Get the saved time in seconds. */
	UFUNCTION(BlueprintCallable, Category="Time")
	int64 GetSavedTime() const;

	/** Whether progressed time has been saved. */
	UFUNCTION(BlueprintCallable, Category="Time")
	bool HasSavedTime() const;

private:
	UPROPERTY(VisibleAnywhere, Category="Time")
	int64 SavedSeconds = 0;
}; 