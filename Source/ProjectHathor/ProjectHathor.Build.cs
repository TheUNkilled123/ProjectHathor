// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectHathor : ModuleRules
{
	public ProjectHathor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "HeadMountedDisplay", "GameplayTasks"});
	}
}
