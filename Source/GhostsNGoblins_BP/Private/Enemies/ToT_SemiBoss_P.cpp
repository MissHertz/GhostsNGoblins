// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_SemiBoss_P.h"

#include "GhostsNGoblins_BP/ToT_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/ToT_ProjectileParent_P.h"
#include "Interaction/ToT_BPI_Key_P.h"


// Sets default values
AToT_SemiBoss_P::AToT_SemiBoss_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Health variables setup
	MaxHealth = 220.f;
	CurrentHealth = MaxHealth;
	
	// Combat variables setup
	DetectionRange = 1900.f;
	IsChargedAttackReady = false;
	ChargedAttackCount = 0.f;
	IsSemiBossDead = false;
	CanAttack = false;
	JustHit = false;
	
	// State Tree components setup
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"));
	Dead.Tag = FGameplayTag::RequestGameplayTag(TEXT("SemiBossDead"));
	
	// Collision setup
	UCapsuleComponent* CollisionCapsule = GetCapsuleComponent();
	//CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AToT_SemiBoss_P::OnOverlapBegin);
	
	// Binding the event ApplyDamage to the function TakeDamage
	OnTakeAnyDamage.AddDynamic(this, &AToT_SemiBoss_P::TakeDamage);
	
}

// Called when the game starts or when spawned
void AToT_SemiBoss_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_SemiBoss_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
void AToT_SemiBoss_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AToT_SemiBoss_P::TakeDamage(AActor* DamagedActor, float Damage, 
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	// Checks the health of the semi boss and applies if it doesn't equal to zero
	if (CurrentHealth > 0.f)
	{
		CurrentHealth -= Damage;
		if (DamageCauser->IsA<AToT_ProjectileParent_P>())
        	{
        		this->PlayAnimMontage(TakingDamageMontage, 1.0, NAME_None);
        	}
	}
	
	if (CurrentHealth <= 0.f)
	{
		CurrentHealth = 0.f;
		IsSemiBossDead = true;
		StateTreeComponent->SendStateTreeEvent(Dead);
		
		TArray<AActor*> PlayerArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AToT_PlayerCharacter::StaticClass(), PlayerArray);
		for (AActor* Player : PlayerArray)
		{
			if (Player && Player->Implements<UToT_BPI_Key_P>())
			{
				IToT_BPI_Key_P::Execute_HasBeatenSemiBossCPP(Player);
			}
		}
	}
}

