// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GhostsNGoblins : ModuleRules
{
	public GhostsNGoblins(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GhostsNGoblins",
			"GhostsNGoblins/Variant_Platforming",
			"GhostsNGoblins/Variant_Platforming/Animation",
			"GhostsNGoblins/Variant_Combat",
			"GhostsNGoblins/Variant_Combat/AI",
			"GhostsNGoblins/Variant_Combat/Animation",
			"GhostsNGoblins/Variant_Combat/Gameplay",
			"GhostsNGoblins/Variant_Combat/Interfaces",
			"GhostsNGoblins/Variant_Combat/UI",
			"GhostsNGoblins/Variant_SideScrolling",
			"GhostsNGoblins/Variant_SideScrolling/AI",
			"GhostsNGoblins/Variant_SideScrolling/Gameplay",
			"GhostsNGoblins/Variant_SideScrolling/Interfaces",
			"GhostsNGoblins/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
