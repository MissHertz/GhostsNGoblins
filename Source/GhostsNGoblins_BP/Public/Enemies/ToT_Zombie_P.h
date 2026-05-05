// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvents.h"
#include "ToT_EnemyParent_P.h"
#include "Components/BoxComponent.h"
#include "Components/StateTreeComponent.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TSubclassOf<AActor> GroundFire;
	
	
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
	 * Checking for player, currently not in use
	 */
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State Tree")
	// FGameplayTag ChaseEvent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Tree")
	UStateTreeComponent* EnemyStateTree; 
	
	// The detection function for the zombie
	// UFUNCTION()
	// void PlayerDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	// UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//
	// UFUNCTION()
	// void PlayerNotDetected(UPrimitiveComponent* OverlappedComp,
	//    AActor* OtherActor,
	//    UPrimitiveComponent* OtherComp,
	//    int32 OtherBodyIndex);
	
	/*
	 * Setting movement positions
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float DownGraveyardPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float DownGraveyardPointLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float UpperGraveyardPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float UpperGraveyardPointLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptGraveyardPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptGraveyardPointLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptStartPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptStartPointLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptMiddlePointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptMiddlePointLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptEndPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptEndPointLeft;
	
	
	
	UFUNCTION()
	void SetMovementBox();
	
	UFUNCTION()
	void SetMovementPositions();
	
	// Changing each interface function to run when gotten the message
	virtual void AtDownGraveyard_Implementation() override; 
	virtual void AtUpperGraveyard_Implementation() override;
	virtual void AtCryptGraveyard_Implementation() override;
	virtual void AtCryptStart_Implementation() override;
	virtual void AtCryptMiddle_Implementation() override;
	virtual void AtCryptEnd_Implementation() override;
};
