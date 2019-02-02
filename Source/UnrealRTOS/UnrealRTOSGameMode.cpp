// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealRTOSGameMode.h"
#include "UnrealRTOSCharacter.h"
#include "AboutHUD.h"
#include "UObject/ConstructorHelpers.h"

AUnrealRTOSGameMode::AUnrealRTOSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AHUD> RTOSHUDClass(TEXT("/Game/ThirdPersonCPP/Blueprints/RTOSAboutHUD"));
	if (RTOSHUDClass.Class != NULL)
	{
		HUDClass = RTOSHUDClass.Class;
	}
}
