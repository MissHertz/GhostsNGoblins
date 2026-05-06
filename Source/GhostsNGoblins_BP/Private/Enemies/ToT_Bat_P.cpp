// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_Bat_P.h"

#include "ToT_MovementBlock_P.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AToT_Bat_P::AToT_Bat_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Presetting the Z movement postion
	MovementPosZ = -500;
	
	// Binding any damage to bat attacked function
	OnTakeAnyDamage.AddDynamic(this, &AToT_Bat_P::BatAttacked);
	
	// Setting up collision sphere for taking damage check
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(45.f);
	
	// Setting up patrol point variables
	DownGraveyardPointRight = 8090.f;
	DownGraveyardPointLeft = 3570.f;
	DownGraveyardPointZ = -500.f;
	
	UpperGraveyardPointRight = 13600.f;
	UpperGraveyardPointLeft = 8800.f;
	UpperGraveyardPointZ = -230.f;
	
	CryptGraveyardPointRight = 16050.f;
	CryptGraveyardPointLeft = 14450.f;
	CryptGraveyardPointZ = -300.f;
	
	CryptStartPointRight = 7050.f;
	CryptStartPointLeft = 5040.f;
	CryptStartPointZ = -1700.f;
	
	CryptMiddlePointRight = 10850.f;
	CryptMiddlePointLeft = 7830.f;
	CryptMiddlePointZ = -1830.f;
	
	CryptEndPointRight = 14030.f;
	CryptEndPointLeft = 12530.f;
	CryptEndPointZ = -2100.f;
}

// Called when the game starts or when spawned
void AToT_Bat_P::BeginPlay()
{
	Super::BeginPlay();
	
	// Setting lane and patrol points
	SetMovementPositions();
	SetMovementBlocks();
	
	// Setting movement mode to flying
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

// Called every frame
void AToT_Bat_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AToT_Bat_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Bat attacked function
void AToT_Bat_P::BatAttacked(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	// Creating an actor array to get overlapping actors in the collision sphere
	TArray<AActor*> ActorArray;
	CollisionSphere->GetOverlappingActors(ActorArray);
	
	// Checking if it is the collision sphere that is hit and that it is the player weapon, taking damage if true
	for (AActor* OverlappingActor : ActorArray)
	{
		if (Weapon and OverlappingActor->IsA(Weapon))
		{
			if (CurrentHealth > 0)
			{
				CurrentHealth -= Damage;
				if (CurrentHealth <= 0)
				{
					this->Destroy(); 
				}
			}
		}
	}
}

// Setting the lane position, destroying bat if it is not in a correct lane
void AToT_Bat_P::SetMovementPositions()
{
	FVector BatPosition = GetActorLocation();
	if (BatPosition.Y == 150)
	{
		LanePositionY = 150;
	}
	else if (BatPosition.Y == -100)
	{
		LanePositionY = -100;
	}
	else if (BatPosition.Y == 1700)
	{
		LanePositionY = 1700;
	}
	else if (BatPosition.Y == 1450)
	{
		LanePositionY = 1450;
	}
	else
	{
		this->Destroy();
	}
	
}

// Setting patrol points by sending message to the overlapping movement block
void AToT_Bat_P::SetMovementBlocks()
{
	// Creating the array for the overlapping actors
	TArray<AActor*> OverlappingActors;
	// Looks only for actors in a specific class to help the process be easier
	TSubclassOf<AToT_MovementBlock_P> SearchingClass;
	
	// Getting the overlapping actors of the specific class
	GetOverlappingActors(OverlappingActors, SearchingClass);
	
	// Sends the interface message to all of the actors that has the interface (should only be one)
	for (AActor* OverlappingActor :  OverlappingActors)
	{
		if (OverlappingActor->GetClass()->ImplementsInterface(UToT_EnemyInMovementBlock::StaticClass()))
		{
			IToT_EnemyInMovementBlock::Execute_EnemyInMovementBlock(OverlappingActor, this);
		}
	}
}

/*
 * Setting patrol positions
 */ 
void AToT_Bat_P::AtDownGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtDownGraveyard_Implementation();
	EnemyGoalPatrolRight = DownGraveyardPointRight;
	EnemyGoalPatrolLeft = DownGraveyardPointLeft;
	MovementPosZ = DownGraveyardPointZ;
}

void AToT_Bat_P::AtUpperGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtUpperGraveyard_Implementation();
	EnemyGoalPatrolRight = UpperGraveyardPointRight;
	EnemyGoalPatrolLeft = UpperGraveyardPointLeft;
	MovementPosZ = UpperGraveyardPointZ;
}

void AToT_Bat_P::AtCryptGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtCryptGraveyard_Implementation();
	EnemyGoalPatrolRight = CryptGraveyardPointRight;
	EnemyGoalPatrolLeft = CryptGraveyardPointLeft;
	MovementPosZ = CryptGraveyardPointZ;
}

void AToT_Bat_P::AtCryptStart_Implementation()
{
	IToT_MovementBlocks_P::AtCryptStart_Implementation();
	EnemyGoalPatrolRight = CryptStartPointRight;
	EnemyGoalPatrolLeft = CryptStartPointLeft;
	MovementPosZ = CryptStartPointZ;
}

void AToT_Bat_P::AtCryptMiddle_Implementation()
{
	IToT_MovementBlocks_P::AtCryptMiddle_Implementation();
	EnemyGoalPatrolRight = CryptMiddlePointRight;
	EnemyGoalPatrolLeft = CryptMiddlePointLeft;
	MovementPosZ = CryptMiddlePointZ;
}

void AToT_Bat_P::AtCryptEnd_Implementation()
{
	IToT_MovementBlocks_P::AtCryptEnd_Implementation();
	EnemyGoalPatrolRight = CryptEndPointRight;
	EnemyGoalPatrolLeft = CryptEndPointLeft;
	MovementPosZ = CryptEndPointZ;
}

