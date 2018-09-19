// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include <MyProject.h>
#include "MyProjectPawn.h"
#include "EnemyCharacter.h"

AMyProjectGameMode::AMyProjectGameMode()
	
{
	// set default pawn class to our character class
	DefaultPawnClass = AMyProjectPawn::StaticClass();
	this->EnemiesPerSecond = 2;
	
	//PlayerControllerClass = AMyPlayerController::StaticClass();
	
}

void AMyProjectGameMode::BeginPlay()
{
	TArray<AActor*> AllOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), AllOutActors);
	if (AllOutActors.Num() > 0) {
		this->Spawner = Cast<AEnemySpawner>(AllOutActors[0]);
	}

	if (this->Spawner) {
		FTimerHandle SpawnTimerHandler;
		GetWorldTimerManager().SetTimer(SpawnTimerHandler, this->Spawner, &AEnemySpawner::SpawnEnemy, 1.0f / this->EnemiesPerSecond, true);
	}

}