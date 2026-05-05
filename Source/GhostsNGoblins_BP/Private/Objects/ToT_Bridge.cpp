// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_Bridge.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_Bridge::AToT_Bridge()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Bridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bridge"));
	RootComponent = Bridge;
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

void AToT_Bridge::RotateCPP_Implementation()
{	
	// Code for the bridge with tag "Right"
	TArray<AActor*> RightBridges;
	UGameplayStatics::GetAllActorsOfClassWithTag(
		GetWorld(),
		AToT_Bridge::StaticClass(),
		FName("Right"),
		RightBridges);

	for (auto CurrentRightBridge : RightBridges)
	{
	if (CurrentRightBridge)
	{
		USceneComponent* Root = CurrentRightBridge->GetRootComponent();
		
		if (Root)
		{
			FRotator Current = Root->GetComponentRotation();
			FRotator BridgeRotation = FRotator(-90.0,Current.Yaw,Current.Roll);
			Root->SetWorldRotation(BridgeRotation);
		}
	}
	}
	
	// Code for the bridge with tag "Left"
	TArray<AActor*> LeftBridges;
	UGameplayStatics::GetAllActorsOfClassWithTag(
		GetWorld(),
		AToT_Bridge::StaticClass(),
		FName("Left"),
		LeftBridges);

	for (auto CurrentLeftBridge : LeftBridges)
	{
		if (CurrentLeftBridge)
		{
			USceneComponent* Root = CurrentLeftBridge->GetRootComponent();
		
			if (Root)
			{
				FRotator Current = Root->GetComponentRotation();
				FRotator BridgeRotation = FRotator(-90.0,Current.Yaw,Current.Roll);
				Root->SetWorldRotation(BridgeRotation);
			}
		}
	}
}

