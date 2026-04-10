// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostsNGoblins_BP/Public/ToT_MovementBlock_P.h"

#include "Components/BoxComponent.h"


// Sets default values
AToT_MovementBlock_P::AToT_MovementBlock_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_MovementBlock_P::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AToT_MovementBlock_P::OnOverlapEnd);
	
	PlayerInBox = false; 
	
}

// Called when the game starts or when spawned
void AToT_MovementBlock_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_MovementBlock_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_MovementBlock_P::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor and OtherActor->IsA(PlayerBlueprint))
	{
		PlayerInBox = true;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Player entered box"));
	}
}

void AToT_MovementBlock_P::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor and OtherActor->IsA(PlayerBlueprint))
	{
		PlayerInBox = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Player left box"));
	}
}

void AToT_MovementBlock_P::SpawnEnemies()
{
	if (PlayerInBox == true)
	{
		
	}
}

