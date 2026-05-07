// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_FireWall_P.h"

#include "Components/BoxComponent.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"


// Sets default values
AToT_FireWall_P::AToT_FireWall_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Creating static mesh
	Firewall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Firewall"));
	
	// Creating the collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	FVector CollisionBoxLocation = FVector(295.f, 0.f, 220.f);
	CollisionBox->SetRelativeLocation(CollisionBoxLocation);
	
	// Setting up the root component of the actor
	RootComponent = Firewall;
	CollisionBox->SetupAttachment(RootComponent);
	
	// Creating the timeline
	FirewallTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FirewallTimeline"));
	
	// Binding collision box on overlap to on player overlap function
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_FireWall_P::OnPlayerOverlap);
	
}

// Called when the game starts or when spawned
void AToT_FireWall_P::BeginPlay()
{
	Super::BeginPlay();
	
	// Getting actors Z location, is needed for timeline movement
	ActorLocationZ = GetActorLocation().Z;
	
	// Setting up timeline
	FirewallDelegate.BindDynamic(this, &AToT_FireWall_P::FirewallTimelineUpdate);
	
	if (FirewallCurve)
	{
		FirewallTimeline->AddInterpFloat(FirewallCurve, FirewallDelegate);
	}
	
}

// Called every frame
void AToT_FireWall_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Timeline on update function
void AToT_FireWall_P::FirewallTimelineUpdate(float InValue)
{
	// Finding the new location to set
	float NewZLocation = ActorLocationZ + InValue;
	
	// Setting new location of firewall
	FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, NewZLocation);
	SetActorLocation(NewLocation, false);
}

// Not in use
void AToT_FireWall_P::FirewallTimelineEnded()
{
}

// On overlap with player 
void AToT_FireWall_P::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if overlapping actor is the player, starting timeline if true
	if (OtherActor and OtherActor->IsA(PlayerBlueprint))
	{
		if (FirewallTimeline)
		{
			FirewallTimeline->PlayFromStart();
		}
	}
}

