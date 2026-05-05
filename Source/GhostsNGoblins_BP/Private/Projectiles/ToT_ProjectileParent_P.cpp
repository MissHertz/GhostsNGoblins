// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ToT_ProjectileParent_P.h"

#include "Enemies/ToT_EnemyParent_P.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_ProjectileParent_P::AToT_ProjectileParent_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Preset values of the projectile
	WeaponDamage = 20.f; 
	ExsistanceTime = 2.f; 
	
	// Creating the projectile mesh and setting its rotation and as a root component
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = Projectile;
	Projectile->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	
	// Creating the collision capsule and setting its rotation and attatchment to the projectile mesh
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	CollisionCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	CollisionCapsule->SetupAttachment(RootComponent);
	
	// Creating the projectile movement component and also connecting it to the mesh(root component)
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	
	// Setting the collision for the collision capsule
	CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	// Binding the on overlap with my own function
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AToT_ProjectileParent_P::HitEnemy);
}

// Called when the game starts or when spawned
void AToT_ProjectileParent_P::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AToT_ProjectileParent_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Destroying the projectile when it has exsisted for a long enough time
	ExsistanceTime -= DeltaTime; 
	if (ExsistanceTime < 0)
	{
		this->Destroy();
	}
}

// Function for when the projectile hits the enemy
void AToT_ProjectileParent_P::HitEnemy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if the actor hit is the one we have set as the enemy parent, if not this code will not run
	if (OtherActor->IsA(EnemyBlueprint))
	{
		// Applying changes to the enemy it hits
		UGameplayStatics::ApplyDamage(OtherActor, WeaponDamage, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}


