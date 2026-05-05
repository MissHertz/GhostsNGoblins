#include "Projectiles/ToT_ProjectileTorch_P.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

AToT_ProjectileTorch_P::AToT_ProjectileTorch_P()
{
	PrimaryActorTick.bCanEverTick = true;
    
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AToT_ProjectileTorch_P::OnHittingEnemy);
	ExistingFire = false;

	if (Projectile)
	{
		Projectile->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

void AToT_ProjectileTorch_P::BeginPlay()
{
	Super::BeginPlay(); // This runs the Blueprint BeginPlay, which handles the impulse
}

void AToT_ProjectileTorch_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	ExsistanceTime -= DeltaTime; 
	if (ExsistanceTime < 0)
	{
		this->Destroy();
	}
}

void AToT_ProjectileTorch_P::OnHittingEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!ExistingFire)
	{
		ExistingFire = true;
		FVector SpawnLocation = Projectile->GetComponentLocation();
		FRotator SpawnRotation(0.0, 0.0, 0.0);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
        
		GetWorld()->SpawnActor<AActor>(FireballGroundFire, SpawnLocation, 
			SpawnRotation, SpawnParameters);

		if (OtherActor && OtherActor != this)
		{
			UGameplayStatics::ApplyDamage(OtherActor, WeaponDamage, 
				GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}
}