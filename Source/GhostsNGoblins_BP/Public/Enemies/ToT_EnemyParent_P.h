// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToT_EnemyParent_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_EnemyParent_P : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToT_EnemyParent_P();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UMeshComponent* EnemyMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* CollisionCapsule;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/*
	 * Variables
	 */
	
	// Health related 
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth; 
	
	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth; 
	
	// Movement related
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	float EnemySpeed;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	bool IsMovingRight;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	bool IsMovingLeft;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	float EnemyGoalPatrolRight;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	float EnemyGoalPatrolLeft;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Movement")
	float LanePositionY;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	int MovementLane;
	
	// Combat Related
	UPROPERTY(EditAnywhere, Category = "Combat")
	float DamageToPlayer;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool TwoLaneAttack;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool CanAttack;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool JustHit;
	
	/*
	 * Melee attack 
	 */
	
	// Getting the player class (Must be set in Unreal)
	UPROPERTY(EditAnywhere, Category="Player")
	TSubclassOf<ACharacter> PlayerBlueprint; 
	
	// Creating the function
	UFUNCTION()
	void OnPlayerHit(UPrimitiveComponent* HitComponent, 
		AActor* HitActor, 
		UPrimitiveComponent* OtherComponent, 
		FVector NormalImpulse, 
		const FHitResult& Hit);
	
};
