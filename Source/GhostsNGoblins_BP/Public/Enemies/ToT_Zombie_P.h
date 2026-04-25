// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToT_EnemyParent_P.h"
#include "Components/BoxComponent.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"
#include "MovementBlocks/ToT_MovementBlocks_P.h"
#include "ToT_Zombie_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_Zombie_P : public AToT_EnemyParent_P, public IToT_MovementBlocks_P
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToT_Zombie_P();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	UBoxComponent* PlayerOverlapBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void ZombieAttacked(AActor* DamagedActor, float Damage, 
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* HitAnimation; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop Objects")
	UClass* DropKey; 
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	// UClass* Player;
	
	/*
	 * Setting movement positions
	 */
	UFUNCTION()
	void SetMovementBox();
	
	UFUNCTION()
	void SetMovementPositions();
	
	virtual void AtDownGraveyard_Implementation() override; 
	virtual void AtUpperGraveyard_Implementation() override;
	virtual void AtCryptGraveyard_Implementation() override;
	virtual void AtCryptStart_Implementation() override;
	virtual void AtCryptMiddle_Implementation() override;
	virtual void AtCryptEnd_Implementation() override;
	// virtual void EnemyInMovementBlock_Implementation(AActor* Executor) override;
	
	
	/*
	 * Checking for player
	 */
	
	UFUNCTION()
	void OnOverlapBegin(
	   UPrimitiveComponent* OverlappedComp,
	   AActor* OtherActor,
	   UPrimitiveComponent* OtherComp,
	   int32 OtherBodyIndex,
	   bool bFromSweep,
	   const FHitResult& SweepResult
   );
	
	/*
	 * Get player
	 */
	AToT_PlayerCharacter* Player;
	
	/*
	 * Zombie's own variables
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie Variables")
	int ZombiesToKill;
};
