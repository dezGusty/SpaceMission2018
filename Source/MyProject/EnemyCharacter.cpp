// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "MyPlayerController.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

AMyEnemyAIController* EPC = nullptr;
AMyEnemyAIController* EPCC = nullptr;
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//create the mesh component for the enemy 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	EnemyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	RootComponent = EnemyMeshComponent;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	EPCC = Cast<AMyEnemyAIController>(this->GetController());
	EPC = Cast<AMyEnemyAIController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get player location
	FVector ShipLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	////Set enemy location to player location
	//--cu asta se misca suprapus cu nava noastra
	//SetActorLocation(ShipLocation);

	//aici am incercat sa folosesc functia asta din AI, dar da crash programul-- de studiat daca se ia bine actorul care trebuie urmarit si daca controller-ul AI ia ce trebuie
	EPCC->MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
	//EPC->MoveToLocation(ShipLocation);


}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

