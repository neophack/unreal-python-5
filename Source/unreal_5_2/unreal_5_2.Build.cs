// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class unreal_5_2 : ModuleRules
{
	public unreal_5_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Sockets", "Networking", "Json", "JsonUtilities", "RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        PrivateIncludePaths.AddRange(new string[] {
            "unreal_5_2/Server",
            "unreal_5_2/Message",
            "unreal_5_2/Objects",
            "unreal_5_2/Camera"
        });
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
