// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_Zombie_P.h"

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
	PlayerOverlapBox->SetupAttachment(RootComponent);
	//PlayerOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_Zombie_P::OnOverlapBegin); // Commented out as the function is not yet in use
	
	// Binding the taking damage to the taking damage function
	OnTakeAnyDamage.AddDynamic(this, &AToT_Zombie_P::ZombieAttacked);
	
	// Presetting the variable
	ZombiesToKill = 3;
	
	AnimationTime = 0.6;
	AnimTimeCounter = 0;
	
	
}

// Called when the game starts or when spawned
void AToT_Zombie_P::BeginPlay()
{
	Super::BeginPlay();
	
	// Setting the lane the enemy moves along
	SetMovementPositions();
	// Finding the overlapping movement box and setting the movement variables based on it
	SetMovementBox();
	
	// Casting to the player controller to be able to get the player and use the variables for the player
	Player = Cast<AToT_PlayerCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
	
	
}

// Called every frame
void AToT_Zombie_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (AnimTimeCounter > 0)
	{
		AnimTimeCounter -= DeltaTime;
		if (AnimTimeCounter <= 0)
		{
			this->Destroy();
		}
	}
	
}

// Called to bind functionality to input
void AToT_Zombie_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Enemy taking damage function
void AToT_Zombie_P::ZombieAttacked(AActor* DamagedActor, float Damage, 
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	TArray<AActor*> ActorArray;
	
	GetCapsuleComponent()->GetOverlappingActors(ActorArray);
	
	for (AActor* OverlappingActor : ActorArray)
	{
		if (Weapon and OverlappingActor->IsA(Weapon))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Projectile overlapping"));
			// Checks if the health is above zero
			if (CurrentHealth > 0)
			{
				// Subtracting the damage from the healt
				CurrentHealth -= Damage; 
				//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("I have taken damage"));
		
				// Playing the hit or die anitmation
				PlayAnimMontage(HitAnimation, 2.f, FName("Default"));
		
				// Checks if the enemy is dead after taking the damage, destroying the actor if it is
				if (CurrentHealth <= 0)
				{
			
					// Checks that the player is valid to be able to get the values
					if (Player)
					{
						// Checks if enough zombies has been killed to be able to spawn a key
						if (Player->ZombiesKilled < ZombiesToKill)
						{
							Player->ZombiesKilled += 1;
							PlayAnimMontage(DieAnimation, 3.f, FName("Default"));
							AnimTimeCounter = AnimationTime;
						}
						else
						{
							// Checks if the key has been dropped already or not
							if (Player->CryptKeyDropped)
							{
								PlayAnimMontage(DieAnimation, 3.f, FName("Default"));
								AnimTimeCounter = AnimationTime;
							}
							// Spawning key if enough zombies have been killed
							else
							{
								PlayAnimMontage(DieAnimation, 3.f, FName("Default"));
								AnimTimeCounter = AnimationTime;
						
								FVector ZombieLocation = this->GetActorLocation();
								FRotator Rotation = FRotator(0, 0, 0);
								FActorSpawnParameters SpawnParameters;
						
								// Spawning key at the zombies location
								GetWorld()->SpawnActor<AActor>(DropKey, ZombieLocation, Rotation, SpawnParameters);
						
								// Telling the player the key is dropped
								Player->CryptKeyDropped = true;
						
								// Destroying the actor
							}
						}
					}
					// Still destroying and killing the zombie if the player is not valid
					else
					{
						PlayAnimMontage(DieAnimation, 3.f, FName("Default"));
						AnimTimeCounter = AnimationTime;
					}
				}
			} 
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
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Sending Message to movement box"));
			IToT_EnemyInMovementBlock::Execute_EnemyInMovementBlock(OverlappingActor, this);
		}
	}
}

// Setting the lane the zombie moves in, destroys the character if it cannot find a "valid" lane
void AToT_Zombie_P::SetMovementPositions()
{
	// Getting the Zombie's location
	FVector ZombiePosition = GetActorLocation();
	
	// Setting the lane based on the position they have
	if (ZombiePosition.Y == 150)
	{
		LanePositionY = 150;
	}
	else if (ZombiePosition.Y == -100)
	{
		LanePositionY = -100;
	}
	else if (ZombiePosition.Y == 1700)
	{
		LanePositionY = 1700;
	}
	else if (ZombiePosition.Y == 1450)
	{
		LanePositionY = 1450;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("No lane position"));
		this->Destroy();	
	}

}

/*
 * Getting the interface message and setting the patrol locations based on that
 */ 

void AToT_Zombie_P::AtDownGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtDownGraveyard_Implementation();
	EnemyGoalPatrolRight = 8090.f;
	EnemyGoalPatrolLeft = 3570.f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtUpperGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtUpperGraveyard_Implementation();
	EnemyGoalPatrolRight = 13600.f;
	EnemyGoalPatrolLeft = 8800.f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptGraveyard_Implementation()
{
	IToT_MovementBlocks_P::AtCryptGraveyard_Implementation();
	EnemyGoalPatrolRight = 16050.f;
	EnemyGoalPatrolLeft = 14450.f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptStart_Implementation()
{
	IToT_MovementBlocks_P::AtCryptStart_Implementation();
	EnemyGoalPatrolRight = 7050.f;
	EnemyGoalPatrolLeft = 5000.f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptMiddle_Implementation()
{
	IToT_MovementBlocks_P::AtCryptMiddle_Implementation();
	EnemyGoalPatrolRight = 10850.f;
	EnemyGoalPatrolLeft = 7830.f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

void AToT_Zombie_P::AtCryptEnd_Implementation()
{
	IToT_MovementBlocks_P::AtCryptEnd_Implementation();
	EnemyGoalPatrolRight = 14030.f;
	EnemyGoalPatrolLeft = 12530.f;
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Movement goals set"));
}

// Currently not in use
void AToT_Zombie_P::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

