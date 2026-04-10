// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "ToT_MovementBlock_P.generated.h"

class UBoxComponent;

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_MovementBlock_P : public AActor
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
	
	UFUNCTION()
	void SpawnEnemies();
	
	
	int EnemiesInBox = 0;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	int EnemySpawn;
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	int EnemySpawnRange = 2; 
	
	UPROPERTY(EditAnywhere, Category="Spawner")
	float DelaySpawnTimer = 2.f; 
	
};
