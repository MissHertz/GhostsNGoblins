// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementBlocks/ToT_CryptGraveyard_P.h"

#include "MovementBlocks/ToT_MovementBlocks_P.h"


// Sets default values
AToT_CryptGraveyard_P::AToT_CryptGraveyard_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToT_CryptGraveyard_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_CryptGraveyard_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_CryptGraveyard_P::EnemyInMovementBlock_Implementation(AActor* Executor)
{
	Super::EnemyInMovementBlock_Implementation(Executor);
	
	if (Executor->GetClass()->ImplementsInterface(UToT_MovementBlocks_P::StaticClass()))
	{
		IToT_MovementBlocks_P::Execute_AtCryptGraveyard(Executor);
	}
}

