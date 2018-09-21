// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "MyEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemySpawner::AEnemySpawner() 
		: AActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor EnemySpawner"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = this->SpawnVolume;
	

	this->MaxEnemies = 10;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("EnemySpawner BeginPlay"));
	Super::BeginPlay();

}

 //Called every frame
void AEnemySpawner::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);


}

void AEnemySpawner::SpawnEnemy()

{
	UE_LOG(LogTemp, Warning, TEXT("EnemySpawner Spawn Enemy function"));
	TArray<AActor*> AllOutActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), AllOutActors);
	UE_LOG(LogTemp, Warning, TEXT("Spawning Now!"));

	
	if (AllOutActors.Num() < this->MaxEnemies)
	{
		FVector NewLocation =
			//GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() +
			UKismetMathLibrary::RandomPointInBoundingBox(this->SpawnVolume->GetComponentLocation(), this->SpawnVolume->GetScaledBoxExtent());

		//FVector(100.f, 100.f, 0.f);
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Name = "Ghita";

		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEnemyCharacter* NewEnemy = GetWorld()->SpawnActor <AEnemyCharacter>(NewLocation, FRotator::ZeroRotator, SpawnParams);

		NewEnemy->SpawnDefaultController();
		
		NewEnemy->FireBullet();
		
	}
		
	
}
