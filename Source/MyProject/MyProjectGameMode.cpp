// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include <MyProject.h>
#include "MyProjectPawn.h"
#include "EnemyCharacter.h"
#include "MyPlayerController.h"
#include "EnemySpawner.h"


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

	AEnemySpawner* Spawner = nullptr;

	if (AllOutActors.Num() > 0) {
		Spawner = Cast<AEnemySpawner>(AllOutActors[0]);
	}


	if ((Spawner)!=nullptr) {


		float fRate = 1;
		if (this->EnemiesPerSecond != 0) {
			fRate = 1.0f / this->EnemiesPerSecond;
		}

		FTimerHandle SpawnTimerHandler;

		GetWorldTimerManager().SetTimer(
			SpawnTimerHandler, 
			Spawner, 
			&AEnemySpawner::SpawnEnemy, 
			fRate,
			true);
	
	}

	
}

void AMyProjectGameMode::RespawnPlayer()
{
	UWorld * World = GetWorld();

	if (World) {
		TArray<AActor *> AllOutActors;
		UGameplayStatics::GetAllActorsOfClass(World, AEnemyCharacter::StaticClass(), AllOutActors);

		for (AActor * EachActor : AllOutActors) {
			EachActor->Destroy();
		}

		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
		AMyProjectPawn * NewPlayerCharacter = World->SpawnActor<AMyProjectPawn>(this->PlayerSpawnTransform.GetLocation(), this->PlayerSpawnTransform.GetRotation().Rotator());
		APlayerController * PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->Possess(NewPlayerCharacter);
	}
}

void AMyProjectGameMode::IncrementScore(int32 DeltaScore)
{
	this->Score += DeltaScore;
}