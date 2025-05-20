#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FYT_TimeManagerSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
}; 