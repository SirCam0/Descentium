// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Descentium : ModuleRules
{
	public Descentium(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "UMG", "Slate", "SlateCore", "CableComponent", "NiagaraUIRenderer", "GameplayTasks", "NavigationSystem"});
		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent", "NiagaraUIRenderer", "Niagara"});
        PrivateIncludePathModuleNames.AddRange(new string[] { "CableComponent", "NiagaraUIRenderer", "Niagara"});
        
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Steam", "lib", "steam_api64.lib"));

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
