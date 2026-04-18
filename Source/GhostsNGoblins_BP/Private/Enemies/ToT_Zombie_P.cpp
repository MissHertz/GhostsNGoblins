// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_Zombie_P.h"

#include "StaticMeshSceneProxy.h"
#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_Zombie_P::AToT_Zombie_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerOverlapBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	PlayerOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_Zombie_P::OnOverlapBegin);
	
	OnTakeAnyDamage.AddDynamic(this, &AToT_Zombie_P::ZombieAttacked);
}

// Called when the game starts or when spawned
void AToT_Zombie_P::BeginPlay()
{
	Super::BeginPlay();
	
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
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("I have taken damage"));
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
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Turquoise, TEXT("Actor destroyed"));
			this->Destroy();
		}
	}
}

void AToT_Zombie_P::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

