// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "MyProject.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectProjectile.h"
#include "MyEnemyAIController.h"
#include "MyProjectGameMode.h"
#include "kismet/KismetMathLibrary.h"



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
	

	this->EnemyMeshComponent->AttachTo(GetRootComponent()); //AttachTo deprat
	this->EnemyMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f,0.f));

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	EnemyFireSound = FireAudio.Object;

	this->AIControllerClass = AMyEnemyAIController::StaticClass();
	this->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	
	this->Score = 500;
	this->isDead = false;
	this->Health = 20;
	InitialLifeSpan = 0;
	EnemyFireRate = 0.5f;

}


								////calculate health function(helper)
								//void aenemycharacter::calculatedead()
								//{
								//if (this->health <= 0)
								//{
								//isdead = true;
								//}
								//else {
								//isdead = false;
								//}
								//}

								////calculate health
								//void aenemycharacter::calculatehealth(float delta)
								//{
								//this->health += delta;
								//this->calculatedead();
								//}

								//void aenemycharacter::affecthealth_implementation(float delta)
								//{
								//	this->calculatehealth(delta);

								//	if (this->isdead) {
		

								//		amyprojectgamemode * gamemode = cast<amyprojectgamemode>(ugameplaystatics::getgamemode(getworld()));
								//		gamemode->incrementscore(score);

								//		this->detachfromcontrollerpendingdestroy();

								//		if (!getworldtimermanager().istimeractive(deadanimationtimerhandler)) {
								//			getworldtimermanager().settimer(deadanimationtimerhandler, this, &aenemycharacter::destroyenemy, 0.5f, false);
								//		}
								//	}


								//}

								//void aenemycharacter::destroyenemy()
								//{
								//	destroy();
								//}




//#if WITH_EDITOR
////Update heath logic after editing inside editor
//void AEnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
//{
//	this->isDead = false;
//	this->Health = 20;
//
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//
//	this->CalculateDead();
//}
//#endif













void AEnemyCharacter::FireBullet()
{
	GetWorldTimerManager().SetTimer(MyEnemyTimerHandle, this,&AEnemyCharacter::CreateEnemyFireBullet, EnemyFireRate,true);
}


void AEnemyCharacter::CreateEnemyFireBullet()
{
	if (this->AIControllerClass == nullptr)
	{
		
		return;
	}
	FVector PlayerLocation = this->GetActorLocation();
	FRotator PlayerRotation = this->GetActorRotation();
	FVector ProjectileScale = FVector(1.5f, 1.5f, 1.5f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = PlayerLocation + UKismetMathLibrary::GetForwardVector(PlayerRotation) * 200.f;

		
	FTransform BulletTransfom = FTransform(PlayerRotation, SpawnLocation + UKismetMathLibrary::GetRightVector(PlayerRotation), ProjectileScale);
	AMyProjectProjectile* EnemyProjectile = GetWorld()->SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(), BulletTransfom, SpawnParams);
	EnemyProjectile->SetProjectileMaterial();

	
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


