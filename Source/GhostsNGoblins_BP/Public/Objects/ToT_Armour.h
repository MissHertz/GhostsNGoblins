// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "GameFramework/Actor.h"
#include "ToT_Armour.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_Armour : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_Armour();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* Armour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChaosGameplayEventDispatcher* OnPickedUp;
	
	virtual void PickUp();
};
