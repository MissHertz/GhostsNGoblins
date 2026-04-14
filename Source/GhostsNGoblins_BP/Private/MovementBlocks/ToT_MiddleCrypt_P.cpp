// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementBlocks/ToT_MiddleCrypt_P.h"

#include "MovementBlocks/ToT_MovementBlocks_P.h"


// Sets default values
AToT_MiddleCrypt_P::AToT_MiddleCrypt_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToT_MiddleCrypt_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_MiddleCrypt_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_MiddleCrypt_P::EnemyInMovementBlock_Implementation(AActor* Executor)
{
	Super::EnemyInMovementBlock_Implementation(Executor);
	
	if (Executor->GetClass()->ImplementsInterface(UToT_MovementBlocks_P::StaticClass()))
	{
		IToT_MovementBlocks_P::Execute_AtCryptMiddle(Executor);
	}
}

