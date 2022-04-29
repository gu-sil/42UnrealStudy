// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal42 : ModuleRules
{
	public Unreal42(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
