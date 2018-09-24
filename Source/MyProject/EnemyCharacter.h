// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"



UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	FTimerHandle DamageTimerHandler;


	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* EnemyMeshComponent;




	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	int32 Score;

	//UFUNCTION()
	//void AffectHealth_Implementation(float Delta);

	//FTimerHandle DeadAnimationTimerHandler;
	//void DestroyEnemy();


	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float EnemyFireRate;

	FTimerHandle MyEnemyTimerHandle;

	UFUNCTION()
	void FireBullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Character health
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
	float Health = 100;

	////Character dead status
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character")
	bool isDead = false;

	////Calculate health function(helper)
	//virtual void CalculateDead();

	//Calculate health
	//UFUNCTION(BlueprintCallable, Category = "Base Character")
	//virtual void CalculateHealth(float Delta);

#if WITH_EDITOR
	//Update heath logic after editing inside editor
	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


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
