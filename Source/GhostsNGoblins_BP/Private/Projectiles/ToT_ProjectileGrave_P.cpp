// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ToT_ProjectileGrave_P.h"


// Sets default values
AToT_ProjectileGrave_P::AToT_ProjectileGrave_P()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AToT_ProjectileGrave_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_ProjectileGrave_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

