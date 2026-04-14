// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementBlocks/ToT_DownGraveyard_P.h"


// Sets default values
AToT_DownGraveyard_P::AToT_DownGraveyard_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToT_DownGraveyard_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_DownGraveyard_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

