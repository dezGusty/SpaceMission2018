// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectPawn.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets") TSubclassOf<class UUserWidget> wTwinStickHUD;
	UUserWidget* myWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
