// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class YT_TimerManagerSystemTests : ModuleRules
{
	public YT_TimerManagerSystemTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"YT_TimeManagerSystem",
				"FunctionalTesting",
				"AutomationTest"
			}
		);
	}
} 