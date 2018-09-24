// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyEnemyAIController.generated.h"


/**
 * 
 */

//class UBlackboardComponent;
//class UBehaviorTreeComponent;

UCLASS(Blueprintable)
class MYPROJECT_API AMyEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyEnemyAIController();//const FPostConstructInitializeProperties & PCIP


	//UPROPERTY(transient)
	//TSubobjectPtrDeprecated<UBlackboardComponent> BlackboardComp;

	//UPROPERTY(transient)
	//TSubobjectPtrDeprecated<UBehaviorTreeComponent> BehaviorComp;





	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void TrackPlayer();
	
	
	
};