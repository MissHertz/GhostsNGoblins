// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ToT_WaterCollider_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_WaterCollider_P : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_WaterCollider_P();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<ACharacter> PlayerBlueprint; 
	
	UFUNCTION()
	void PlayerOverlapping(UPrimitiveComponent* OverlappedComp,
	   AActor* OtherActor,
	   UPrimitiveComponent* OtherComp,
	   int32 OtherBodyIndex,
	   bool bFromSweep,
	   const FHitResult& SweepResult);
};
