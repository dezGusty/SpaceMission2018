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


//Movement
const FName AMyProjectPawn::MoveForwardBinding("MoveForward");
const FName AMyProjectPawn::MoveRightBinding("MoveRight");

//Firing
const FName AMyProjectPawn::FirePlayerBulletBinding("FirePlayerBullet");
const FName AMyProjectPawn::StopFireBulletBinding("StopFireBullet");

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
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	FireRate = 0.15f;
	
}

void AMyProjectPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction("FirePlayerBullet", IE_Pressed, this, &AMyProjectPawn::FireBullet);
	PlayerInputComponent->BindAction("StopFireBullet", IE_Released, this, &AMyProjectPawn::StopFireBullet);
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

			
	//if(PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	//PC->GetPawn()->SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), WorldLocation).Yaw, 0));
	//else
	//	UE_LOG(LogTemp, Error, TEXT("Error Getting hit result %s"), *FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), WorldLocation).Yaw, 0).ToString());


	
}
void AMyProjectPawn::StopFireBullet()
{
	GetWorldTimerManager().ClearTimer(MyTimerHandle);
}


//Spawn bullets
void AMyProjectPawn::CreateFireBullet()
{
	FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
	FRotator PlayerRotation = PC->GetPawn()->GetActorRotation();


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = PlayerLocation + UKismetMathLibrary::GetForwardVector(PlayerRotation) *100.f;

	//////////////////////////////////////////
	///////////////	TODO   //////////////////
	// De refactorizat spwanarea gloantelor multiple
	float offSetToRightFire[] = {25,-25,50,0,-50,50,25,-25,-50,50,25,0,-25,50};
	float offSetYawFire[] ={ 2,-2,};
	int NoOfBullets = 3;
	for (int i = 0; i < NoOfBullets; i++)
	{


	}

	PlayerRotation.Yaw += 2.f;
	FTransform BulletTransfom = FTransform(PlayerRotation, SpawnLocation, FVector::ZeroVector);
	PlayerRotation.Yaw += 2.f;
	FTransform BulletTransfom2 = FTransform(PlayerRotation, SpawnLocation + UKismetMathLibrary::GetRightVector(PlayerRotation) * 50.f, FVector::ZeroVector);
	PlayerRotation.Yaw -= 4.f;
	FTransform BulletTransfom3 = FTransform(PlayerRotation, SpawnLocation + UKismetMathLibrary::GetRightVector(PlayerRotation) * (-50.f), FVector::ZeroVector);

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		
		// spawn the projectile
		AMyProjectProjectile* NewProjectile = World->
			SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(), BulletTransfom, SpawnParams);
		AMyProjectProjectile* NewProjectile1 = World->
			SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(), BulletTransfom2, SpawnParams);
		AMyProjectProjectile* NewProjectile2 = World->
			SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(), BulletTransfom3, SpawnParams);

		NewProjectile->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		NewProjectile1->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		NewProjectile2->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	//////////////////////////////////////////////////////
	////////////// END  TODO /////////////////////////////

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

//Fire Bullets while LMButton is pressed
void AMyProjectPawn::FireBullet()
{
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &AMyProjectPawn::CreateFireBullet, FireRate, true);
}



void AMyProjectPawn::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		PC->CurrentMouseCursor = EMouseCursor::Crosshairs;
	}

}