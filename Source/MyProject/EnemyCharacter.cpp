// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "MyEnemyAIController.h"
#include "MyProjectPawn.h"
#include "MyProject.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectProjectile.h"


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
	
	EnemyMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.f));
	EnemyMeshComponent->SetRelativeRotation(FRotator(0.f, 0.0f, 0.0f));
		
	RootComponent = EnemyMeshComponent;

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	EnemyFireSound = FireAudio.Object;

	this->AIControllerClass = AMyEnemyAIController::StaticClass();
	this->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	InitialLifeSpan = 0;
	EnemyFireRate = 0.5f;

}

void AEnemyCharacter::FireBullet()
{
	GetWorldTimerManager().SetTimer(MyEnemyTimerHandle, this,&AEnemyCharacter::CreateEnemyFireBullet, EnemyFireRate,true);
}


void AEnemyCharacter::CreateEnemyFireBullet()
{
	if (this->AIControllerClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PC is null ptr"));
		return;
	}
	FVector PlayerLocation = this->GetActorLocation();
	FRotator PlayerRotation = this->GetActorRotation();
	FVector ProjectileScale = FVector(1.5f, 1.5f, 1.5f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = PlayerLocation + UKismetMathLibrary::GetForwardVector(PlayerRotation) *100.f;

		
	FTransform BulletTransfom = FTransform(PlayerRotation, SpawnLocation + UKismetMathLibrary::GetRightVector(PlayerRotation), ProjectileScale);
	AMyProjectProjectile* EnemyProjectile = GetWorld()->SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(), BulletTransfom, SpawnParams);
	EnemyProjectile->SetProjectileMaterial();
	PlayerRotation.Yaw += 2;
	
	// try and play the sound if specified
	if (AEnemyCharacter::EnemyFireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EnemyFireSound, GetActorLocation());
	}
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


