// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_Zombie_P.h"

#include "StaticMeshSceneProxy.h"


// Sets default values
AToT_Zombie_P::AToT_Zombie_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OnTakeAnyDamage.AddDynamic(this, &AToT_Zombie_P::ZombieAttacked);
}

// Called when the game starts or when spawned
void AToT_Zombie_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_Zombie_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GetMesh()->OnComponentHit.AddDynamic(this, &AToT_Zombie_P::ZombieAttacked);
	
}

// Called to bind functionality to input
void AToT_Zombie_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AToT_Zombie_P::ZombieAttacked(AActor* DamagedActor, float Damage, 
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage; 
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("I have taken damage"));
	}
}

