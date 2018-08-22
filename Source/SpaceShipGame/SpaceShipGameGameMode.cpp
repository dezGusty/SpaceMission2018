// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceShipGameGameMode.h"
#include "SpaceShipGamePawn.h"

ASpaceShipGameGameMode::ASpaceShipGameGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ASpaceShipGamePawn::StaticClass();
}

