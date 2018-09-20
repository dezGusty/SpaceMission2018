// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController()
	:
	APlayerController()
{

}
void AMyPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("MyPlayerController BeginPlay"));
	Super::BeginPlay();


	

}

