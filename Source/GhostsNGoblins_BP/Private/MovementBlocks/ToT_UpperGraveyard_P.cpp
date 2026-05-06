// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementBlocks/ToT_UpperGraveyard_P.h"

#include "MovementBlocks/ToT_MovementBlocks_P.h"


// Sets default values
AToT_UpperGraveyard_P::AToT_UpperGraveyard_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToT_UpperGraveyard_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_UpperGraveyard_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Getting and sending interface message
void AToT_UpperGraveyard_P::EnemyInMovementBlock_Implementation(AActor* Executor)
{
	Super::EnemyInMovementBlock_Implementation(Executor);
	if (Executor->GetClass()->ImplementsInterface(UToT_MovementBlocks_P::StaticClass()))
	{
		IToT_MovementBlocks_P::Execute_AtUpperGraveyard(Executor);
	}
}

