// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectPawn.h"
#include "MyDamage.generated.h"

UCLASS()
class MYPROJECT_API AMyDamage : public APawn
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AMyDamage();

	UFUNCTION()
	void AffectHealth_Implementation(float Delta, bool isEnemy);

	UFUNCTION()
	void CalculateDead();
	
	UFUNCTION()
	void CalculateHealth(float Delta);

	UFUNCTION()
	void DestroyEnemy();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float Health = 80.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	bool isDead = false;
	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	int32 Score;
	
	FTimerHandle DeadAnimationTimerHandler;
};
