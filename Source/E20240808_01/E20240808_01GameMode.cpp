// Copyright Epic Games, Inc. All Rights Reserved.

#include "E20240808_01GameMode.h"
#include "E20240808_01Character.h"
#include "UObject/ConstructorHelpers.h"

AE20240808_01GameMode::AE20240808_01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
