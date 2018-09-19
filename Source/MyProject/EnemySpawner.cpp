// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "MyEnemyAIController.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	this->MaxEnemies = 10;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AEnemySpawner::SpawnEnemy()
{
	TArray<AActor*> AllOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), AllOutActors);
	UE_LOG(LogTemp, Warning, TEXT("Spawning Now!"));
	if (AllOutActors.Num() < this->MaxEnemies) {

		FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(100.f, 100.f, 0.f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = "Ghita";
		//UKismetMathLibrary::RandomPointInBoundingBox(this->SpawnVolume->GetComponentLocation(), this->SpawnVolume->GetScaledBoxExtent());
		AEnemyCharacter * NewEnemy = GetWorld()->SpawnActor <AEnemyCharacter>(NewLocation, FRotator::ZeroRotator, SpawnParams);
		
		NewEnemy->SpawnDefaultController();

		
	}
}
