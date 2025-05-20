#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YT_CalendarDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FCalendarUnit
{
	GENERATED_BODY();

	// Name of the unit (e.g., "Hour", "Day", "Week", "Season")
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Calendar")
	FName Name;

	// How many seconds in one of this unit
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Calendar")
	int64 SecondsPerUnit = 0;

	// Does this unit cycle/wrap?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Calendar")
	bool bCycles = false;

	// If it cycles, what is the max before it wraps? (e.g., 24 for hours, 7 for days in week)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Calendar", meta=(EditCondition="bCycles"))
	int32 CycleAmount = 0;

	// Optional: names for each cycle (e.g., days of week, seasons)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Calendar")
	TArray<FText> CycleNames;

	// Get the value for this unit from raw seconds. If not cycling, returns raw value.
	int32 GetValue(int64 ProgressedSeconds) const
	{
		if (SecondsPerUnit <= 0) return 0;
		int64 RawValue = ProgressedSeconds / SecondsPerUnit;
		if (bCycles && CycleAmount > 0)
		{
			return static_cast<int32>(RawValue % CycleAmount);
		}
		return static_cast<int32>(RawValue);
	}

	// Get the cycle name for this unit from raw seconds. If not cycling or no names, returns empty text.
	FText GetCycleName(int64 ProgressedSeconds) const
	{
		if (!bCycles || CycleNames.Num() == 0) return FText::GetEmpty();
		int32 Value = GetValue(ProgressedSeconds);
		if (CycleNames.IsValidIndex(Value))
		{
			return CycleNames[Value];
		}
		return FText::GetEmpty();
	}
};

UCLASS(BlueprintType)
class YT_TIMEMANAGERSYSTEM_API UYT_CalendarDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	// The units that make up this calendar, in any order
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Calendar")
	TArray<FCalendarUnit> Units;

	// Get the value for a given unit (e.g., "Hour", "Day", "Week", etc.)
	UFUNCTION(BlueprintCallable, Category="Calendar")
	int32 GetUnitValue(FName UnitName, int64 ProgressedSeconds) const;

	// Get the cycle name for a given unit (e.g., "Monday" for day of week)
	UFUNCTION(BlueprintCallable, Category="Calendar")
	FText GetCycleName(FName UnitName, int64 ProgressedSeconds) const;

	// Get a full breakdown of all unit values
	UFUNCTION(BlueprintCallable, Category="Calendar")
	TMap<FName, int32> GetAllUnitValues(int64 ProgressedSeconds) const;
}; 