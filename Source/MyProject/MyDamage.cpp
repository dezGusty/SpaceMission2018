// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDamage.h"
#include "MyProjectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"
#include "MyProjectGameMode.h"
#include "MyEnemyAIController.h"
#include "kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AMyDamage::AMyDamage()
{


}

// Called when the game starts or when spawned

void AMyDamage::AffectHealth_Implementation(float Delta, bool isEnemy)
{
	UE_LOG(LogTemp, Warning, TEXT("AffectHealth reusit"));
	this->CalculateHealth(Delta);

	if (this->isDead)
	{

		AMyProjectGameMode * GameMode = Cast<AMyProjectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (isEnemy)
		{
			GameMode->IncrementScore(Score);
			AMyDamage::DestroyEnemy();
			/*this->detachfromcontrollerpendingdestroy();

			if (!getworldtimermanager().istimeractive(deadanimationtimerhandler)) {
				getworldtimermanager().settimer(deadanimationtimerhandler, this, &amydamage::destroyenemy, 0.5f, false);
			}*/
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ramura de health"));
			//AMyDamage::DestroyEnemy();
		//	GameMode->RespawnPlayer();
		}

	}
	

}

void AMyDamage::CalculateDead()
{
	if (this->Health <= 0)
	{
		isDead = true;
	}
	else {
		isDead = false;
	}
}

//Calculate health
void AMyDamage::CalculateHealth(float Delta)
{
	
	//this->Health += Delta;
	UE_LOG(LogTemp, Warning, TEXT("Health reusit"));
//	this->CalculateDead();
}

void AMyDamage::DestroyEnemy()
{
	Cast<AActor>(this)->Destroy();
}