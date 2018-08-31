// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPawn.h"
#include "MyProjectProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundBase.h"
#include "iostream"
#include <debug/DebugDrawService.h>


const FName AMyProjectPawn::MoveForwardBinding("MoveForward");
const FName AMyProjectPawn::MoveRightBinding("MoveRight");
const FName AMyProjectPawn::FireForwardBinding("FireForward");
const FName AMyProjectPawn::FireRightBinding("FireRight");
const FName AMyProjectPawn::FirePlayerBulletBinding("FirePlayerBullet");
FHitResult Result;
AMyPlayerController* PC = nullptr;

AMyProjectPawn::AMyProjectPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
}

void AMyProjectPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void AMyProjectPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	

	
	if (PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, Result))
		PC->GetPawn()->SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Result.Location).Yaw, 0));
	else
		UE_LOG(LogTemp, Error, TEXT("Error Getting hit result") );

	InputComponent = PC->GetPawn()->FindComponentByClass<UInputComponent>();
	InputComponent->BindAction("FirePlayerBullet", IE_Pressed, this, &AMyProjectPawn::FireBullet);
	
	


	
	//if(PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	//PC->GetPawn()->SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), WorldLocation).Yaw, 0));
	//else
	//	UE_LOG(LogTemp, Error, TEXT("Error Getting hit result %s"), *FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), WorldLocation).Yaw, 0).ToString());


	
}



void AMyProjectPawn::FireBullet( )
{
	// If we it's ok to fire again
	if (bCanFire == true)
	{
		
		FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
		FRotator PlayerRotation = PC->GetPawn()->GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
						
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = PlayerLocation + UKismetMathLibrary::GetForwardVector(PlayerRotation) *120.f;
		FTransform BulletTransfom = FTransform(PlayerRotation, SpawnLocation, FVector::ZeroVector);
		

		UWorld* const World = GetWorld();
		if (World != NULL)
		{	

			// spawn the projectile
			AMyProjectProjectile* NewProjectile = World->
					SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(),BulletTransfom, SpawnParams);
			NewProjectile->SetActorScale3D(FVector(1.5f,1.5f,1.5f));
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyProjectPawn::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
	

	}

	
}

void AMyProjectPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AMyProjectPawn::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<AMyPlayerController>(GetController());
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		PC->CurrentMouseCursor = EMouseCursor::Crosshairs;
	}


}