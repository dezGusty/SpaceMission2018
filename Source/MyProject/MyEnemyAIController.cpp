// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAIController.h"
#include "MyProjectPawn.h"
#include "MyProject.h"


AMyEnemyAIController::AMyEnemyAIController()
{

}


void AMyEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle handler;
	GetWorldTimerManager().SetTimer(handler, this, &AMyEnemyAIController::TrackPlayer, 1.0f, true, 0.0f);
}

void AMyEnemyAIController::TrackPlayer()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC) {
		this->MoveToActor(PC->GetPawn(), 5);
	}
}



