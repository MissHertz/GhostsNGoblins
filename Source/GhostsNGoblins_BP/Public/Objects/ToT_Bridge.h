// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ToT_Interact_P.h"
#include "ToT_Bridge.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_Bridge : public AActor, public IToT_Interact_P
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_Bridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Bridge;
	
	/*UPROPERTY(EditAnywhere, Category = "Interfaces")
	TScriptInterface<UInterface> BPI_Interact;*/
	
	// Function from Interface Interact
	virtual void Rotate_Implementation() override;
};
