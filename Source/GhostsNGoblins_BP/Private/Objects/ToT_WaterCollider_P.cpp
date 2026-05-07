// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_WaterCollider_P.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_WaterCollider_P::AToT_WaterCollider_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Creating the collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisonBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetRelativeScale3D(FVector(1.f, 1.f, 0.3));
	
	// Binding collision box on overlap to on player overlap function
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_WaterCollider_P::PlayerOverlapping);
	
	// Setting default damage value
	Damage = 2; 
}

// Called when the game starts or when spawned
void AToT_WaterCollider_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_WaterCollider_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// On player overlapping function
void AToT_WaterCollider_P::PlayerOverlapping(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if overlapping actor is the player, if true applying damage to player
	if (OtherActor->IsA(PlayerBlueprint))
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

