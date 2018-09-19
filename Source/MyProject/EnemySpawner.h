// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "MyProject.h"
#include "EnemyCharacter.h"
#include "EnemySpawner.generated.h"



UCLASS(Blueprintable)
class MYPROJECT_API AEnemySpawner : public AActor
{
		GENERATED_BODY()
public:

	AEnemySpawner();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy Spawner")
	UBoxComponent* SpawnVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Spawner")
	int32 MaxEnemies;
	
	// Sets default values for this actor's properties
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Enemy Spawner")
	void SpawnEnemy();
	
};
