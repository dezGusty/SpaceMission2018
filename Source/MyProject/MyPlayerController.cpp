// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController()
	:
	APlayerController()
{

}
void AMyPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("MyPlayerController BeginPlay"));
	Super::BeginPlay();
	if (wTwinStickHUD)
	{
		myWidget = CreateWidget<UUserWidget>(this, wTwinStickHUD);
		if (myWidget)
		{
			myWidget->AddToViewport();
		}

		bShowMouseCursor = true;
	}

	

}

