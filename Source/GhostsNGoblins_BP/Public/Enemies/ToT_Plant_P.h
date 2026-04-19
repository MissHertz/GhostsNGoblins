// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToT_EnemyParent_P.h"
#include "ToT_Plant_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_Plant_P : public AToT_EnemyParent_P
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToT_Plant_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void PlantAttacked(AActor* DamagedActor, 
		float Damage, 
		const class UDamageType* DamageType, 
		class AController* InstigatedBy, 
		AActor* DamageCauser);
};
