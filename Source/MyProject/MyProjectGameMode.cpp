// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include <MyProject.h>
#include "MyProjectPawn.h"

AMyProjectGameMode::AMyProjectGameMode()
	:
	AGameModeBase()
{
	// set default pawn class to our character class
	DefaultPawnClass = AMyProjectPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	
}

