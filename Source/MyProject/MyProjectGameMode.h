// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EnemySpawner.h"
#include "MyPlayerController.h"
#include "MyProjectGameMode.generated.h"

UCLASS(MinimalAPI)
class AMyProjectGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinShooter Game Mode")
	FTransform PlayerSpawnTransform;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "TwinShooter Game Mode")
	AEnemySpawner* Spawner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinShooter Game Mode")
	int32 EnemiesPerSecond;

	virtual void BeginPlay();
};



