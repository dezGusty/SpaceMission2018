// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "MyProjectProjectile.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "MyProjectPawn.generated.h"

UCLASS(Blueprintable)
class AMyProjectPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	



public:
	AMyProjectPawn();
		
	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;



	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface



	/* Fire a shot in the specified direction */
	UFUNCTION()
	void FireBullet();

	/*Stop Firing on realease*/
	UFUNCTION()
	void StopFireBullet();

	//Create a bullet at a specified location
	UFUNCTION()
	void CreateFireBullet();


	// Static names for axis and actions bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FirePlayerBulletBinding;
	static const FName StopFireBulletBinding;


private:
	UInputComponent* InputComponent = nullptr;

	//Timer handle for automatically firing
	FTimerHandle MyTimerHandle;


public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

