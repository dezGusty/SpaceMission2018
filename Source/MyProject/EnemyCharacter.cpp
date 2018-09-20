// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "MyEnemyAIController.h"
#include "MyProject.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter() 
	

{ 
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//create the mesh component for the enemy 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMesh(TEXT("/Game/TwinStick/Meshes/Enemy_Mesh.Enemy_Mesh"));
	
	EnemyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMeshComponent->SetStaticMesh(EnemyMesh.Object);
	EnemyMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	
	EnemyMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	EnemyMeshComponent->SetRelativeRotation(FRotator(0.f, 0.0f, 0.0f));
	UCapsuleComponent* EnemyCapsuleComponent = this->GetCapsuleComponent();
	
	
	this->EnemyMeshComponent->AttachTo(GetRootComponent());
	RootComponent = EnemyMeshComponent;

	this->AIControllerClass = AMyEnemyAIController::StaticClass();

	InitialLifeSpan = 0;

}






// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


}


