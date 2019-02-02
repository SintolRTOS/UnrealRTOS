// Fill out your copyright notice in the Description page of Project Settings.

#include "AboutHUD.h"
#include "Engine/Canvas.h"



void AAboutHUD::DrawHUD()
{
	FString AboutStr = 
L"|---------------------------------------------------------------------------\r\n\
|                 Welcome to SintolRTOS       \r\n\
|               It's created by wangjingyi     \r\n\
|              Email:langkexiaoyi@gmail.com      \r\n\
|                   Wechat:18513285865        \r\n\
|    It can help you create large-scale distributed computing       \r\n\
|    It is the basic calculation of distributed cluster artificial intelligence     \r\n\
|    You can use sintolsdk to link node for creating and joining fed         \r\n\
|-----------------------------------------------------------------------------\r\n";
	DrawText(AboutStr, FColor::Red, 10.0f, 10.0f, HUDFont);
}
