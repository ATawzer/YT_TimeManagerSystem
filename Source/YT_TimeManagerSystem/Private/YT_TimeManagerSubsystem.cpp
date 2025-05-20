#include "YT_TimeManagerSubsystem.h"

void UYT_TimeManagerSubsystem::SaveTime(int64 InSeconds)
{
	SavedSeconds = InSeconds;
}

int64 UYT_TimeManagerSubsystem::GetSavedTime() const
{
	return SavedSeconds;
}

bool UYT_TimeManagerSubsystem::HasSavedTime() const
{
	return SavedSeconds > 0;
} 