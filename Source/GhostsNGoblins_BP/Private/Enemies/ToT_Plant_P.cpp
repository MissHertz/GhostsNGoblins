// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_Plant_P.h"


// Sets default values
AToT_Plant_P::AToT_Plant_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OnTakeAnyDamage.AddDynamic(this, &AToT_Plant_P::PlantAttacked);
}

// Called when the game starts or when spawned
void AToT_Plant_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_Plant_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AToT_Plant_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Plant attacked function
void AToT_Plant_P::PlantAttacked(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	// Checking if current health is more than zero, taking damage if true
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0)
		 {
			this->Destroy(); 
		 }
	}
}

