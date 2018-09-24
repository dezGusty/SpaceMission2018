// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyProjectGameMode.generated.h"

UCLASS()
class AMyProjectGameMode : public AGameMode
{
	GENERATED_BODY()
	AMyProjectGameMode();
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinShooter Game Mode")
	FTransform PlayerSpawnTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinShooter Game Mode")
	int32 Score;

	UFUNCTION(BlueprintCallable, Category = "TwinShooter Game Mode")
	void RespawnPlayer();

	UFUNCTION(BlueprintCallable, Category = "TwinShooter Game Mode")
	void IncrementScore(int32 DeltaScore);

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "TwinShooter Game Mode")
	//AEnemySpawner* Spawner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TwinShooter Game Mode")
	int32 EnemiesPerSecond;

	virtual void BeginPlay() override;
};



