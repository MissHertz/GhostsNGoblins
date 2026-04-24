// Fill out your copyright notice in the Description page of Project Settings.


#include "ToT_PlayerCharacter.h"

// Sets default values
AToT_PlayerCharacter::AToT_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SwitchNumber = 250;
	PositionClose = 100; 
	PositionFar = PositionClose-SwitchNumber;
	MaxHealth = 2;
	PlayerHealth = MaxHealth;
	CryptPositionFar = 1450;
	CryptPositionClose = CryptPositionFar+SwitchNumber;
	EnteredCrypt = false;
	CryptKeyDropped = false; 
	HasSwitched = false;
	WeaponCooldownOver = true;
	WeaponCooldownTime = 0.5;
	FMPlayerMesh = true; 
	LifeCounter = 2; 
	HoldsCryptKey = false;
	BeatenSemiBoss = false; 

}

// Called when the game starts or when spawned
void AToT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			// UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)
			// {
			// 	Subsystem->AddMappingContext
			// }
			
		}
	}
	
}

// Called every frame
void AToT_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AToT_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AToT_PlayerCharacter::HandleCameraSplineMovement(AActor CameraSplineReference)
{
	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	
}

