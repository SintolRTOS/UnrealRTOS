// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "UnrealRTOSGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealRTOSGameMode() {}
// Cross Module References
	UNREALRTOS_API UClass* Z_Construct_UClass_AUnrealRTOSGameMode_NoRegister();
	UNREALRTOS_API UClass* Z_Construct_UClass_AUnrealRTOSGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_UnrealRTOS();
// End Cross Module References
	void AUnrealRTOSGameMode::StaticRegisterNativesAUnrealRTOSGameMode()
	{
	}
	UClass* Z_Construct_UClass_AUnrealRTOSGameMode_NoRegister()
	{
		return AUnrealRTOSGameMode::StaticClass();
	}
	UClass* Z_Construct_UClass_AUnrealRTOSGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AGameModeBase,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealRTOS,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "UnrealRTOSGameMode.h" },
				{ "ModuleRelativePath", "UnrealRTOSGameMode.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AUnrealRTOSGameMode>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AUnrealRTOSGameMode::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00880288u,
				nullptr, 0,
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AUnrealRTOSGameMode, 3083533373);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUnrealRTOSGameMode(Z_Construct_UClass_AUnrealRTOSGameMode, &AUnrealRTOSGameMode::StaticClass, TEXT("/Script/UnrealRTOS"), TEXT("AUnrealRTOSGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealRTOSGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
