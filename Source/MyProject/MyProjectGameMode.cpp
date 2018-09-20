// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include <MyProject.h>
#include "MyProjectPawn.h"
#include "EnemyCharacter.h"

AMyProjectGameMode::AMyProjectGameMode()
	
{
	// set default pawn class to our character class
	DefaultPawnClass = AMyProjectPawn::StaticClass();
	this->EnemiesPerSecond = 1;
	
	//PlayerControllerClass = AMyPlayerController::StaticClass();
	
}

void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> AllOutActors;
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), AllOutActors);

	UE_LOG(LogTemp, Warning, TEXT("Begining play %d"), AllOutActors.Num());

	

	if (AllOutActors.Num() > 0) {
	this->Spawner = Cast<AEnemySpawner>(AllOutActors[0]);
	UE_LOG(LogTemp, Warning, TEXT(" Spawner Casted "));
	}
	UE_LOG(LogTemp, Warning, TEXT(" Before Spawner created "));

	if ((this->Spawner)!=nullptr) {

		UE_LOG(LogTemp, Warning, TEXT(" Spawner created "));
		float fRate = 1;
		if (this->EnemiesPerSecond != 0) {
			fRate = 1.0f / this->EnemiesPerSecond;
		}

		FTimerHandle SpawnTimerHandler;

		GetWorldTimerManager().SetTimer(
			SpawnTimerHandler, 
			this->Spawner, 
			&AEnemySpawner::SpawnEnemy, 
			fRate,
			true);
		UE_LOG(LogTemp, Warning, TEXT(" Spawn Timer Fired"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Spawner NOT created "));

	}
	
}