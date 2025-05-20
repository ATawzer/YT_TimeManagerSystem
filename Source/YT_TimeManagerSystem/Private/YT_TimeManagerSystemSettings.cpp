#include "YT_TimeManagerSystemSettings.h"

UYT_TimeManagerSystemSettings::UYT_TimeManagerSystemSettings()
{
	CategoryName = TEXT("Game");
	SectionName = TEXT("Time Manager System");
	// DefaultCalendarDataAsset can be set in project settings.
}

UYT_TimeManagerSystemSettings* UYT_TimeManagerSystemSettings::Get()
{
	return GetMutableDefault<UYT_TimeManagerSystemSettings>();
} 