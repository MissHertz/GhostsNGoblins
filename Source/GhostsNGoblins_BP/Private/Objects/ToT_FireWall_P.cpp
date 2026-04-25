// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_FireWall_P.h"

#include "Components/BoxComponent.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"


// Sets default values
AToT_FireWall_P::AToT_FireWall_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Firewall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Firewall"));
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	FVector CollisionBoxLocation = FVector(295.f, 0.f, 220.f);
	CollisionBox->SetRelativeLocation(CollisionBoxLocation);
	FVector CollisionBoxTransform = FVector(0.2, 5.f, 3.f);
	CollisionBox->SetRelativeScale3D(CollisionBoxTransform);
	
	RootComponent = Firewall;
	
	FirewallTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FirewallTimeline"));
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_FireWall_P::OnPlayerOverlap);
	
}

// Called when the game starts or when spawned
void AToT_FireWall_P::BeginPlay()
{
	Super::BeginPlay();
	
	ActorLocationZ = GetActorLocation().Z;
	
	FirewallDelegate.BindDynamic(this, &AToT_FireWall_P::FirewallTimelineUpdate);
	//FirewallTimelineOver.BindDynamic(this, &AToT_FireWall_P::FirewallTimelineEnded);
	
	if (FirewallCurve)
	{
		FirewallTimeline->AddInterpFloat(FirewallCurve, FirewallDelegate);
		//FirewallTimeline->SetTimelineFinishedFunc(FirewallTimelineOver);
	}
	
}

// Called every frame
void AToT_FireWall_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_FireWall_P::FirewallTimelineUpdate(float InValue)
{
	float NewZLocation = ActorLocationZ + InValue;
	
	FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, NewZLocation);
	SetActorLocation(NewLocation, false);
}

void AToT_FireWall_P::FirewallTimelineEnded()
{
}

void AToT_FireWall_P::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor and OtherActor->IsA(PlayerBlueprint))
	{
		if (FirewallTimeline)
		{
			FirewallTimeline->PlayFromStart();
		}
	}
}

