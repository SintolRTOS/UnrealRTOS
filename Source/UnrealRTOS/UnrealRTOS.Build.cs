// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UnrealRTOS : ModuleRules
{
	public UnrealRTOS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        bEnableExceptions = true;

        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include", "rti1516"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include", "SintolRTI"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "sintolsdk.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "SintolRTI.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "rti1516.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "fedtime1516.lib"));
        //PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "dll"));
        //PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "dll"));
        //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "dll", "SintolRTId.dll")));
        //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "dll", "RTI-NGd.dll")));
        //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "dll", "rti1516d.dll")));
        //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "dll", "fedtime1516d.dll")));
        //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "dll", "FedTimed.dll")));
    }

    private string ModulePath
    {
        get
        {
            return ModuleDirectory;
        }
    }

    private string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty"));
        }
    }
}
