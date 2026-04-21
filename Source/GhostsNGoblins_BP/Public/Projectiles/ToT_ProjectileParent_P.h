// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ToT_ProjectileParent_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_ProjectileParent_P : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_ProjectileParent_P();
	
	// Properties of the actor
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Projectile;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionSphere;
	
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Reference to the Enemy blueprint (not the enemy directly)
	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<ACharacter> EnemyBlueprint;
	
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float WeaponDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ExsistanceTime;
	
	// Function for when the projectile hits the enemy
	void HitEnemy(UPrimitiveComponent* HitComponent, AActor* HitActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
