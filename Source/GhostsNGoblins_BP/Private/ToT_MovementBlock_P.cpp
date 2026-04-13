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
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Player entered box"));
		EnemySpawnTime = 5; 
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
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Player left box"));
	}
}

// Enemy spawner
void AToT_MovementBlock_P::SpawnEnemies(float DeltaTime)
{
	// Checks if player is in the box
	if (PlayerInBox == true)
	{
		// Has time pass to avoid enemies spawning all the time (basically a buffer)
		EnemySpawnTime -= DeltaTime; 
		
		if (EnemySpawnTime <= 0)
		{
			
			int randomInteger = FMath::RandHelper(EnemySpawnRange);
			
			switch (randomInteger)
			{
			case 0: 
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Spawning ZOMBIE"));
				SpawnZombie();
				break;
			case 1:
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Spawning BAT"));
				break;
			default:
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Spawning NOTHING"));
				break;
			}
			
			// Debug message
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Spawning Enemy"));
			
			EnemySpawnTime = 5;
		}
	}
}

// Spawning zombie function
void AToT_MovementBlock_P::SpawnZombie()
{
	if (Player == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("No playa"));
		return;
	} 
	
	FVector PlayerLocation = Player->GetActorLocation();
	float PositionX = PlayerLocation.X + 500;
	float PositionZ = PlayerLocation.Z + 50;
	
	FVector ZombieSpawnLocation = FVector(PositionX, PlayerLocation.Y, PositionZ); 
	// ZombieSpawnLocation.X = PositionX;
	// ZombieSpawnLocation.Y = PlayerLocation.Y;
	// ZombieSpawnLocation.Z = PositionZ;
	
	FRotator ZombieRotation;
	ZombieRotation.Yaw = 0;
	ZombieRotation.Roll = 0;
	ZombieRotation.Pitch = 0;
	
	FActorSpawnParameters SpawnParameters;
	
	GetWorld()->SpawnActor<ACharacter>(Zombie, 
		ZombieSpawnLocation,
		ZombieRotation,
		SpawnParameters);
	
}

// Spawning bat function
void AToT_MovementBlock_P::SpawnBat()
{
}

