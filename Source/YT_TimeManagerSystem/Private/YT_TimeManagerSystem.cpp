#include <YT_TimeManagerSystem.h>
#include <YT_TimeManagerSystemLog.h>

#define LOCTEXT_NAMESPACE "FYT_TimeManagerSystemModule"

void FYT_TimeManagerSystemModule::StartupModule()
{
	UE_LOG(LogYT_TimeManagerSystem, Log, TEXT("YT_TimeManagerSystem: Module Started"));
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FYT_TimeManagerSystemModule::ShutdownModule()
{
	UE_LOG(LogYT_TimeManagerSystem, Log, TEXT("YT_TimeManagerSystem: Module Shutdown"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYT_TimeManagerSystemModule, YT_TimeManagerSystem) 