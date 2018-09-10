// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyEnemyAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	
};
