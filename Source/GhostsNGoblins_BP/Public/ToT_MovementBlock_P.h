// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MovementBlocks/ToT_EnemyInMovementBlock.h"
#include "ToT_MovementBlock_P.generated.h"

class UBoxComponent;

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_MovementBlock_P : public AActor, public IToT_EnemyInMovementBlock
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_MovementBlock_P();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/*
	 * Player in box detection
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
	
	UFUNCTION()
	void OnOverlapEnd(
	   UPrimitiveComponent* OverlappedComp,
	   AActor* OtherActor,
	   UPrimitiveComponent* OtherComp,
	   int32 OtherBodyIndex
   );
	UPROPERTY(EditAnywhere, Category="Player")
	TSubclassOf<ACharacter> PlayerBlueprint; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	bool PlayerInBox = false; 
	
	/*
	 * Spawn enemies function
	 */
	UFUNCTION()
	void SpawnEnemies(float DeltaTime);
	
	UFUNCTION()
	void SpawnZombie();
	
	UFUNCTION()
	void SpawnBat();
	
	// Spawn variables
	UPROPERTY(EditAnywhere, Category="Spawner")
	float EnemySpawnTime;
	
	UPROPERTY()
	float EnemySpawnCooldown;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	int EnemySpawnRange; 
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	float DelaySpawnTimer; 
	
	UPROPERTY(EditAnywhere, Category="Spawn Actors")
	UClass* Zombie;
	
	UPROPERTY(EditAnywhere, Category="Spawn Actors")
	UClass* Bat;
	
	UPROPERTY(EditAnywhere, Category="Spawn Actors")
	float BatSpawnOffsetX; 
	
	UPROPERTY(EditAnywhere, Category="Spawn Actors")
	float BatSpawnOffsetZ; 
	
	UPROPERTY(EditAnywhere, Category="Spawn Actors")
	float ZombieSpawnOffsetX; 
	
	UPROPERTY(EditAnywhere, Category="Spawn Actors")
	float ZombieSpawnOffsetZ; 
	
	UPROPERTY()
	AToT_PlayerCharacter* Player; 

};
