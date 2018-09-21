// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemyAIController.h"
#include "MyProjectPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyCharacter.generated.h"


class UFloatingPawnMovement;

UCLASS(config=game)
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* EnemyMovementComponent;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* EnemyMeshComponent;

	// Sets default values for this character's properties
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	FLinearColor EnemyColor;
*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	AMyProjectPawn * Hero;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float EnemyFireRate;

	FTimerHandle MyEnemyTimerHandle;

	UFUNCTION()
	void FireBullet();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE class UStaticMeshComponent* GetEnemyMeshComponent() const { return EnemyMeshComponent; }

	UFUNCTION()
	void CreateEnemyFireBullet();

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* EnemyFireSound;
	
};
