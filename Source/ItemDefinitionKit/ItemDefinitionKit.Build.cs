// Copyright @Kay(JunjieXian)
// Item Definition Kit for Unreal Engine 5.0+
// Includes item definition, fragment, action and instance.

using UnrealBuildTool;

public class ItemDefinitionKit : ModuleRules {
	public ItemDefinitionKit(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
		);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
		);


		PublicDependencyModuleNames.AddRange(
			new[] {
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"GameplayTags"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[] {
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}