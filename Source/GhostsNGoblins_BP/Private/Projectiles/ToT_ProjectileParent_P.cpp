// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ToT_ProjectileParent_P.h"

#include "Enemies/ToT_EnemyParent_P.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_ProjectileParent_P::AToT_ProjectileParent_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponDamage = 20.f; 
	ExsistanceTime = 2.f; 
	
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = Projectile;
	Projectile->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Projectile;
}

// Called when the game starts or when spawned
void AToT_ProjectileParent_P::BeginPlay()
{
	Super::BeginPlay();
	Projectile->OnComponentHit.AddDynamic(this, &AToT_ProjectileParent_P::HitEnemy);

	
}

// Called every frame
void AToT_ProjectileParent_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ExsistanceTime -= DeltaTime; 
	if (ExsistanceTime < 0)
	{
		this->Destroy();
	}
}

void AToT_ProjectileParent_P::HitEnemy(UPrimitiveComponent* HitComponent, AActor* HitActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitActor and EnemyBlueprint and HitActor->IsA(EnemyBlueprint))
	{
		UGameplayStatics::ApplyDamage(HitActor, WeaponDamage, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

