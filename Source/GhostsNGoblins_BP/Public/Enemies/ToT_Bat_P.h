// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToT_EnemyParent_P.h"
#include "MovementBlocks/ToT_MovementBlocks_P.h"
#include "Projectiles/ToT_ProjectileParent_P.h"
#include "ToT_Bat_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_Bat_P : public AToT_EnemyParent_P, public IToT_MovementBlocks_P
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToT_Bat_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Movement")
	float MovementPosZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TSubclassOf<AToT_ProjectileParent_P> Weapon;
	
	UFUNCTION()
	void BatAttacked(AActor* DamagedActor, 
		float Damage, 
		const class UDamageType* DamageType, 
		class AController* InstigatedBy, 
		AActor* DamageCauser);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float DownGraveyardPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float DownGraveyardPointLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float DownGraveyardPointZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float UpperGraveyardPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float UpperGraveyardPointLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float UpperGraveyardPointZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptGraveyardPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptGraveyardPointLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptGraveyardPointZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptStartPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptStartPointLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptStartPointZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptMiddlePointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptMiddlePointLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptMiddlePointZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptEndPointRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptEndPointLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol points")
	float CryptEndPointZ;
	
	
	UFUNCTION()
	void SetMovementPositions();
	void SetMovementBlocks();
	
	virtual void AtDownGraveyard_Implementation() override; 
	virtual void AtUpperGraveyard_Implementation() override;
	virtual void AtCryptGraveyard_Implementation() override;
	virtual void AtCryptStart_Implementation() override;
	virtual void AtCryptMiddle_Implementation() override;
	virtual void AtCryptEnd_Implementation() override;
};
