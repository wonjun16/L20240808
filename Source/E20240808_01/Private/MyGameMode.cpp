// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyHUD.h"
#include "MyPlayerController.h"
#include "BasePawn.h"

AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = ABasePawn::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}
