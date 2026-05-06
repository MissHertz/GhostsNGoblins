// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostsNGoblins_BP/Public/ToT_MovementBlock_P.h"
#include "Components/BoxComponent.h"


// Sets default values
AToT_MovementBlock_P::AToT_MovementBlock_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Setting up the collision box and binding to the overlap begin and end fuctions
	CollisionBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_MovementBlock_P::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AToT_MovementBlock_P::OnOverlapEnd);
	
	// Setting variables
	PlayerInBox = false; 
	EnemySpawnTime = 2;
	EnemySpawnCooldown = 3;
	EnemySpawnRange = 2; 
	DelaySpawnTimer = 2.f;
	
	BatSpawnOffsetX = 1000; 
	BatSpawnOffsetZ = 50;
	ZombieSpawnOffsetX = 750;
	ZombieSpawnOffsetZ = 50;
	
}

// Called when the game starts or when spawned
void AToT_MovementBlock_P::BeginPlay()
{
	Player = Cast<AToT_PlayerCharacter>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
	
	Super::BeginPlay();
	
}

// Called every frame
void AToT_MovementBlock_P::Tick(float DeltaTime)
{
	SpawnEnemies(DeltaTime);
	Super::Tick(DeltaTime);
}

// When player starts overlapping with the box
void AToT_MovementBlock_P::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checks if it actually is the player or not that enters the box
	if (OtherActor and OtherActor->IsA(PlayerBlueprint))
	{
		PlayerInBox = true;
		EnemySpawnCooldown = EnemySpawnTime; 
	}
}

// When player leaves the box
void AToT_MovementBlock_P::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Checks if it actually is the player leaving the box
	if (OtherActor and OtherActor->IsA(PlayerBlueprint))
	{
		PlayerInBox = false;
	}
}

// Enemy spawner
void AToT_MovementBlock_P::SpawnEnemies(float DeltaTime)
{
	// Checks if player is in the box
	if (PlayerInBox == true)
	{
		// Has time pass to avoid enemies spawning all the time (basically a buffer)
		EnemySpawnCooldown -= DeltaTime; 
		
		if (EnemySpawnCooldown <= 0)
		{
			// Getting a random integer
			int RandomInteger = FMath::RandHelper(EnemySpawnRange);
			
			// Spawning enemies according to the value of the random integer
			switch (RandomInteger)
			{
			case 0: 
				SpawnZombie();
				break;
			case 1:
				SpawnBat();
				break;
			default:
				break;
			}
			
			// Setting the cooldown for spawning
			EnemySpawnCooldown = EnemySpawnTime;
		}
	}
}

// Spawning zombie function
void AToT_MovementBlock_P::SpawnZombie()
{
	// Stops function if player is an empty pointer
	if (Player == nullptr)
	{
		return;
	} 
	
	// Getting the players location and setting the spawn offset
	FVector PlayerLocation = Player->GetActorLocation();
	float PositionX = PlayerLocation.X + ZombieSpawnOffsetX;
	float PositionZ = PlayerLocation.Z + ZombieSpawnOffsetZ;
	
	// Setting the spawn location
	FVector ZombieSpawnLocation = FVector(PositionX, PlayerLocation.Y, PositionZ); 
	
	// Setting the spawn rotation
	FRotator ZombieRotation;
	ZombieRotation.Yaw = 0;
	ZombieRotation.Roll = 0;
	ZombieRotation.Pitch = 0;
	
	// Setting the spawn parameters 
	FActorSpawnParameters SpawnParameters;
	
	// Spawning the zombie
	GetWorld()->SpawnActor<ACharacter>(Zombie, 
		ZombieSpawnLocation,
		ZombieRotation,
		SpawnParameters);
	
}

// Spawning bat function
void AToT_MovementBlock_P::SpawnBat()
{
	// Stops function if player is an empty pointer
	if (Player == nullptr)
	{
		return;
	} 
	
	// Getting the player's location and finding a spawn location for the bat
	FVector PlayerLocation = Player->GetActorLocation();
	float PositionX = PlayerLocation.X + BatSpawnOffsetX;
	float PositionZ = PlayerLocation.Z + BatSpawnOffsetZ;
	
	// Setting the spawn location
	FVector BatSpawnLocation = FVector(PositionX, PlayerLocation.Y, PositionZ); 

	// Setting the bats rotation
	FRotator BatRotation = FRotator(0, 0, 0);
	
	FActorSpawnParameters SpawnParameters;
	
	// Spawning the bat
	GetWorld()->SpawnActor<ACharacter>(Bat, 
		BatSpawnLocation,
		BatRotation,
		SpawnParameters);
}

