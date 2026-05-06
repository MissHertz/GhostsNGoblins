// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_EnemyParent_P.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_EnemyParent_P::AToT_EnemyParent_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	/*
	 * Setting default settings for variables
	 */
	// Health Related
	MaxHealth = 100; 
	CurrentHealth = MaxHealth; 
	
	// Movement related
	EnemySpeed = 500;
	IsMovingRight = true;
	IsMovingLeft = false;
	EnemyGoalPatrolRight = 8090.f;
	EnemyGoalPatrolLeft = 3570.f;
	LanePositionY = 150.f;
	MovementLane = 1;
	
	// Combat Related
	DamageToPlayer = 1;
	TwoLaneAttack = false;
	CanAttack = false;
	JustHit = false;
	EnemyHitCooldownTime = 1; 
	
}

// Called when the game starts or when spawned
void AToT_EnemyParent_P::BeginPlay()
{
	Super::BeginPlay();
	
	// Binding functions
	UCapsuleComponent* CollisionCapsule = GetCapsuleComponent();
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AToT_EnemyParent_P::OnPlayerHit);
	
}

// Called every frame
void AToT_EnemyParent_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Actor just hit cooldown "timer"
	if (JustHit == true)
	{
		if (EnemyHitCooldown > 0)
		{
			EnemyHitCooldown -= DeltaTime;
		}
		else if (EnemyHitCooldown <= 0)
		{
			JustHit = false; 
		}

	}
}

// Called to bind functionality to input
void AToT_EnemyParent_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Dealing damage when hitting the player
void AToT_EnemyParent_P::OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* HitActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Checks if the overlapping actor is the player
	if (HitActor and PlayerBlueprint and  HitActor->IsA(PlayerBlueprint))
	{
		// Dealing damage if the enemy has not just hit the player this is to make sure the player has time to react before taking more damage
		if (JustHit == false)
		{
			UGameplayStatics::ApplyDamage(HitActor, DamageToPlayer, GetInstigatorController(), this, UDamageType::StaticClass());
			EnemyHitCooldown = EnemyHitCooldownTime;
			JustHit = true; 
		}
	}
}

