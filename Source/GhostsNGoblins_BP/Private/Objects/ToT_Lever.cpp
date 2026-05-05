// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_Lever.h"

#include "Kismet/GameplayStatics.h"
#include "Objects/ToT_Bridge.h"


// Sets default values
AToT_Lever::AToT_Lever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Mesh setup
	Lever = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	RootComponent = Lever;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
}

// Called when the game starts or when spawned
void AToT_Lever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_Lever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_Lever::InteractCPP_Implementation(ACharacter* CharacterInstigator)
{
	// Rotates the Lever actor
	FRotator LeverRotation = FRotator(45.0, 0.0, 0.0);
	this->AddActorWorldRotation(LeverRotation);
	
	TArray<AActor*> Bridges;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AToT_Bridge::StaticClass(),
		Bridges);
	
	// Sends a message through Interact interface to rotate the bridge
	for (AActor* CurrentBridge:Bridges)
	{
		if (CurrentBridge && CurrentBridge->GetClass()->ImplementsInterface(UToT_Interact_P::StaticClass()))
		{
			IToT_Interact_P::Execute_RotateCPP(CurrentBridge);
		}
	}
}

