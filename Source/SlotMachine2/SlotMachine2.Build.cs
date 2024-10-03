// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlotMachine2 : ModuleRules
{
	public SlotMachine2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
	}
}
