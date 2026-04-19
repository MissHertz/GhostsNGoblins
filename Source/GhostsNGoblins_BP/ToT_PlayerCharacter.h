// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToT_PlayerCharacter.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToT_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleCameraSplineMovement(AActor CameraSplineReference);
	
	/*
	 * Setting all(most) variables
	 */
	
	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SwitchNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PositionClose;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PositionFar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CryptPositionClose;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CryptPositionFar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool HasSwitched;
	
	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int LifeCounter;
	
	// Actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
	bool FMPlayerMesh;
	
	// Menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	bool IsPauseMenuOpen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	bool GameWon;
	
	// Weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool HasWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool HasLance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int CurrentWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool WeaponCooldownOver;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float WeaponCooldownTime;
	
	// Projectiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectiles")
	AActor* LanceProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectiles")
	AActor* TorchProjectile;
	
	// Interactables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactables")
	bool EnteredCrypt;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactables")
	bool CryptKeyDropped;
	

};
