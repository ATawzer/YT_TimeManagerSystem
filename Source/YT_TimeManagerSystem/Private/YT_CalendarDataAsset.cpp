#include "YT_CalendarDataAsset.h"

int32 UYT_CalendarDataAsset::GetUnitValue(FName UnitName, int64 ProgressedSeconds) const
{
	const FCalendarUnit* Unit = Units.FindByPredicate([&](const FCalendarUnit& U) { return U.Name == UnitName; });
	return Unit ? Unit->GetValue(ProgressedSeconds) : 0;
}

FText UYT_CalendarDataAsset::GetCycleName(FName UnitName, int64 ProgressedSeconds) const
{
	const FCalendarUnit* Unit = Units.FindByPredicate([&](const FCalendarUnit& U) { return U.Name == UnitName; });
	return Unit ? Unit->GetCycleName(ProgressedSeconds) : FText::GetEmpty();
}

TMap<FName, int32> UYT_CalendarDataAsset::GetAllUnitValues(int64 ProgressedSeconds) const
{
	TMap<FName, int32> Result;
	for (const FCalendarUnit& Unit : Units)
	{
		Result.Add(Unit.Name, Unit.GetValue(ProgressedSeconds));
	}
	return Result;
} 