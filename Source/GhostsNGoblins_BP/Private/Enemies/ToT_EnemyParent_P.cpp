// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_EnemyParent_P.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_EnemyParent_P::AToT_EnemyParent_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Setting up the actors collision component
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	CollisionCapsule->SetCollisionProfileName(TEXT("Something"));
	CollisionCapsule->SetNotifyRigidBodyCollision(true); 
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AToT_EnemyParent_P::OnPlayerHit);
	
	
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
	
}

// Called when the game starts or when spawned
void AToT_EnemyParent_P::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AToT_EnemyParent_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AToT_EnemyParent_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AToT_EnemyParent_P::OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* HitActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitActor->IsA(PlayerBlueprint))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Has hit player."));
		//UGameplayStatics::ApplyDamage(HitActor, DamageToPlayer, GetInstigatorController(), this, UDamageType::StaticClass());
	}
	
}

