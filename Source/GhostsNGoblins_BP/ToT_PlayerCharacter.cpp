// Fill out your copyright notice in the Description page of Project Settings.


#include "ToT_PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


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
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(MappingContext, 0);
			}
			
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
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(RightLeftMovement, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerMoveRightLeft);
		EnhancedInputComponent->BindAction(SwitchLaneOutW, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerSwitchLaneOutW);
		EnhancedInputComponent->BindAction(SwitchLaneInS, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerSwitchLaneInS);
		EnhancedInputComponent->BindAction(PlayerJumpAction, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerJump);
	}

}

// Currently not 
void AToT_PlayerCharacter::HandleCameraSplineMovement(AActor CameraSplineReference)
{
	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	
}

// Player moving right and left along the lane
void AToT_PlayerCharacter::PlayerMoveRightLeft()
{
}

// Player switching lane out (Further away from the camera)
void AToT_PlayerCharacter::PlayerSwitchLaneOutW()
{
}

// Player switching lane in (Closer to the camera)
void AToT_PlayerCharacter::PlayerSwitchLaneInS()
{
}

// Player jumping
void AToT_PlayerCharacter::PlayerJump()
{
	Jump();
}

