// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class E20240808_01 : ModuleRules
{
	public E20240808_01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "IrisCore" });
	}
}
