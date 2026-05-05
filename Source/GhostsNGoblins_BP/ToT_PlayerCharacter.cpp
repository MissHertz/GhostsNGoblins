// Fill out your copyright notice in the Description page of Project Settings.


#include "ToT_PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
AToT_PlayerCharacter::AToT_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Creating the two timelines
	SwitchInTimelineS = CreateDefaultSubobject<UTimelineComponent>(TEXT("Switch In Timeline"));
	SwitchOutTimelineW = CreateDefaultSubobject<UTimelineComponent>(TEXT("Switch Out Timeline"));
	
	// Setting default value of variables
	// Movement
	SwitchNumber = 250;
	PositionClose = 150; 
	PositionFar = PositionClose-SwitchNumber;
	CryptPositionFar = 1450;
	CryptPositionClose = CryptPositionFar+SwitchNumber;
	HasSwitched = false;
	// Health
	MaxHealth = 2;
	PlayerHealth = MaxHealth;
	LifeCounter = 2; 
	// Interactables
	EnteredCrypt = false;
	CryptKeyDropped = false; 
	HoldsCryptKey = false;
	// Weapons
	WeaponCooldownOver = true;
	WeaponCooldownTime = 0.5;
	// Actor
	FMPlayerMesh = true; 
	// Enemies
	BeatenSemiBoss = false; 
	ZombiesKilled = 0;
	
	

}

// Called when the game starts or when spawned
void AToT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Checking if the player controller is valid and binding it to the player
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
	
	// Binding the timelines to the correlating functions
	SwitchInDelegate.BindDynamic(this, &AToT_PlayerCharacter::SwitchInUpdate);
	SwitchInOver.BindDynamic(this, &AToT_PlayerCharacter::SwitchInFinished);
	
	if (SwitchInCurveS)
	{
		SwitchInTimelineS->AddInterpFloat(SwitchInCurveS, SwitchInDelegate);
		SwitchInTimelineS->SetTimelineFinishedFunc(SwitchInOver);
	}
	
	SwitchOutDelegate.BindDynamic(this, &AToT_PlayerCharacter::SwitchOutUpdate);
	SwitchOutOver.BindDynamic(this, &AToT_PlayerCharacter::SwitchOutFinished);
	
	if (SwitchOutCurveW)
	{
		SwitchOutTimelineW->AddInterpFloat(SwitchOutCurveW, SwitchOutDelegate);
		SwitchOutTimelineW->SetTimelineFinishedFunc(SwitchOutOver);
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
	
	// Binding the controller input to a function
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(RightLeftMovement, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerMoveRightLeft);
		EnhancedInputComponent->BindAction(SwitchLaneOutW, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerSwitchLaneOutW);
		EnhancedInputComponent->BindAction(SwitchLaneInS, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerSwitchLaneInS);
		EnhancedInputComponent->BindAction(PlayerJumpAction, ETriggerEvent::Triggered, this, &AToT_PlayerCharacter::PlayerJump);
	}

}

// Currently not in use
void AToT_PlayerCharacter::HandleCameraSplineMovement(AActor CameraSplineReference)
{
	//FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}

// Switching in timeline (closer to the camera)
void AToT_PlayerCharacter::SwitchInUpdate(float InValue)
{
	// Creating a new location for the player to move
	FVector TargetLocation = FVector(0.f, 0.f, 0.f); 
	
	// Checking if the player has entered the crypt or not, sets the new value based on that
	if (EnteredCrypt == false)
	{
		float NewYPosition = PositionFar + InValue;
		TargetLocation = FVector(GetActorLocation().X, NewYPosition, GetActorLocation().Z);
	}
	else if (EnteredCrypt == true)
	{
		float NewYPosition = CryptPositionFar + InValue;
		TargetLocation = FVector(GetActorLocation().X, NewYPosition, GetActorLocation().Z);
	}
	
	// Moving the player to the new location found
	this->SetActorLocation(TargetLocation, false);
}

// Switching in (closer to the camera) finished
void AToT_PlayerCharacter::SwitchInFinished()
{
	// Creating a new location for the player to move
	FVector ActorLocation = FVector(0.f, 0.f, 0.f); 
	if (EnteredCrypt == false)
	{
		ActorLocation = FVector(GetActorLocation().X, PositionClose, GetActorLocation().Z);
	}
	else if (EnteredCrypt == true)
	{
		ActorLocation = FVector(GetActorLocation().X, CryptPositionClose, GetActorLocation().Z);
	}
	
	// Setting the new player location, is only a safety measure in case timeline fails
	this->SetActorLocation(ActorLocation, false);
	
	// Sets the has switched to false as the player is in the closest lane
	HasSwitched = false; 
}

// Switching out timeline during update (further from the camera)
void AToT_PlayerCharacter::SwitchOutUpdate(float InValue)
{
	// Creating a new location for the player to move
	FVector TargetLocation = FVector(0.f, 0.f, 0.f); 
	
	// Checking if the player has entered the crypt or not, sets the new value based on that
	if (EnteredCrypt == false)
	{
		float NewYPosition = PositionClose - InValue;
		TargetLocation = FVector(GetActorLocation().X, NewYPosition, GetActorLocation().Z);
	}
	else if (EnteredCrypt == true)
	{
		float NewYPosition = CryptPositionClose - InValue;
		TargetLocation = FVector(GetActorLocation().X, NewYPosition, GetActorLocation().Z);
	}
	
	// Moving the player to the new location found
	this->SetActorLocation(TargetLocation, false);
}

// Switching out(further from the camera) finished
void AToT_PlayerCharacter::SwitchOutFinished()
{
	// Creating a new location for the player to move
	FVector ActorLocation = FVector(0.f, 0.f, 0.f); 
	if (EnteredCrypt == false)
	{
		ActorLocation = FVector(GetActorLocation().X, PositionFar, GetActorLocation().Z);
	}
	else if (EnteredCrypt == true)
	{
		ActorLocation = FVector(GetActorLocation().X, CryptPositionFar, GetActorLocation().Z);
	}
	// Setting the new player location, is only a safety measure in case timeline fails for any reason
	this->SetActorLocation(ActorLocation, false);
	HasSwitched = true; 
}

// Player moving right and left along the lane
void AToT_PlayerCharacter::PlayerMoveRightLeft(const FInputActionValue& ActionValue)
{
	FVector2D MovementVector = ActionValue.Get<FVector2D>();
	
	// Setting the movement input for the player
	AddMovementInput(GetActorForwardVector(), MovementVector.X, false);
	
	// Setting the mesh rotation as the actor does not do it itself
	USkeletalMeshComponent* PlayerMesh = this->GetMesh();
	
	FRotator MeshRotation = FRotator(0, MovementVector.X*-90, 0);
	PlayerMesh->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::None);
}

// Player switching lane out (Further away from the camera)
void AToT_PlayerCharacter::PlayerSwitchLaneOutW()
{
	// Checking if the player is not already in this lane, moving the player if it isn't
	if (HasSwitched == false)
	{
		if (SwitchOutTimelineW)
		{
			// Running the timeline from start
			SwitchOutTimelineW->PlayFromStart();
		}
	}
}

// Player switching lane in (Closer to the camera)
void AToT_PlayerCharacter::PlayerSwitchLaneInS()
{
	// Checking if the player is not already in this lane, moving the player if it isn't
	if (HasSwitched == true)
	{
		if (SwitchInTimelineS)
		{
			// Running the timeline from start
			SwitchInTimelineS->PlayFromStart();
		}
	}
}

// Player jumping
void AToT_PlayerCharacter::PlayerJump()
{
	Jump();
}

