// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_Armour.h"

#include "Components/BoxComponent.h"


// Sets default values
AToT_Armour::AToT_Armour()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Armour = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Armour;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	//OnPickedUp = CreateDefaultSubobject<UChaosGameplayEventDispatcher>(TEXT("EventDispatcher"));
}

// Called when the game starts or when spawned
void AToT_Armour::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_Armour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_Armour::PickUp()
{
	//CollisionBox->OnComponentBeginOverlap;
}

