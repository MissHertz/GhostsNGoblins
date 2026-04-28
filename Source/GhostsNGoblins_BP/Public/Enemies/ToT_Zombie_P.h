// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToT_EnemyParent_P.h"
#include "Components/BoxComponent.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"
#include "MovementBlocks/ToT_MovementBlocks_P.h"
#include "Projectiles/ToT_ProjectileParent_P.h"
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
	
	/*
	 * Zombie's own variables
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie Variables")
	int ZombiesToKill;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie Variables")
	float AnimationTime;
	
	UPROPERTY()
	float AnimTimeCounter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TSubclassOf<AToT_ProjectileParent_P> Weapon;
	
	
	/*
	 * Getting player
	 */
	AToT_PlayerCharacter* Player;
	
	
	/*
	 * Zombie hit and/or killed functions an properties
	 */
	// Function for zombie taking damage
	UFUNCTION()
	void ZombieAttacked(AActor* DamagedActor, float Damage, 
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	// The animation that plays when the zombie is hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* HitAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* DieAnimation;
	
	
	// The key the zombie can drop when killed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop Objects")
	UClass* DropKey; 
	
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
	
	/*
	 * Checking for player, currently not in use
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
	
};
