// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CosmicInterrogation : ModuleRules
{
	public CosmicInterrogation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
