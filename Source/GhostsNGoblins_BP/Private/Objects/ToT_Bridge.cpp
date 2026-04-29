// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_Bridge.h"


// Sets default values
AToT_Bridge::AToT_Bridge()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToT_Bridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_Bridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

