// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_Zombie_P.h"

#include "StaticMeshSceneProxy.h"
#include "ToT_MovementBlock_P.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MovementBlocks/ToT_EnemyInMovementBlock.h"


// Sets default values
AToT_Zombie_P::AToT_Zombie_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerOverlapBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//PlayerOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_Zombie_P::OnOverlapBegin);
	
	OnTakeAnyDamage.AddDynamic(this, &AToT_Zombie_P::ZombieAttacked);
}

// Called when the game starts or when spawned
void AToT_Zombie_P::BeginPlay()
{
	Super::BeginPlay();
	SetMovementPositions();
	SetMovementBox();
	
}

// Called every frame
void AToT_Zombie_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GetMesh()->OnComponentHit.AddDynamic(this, &AToT_Zombie_P::ZombieAttacked);
	
}

// Called to bind functionality to input
void AToT_Zombie_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AToT_Zombie_P::ZombieAttacked(AActor* DamagedActor, float Damage, 
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage; 
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("I have taken damage"));
		PlayAnimMontage(HitAnimation, 1.f, FName("Default"));
		if (CurrentHealth <= 0)
		{
			// TArray<AActor*> Actors;
			// UGameplayStatics::GetAllActorsOfClass(GetWorld(), AToT_PlayerCharacter::StaticClass(), Actors);
			// for (AActor* Actor : Actors)
			// {
			// 	if (Actor.)
			// }
			
			// Spawning key, currently every zombie does this
			FVector ZombieLocation = this->GetActorLocation();
			FRotator Rotation = FRotator(0, 0, 0);
			FActorSpawnParameters SpawnParameters;
			GetWorld()->SpawnActor<AActor>(DropKey, ZombieLocation, Rotation, SpawnParameters);
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Actor destroyed"));
			this->Destroy();
		}
	}
}

// Sending message to the movement block the enemy spawns in
void AToT_Zombie_P::SetMovementBox()
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
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Sending Message to movement box"));
			IToT_EnemyInMovementBlock::Execute_EnemyInMovementBlock(OverlappingActor, this);
		}
	}
}

void AToT_Zombie_P::SetMovementPositions()
{
	FVector ZombiePosition = GetActorLocation();
	if (ZombiePosition.Y == 150)
	{
		//MovementLane = 0; 
		LanePositionY = 150;
	}
	else if (ZombiePosition.Y == -100)
	{
		//MovementLane = 1;
		LanePositionY = -100;
	}
	else if (ZombiePosition.Y == 1700)
	{
		//MovementLane = 2;
		LanePositionY = 1700;
	}
	else if (ZombiePosition.Y == 1450)
	{
		//MovementLane = 3;
		LanePositionY = 1450;
	}
	else
	{
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("No lane position"));
		}
	}
	// else
	// {
	// 	MovementLane = 0; 
	// }
	
	// switch (MovementLane)
	// {
	// case 0:
	// 	LanePositionY = 150;
	// 	break; 
	// case 1:
	// 	LanePositionY = -100;
	// 	break; 
	// case 2:
	// 	LanePositionY = 1700;
	// 	break; 
	// case 3:
	// 	LanePositionY = 1450; 
	// 	break;
	// default: 
	// 	LanePositionY = 150;
	// 	break; 
	// }
}

void AToT_Zombie_P::AtDownGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtDownGraveyard_Implementation();
	EnemyGoalPatrolRight = 8090.f;
	EnemyGoalPatrolLeft = 3570.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtUpperGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtUpperGraveyard_Implementation();
	EnemyGoalPatrolRight = 13600.f;
	EnemyGoalPatrolLeft = 8800.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtCryptGraveyard_Implementation();
	EnemyGoalPatrolRight = 16050.f;
	EnemyGoalPatrolLeft = 14450.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptStart_Implementation()
{
	IToT_MovementBlocks_P::AtCryptStart_Implementation();
	EnemyGoalPatrolRight = 7050.f;
	EnemyGoalPatrolLeft = 4070.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptMiddle_Implementation()
{
	IToT_MovementBlocks_P::AtCryptMiddle_Implementation();
	EnemyGoalPatrolRight = 10850.f;
	EnemyGoalPatrolLeft = 7830.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptEnd_Implementation()
{
	IToT_MovementBlocks_P::AtCryptEnd_Implementation();
	EnemyGoalPatrolRight = 14030.f;
	EnemyGoalPatrolLeft = 12530.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

