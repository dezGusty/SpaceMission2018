// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPawn.h"
#include "MyPlayerController.h"
#include "MyProjectProjectile.h"
#include "MyProjectGameMode.h"
#include "Kismet/GameplayStatics.h"




//Movement
const FName AMyProjectPawn::MoveForwardBinding("MoveForward");
const FName AMyProjectPawn::MoveRightBinding("MoveRight");

//Firing
const FName AMyProjectPawn::FirePlayerBulletBinding("FirePlayerBullet");
const FName AMyProjectPawn::StopFireBulletBinding("StopFireBullet");

FHitResult Result;
APlayerController* PC;

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
	//Health
	this->Health = 100.0f;



	
}

void AMyProjectPawn::AffectHealth_Implementation(float Delta)
{
	this->Health += Delta;
	
	if (this->Health <= 0)
	{
		AMyProjectGameMode* GameMode = Cast<AMyProjectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RespawnPlayer();
		
	}


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
	//PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC != nullptr)
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
			UE_LOG(LogTemp, Error, TEXT("Error Getting hit result"));


		//if(PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		//PC->GetPawn()->SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), WorldLocation).Yaw, 0));
		//else
		//	UE_LOG(LogTemp, Error, TEXT("Error Getting hit result %s"), *FRotator(0, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), WorldLocation).Yaw, 0).ToString());
	}
	else 
		UE_LOG(LogTemp, Error, TEXT("MyProjectPawn Tick PC is null"));
}


void AMyProjectPawn::StopFireBullet()
{
	GetWorldTimerManager().ClearTimer(MyTimerHandle);
}



//Spawn bullets
void AMyProjectPawn::CreateFireBullet()
{
	if(PC==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PC is null ptr"));
		return;
	}
	FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
	FRotator PlayerRotation = PC->GetPawn()->GetActorRotation();
	FVector ProjectileScale = FVector(1.5f, 1.5f, 1.5f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = PlayerLocation + UKismetMathLibrary::GetForwardVector(PlayerRotation) *100.f;


	// This number must be obtained from the game instance
	int noOfBullets = 5;


	float* offSetToRightFire =  new float[noOfBullets]();

	switch (noOfBullets)
	{
	case 1: offSetToRightFire[0] = 0.f;
			break;
	case 2: offSetToRightFire[0] = -50.f;
			offSetToRightFire[1] = 50.f;
			break;
	case 3:	offSetToRightFire[0] = -50.f;
			offSetToRightFire[1] = 0.f;
			offSetToRightFire[2] = 50.f;
			break;
	case 4: offSetToRightFire[0] = -100.f;
			offSetToRightFire[1] = -50.f;
			offSetToRightFire[2] = 50.f;
			offSetToRightFire[3] = 100.f;
			break;
	case 5: offSetToRightFire[0] = -100.f;
			offSetToRightFire[1] = -50.f;
			offSetToRightFire[2] = 0.f;
			offSetToRightFire[3] = 50.f;
			offSetToRightFire[4] = 100.f;
			break;
	default:
		break;
	}
	for (int i = 0; i < noOfBullets; i++)
	{	
		FTransform BulletTransfom = FTransform(PlayerRotation, SpawnLocation + UKismetMathLibrary::GetRightVector(PlayerRotation) *offSetToRightFire[i], ProjectileScale);
		GetWorld()->SpawnActor<AMyProjectProjectile>(AMyProjectProjectile::StaticClass(), BulletTransfom, SpawnParams);
		PlayerRotation.Yaw += 2;
	
	}



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
	UE_LOG(LogTemp, Warning, TEXT("MyProjectPawn BeginPlay"));
	Super::BeginPlay();
	
	PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		PC->CurrentMouseCursor = EMouseCursor::Crosshairs;
	}

}