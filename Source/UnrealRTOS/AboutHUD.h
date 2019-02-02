// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AboutHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRTOS_API AAboutHUD : public AHUD
{
	GENERATED_BODY()
	UFont* HUDFont;

	//ÿһ֡�������
	virtual void DrawHUD() override;
};
