// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToT_ProjectileParent_P.h"
#include "ToT_ProjectileGrave_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_ProjectileGrave_P : public AToT_ProjectileParent_P
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_ProjectileGrave_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

