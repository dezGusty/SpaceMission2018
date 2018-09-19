// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemyAIController.h"
#include "MyProjectPawn.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* EnemyMeshComponent;

	// Sets default values for this character's properties
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	FLinearColor EnemyColor;
*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	AMyProjectPawn * Hero;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE class UStaticMeshComponent* GetEnemyMeshComponent() const { return EnemyMeshComponent; }

	
	
};
