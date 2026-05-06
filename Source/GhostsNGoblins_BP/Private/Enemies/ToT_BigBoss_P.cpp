// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ToT_BigBoss_P.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_BigBoss_P::AToT_BigBoss_P()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//AnyDamage
	OnTakeAnyDamage.AddDynamic(this, &AToT_BigBoss_P::BigBossAttacked);
	
}

// Called when the game starts or when spawned
void AToT_BigBoss_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_BigBoss_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AToT_BigBoss_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AToT_BigBoss_P::BigBossAttacked(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage;
		if (HitReactMontage)
		{
			PlayAnimMontage(HitReactMontage);
		}
		
		if (CurrentHealth < 120 && BossLowHealth)
		{
			GetMesh()->SetSkeletalMesh(BossLowHealth);
		}
	 
		if (CurrentHealth <= 0)
		{
			if (VictoryWidgetClass)
			{
				APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (PC)
				{
					// Creating the widget instance
					UUserWidget* VictoryWidget = CreateWidget<UUserWidget>(PC, VictoryWidgetClass);
					
					if (VictoryWidget)
					{
						// Add the widget to the player's screen
						VictoryWidget->AddToViewport();
	                        
						// Enable mouse so player can click buttons on the widget
						PC->SetShowMouseCursor(true);
						FInputModeUIOnly InputMode;
						PC->SetInputMode(InputMode);
					}
				}
			}
	 
			// Final elimination of the actor
			this->Destroy(); 
		}
	}
}