// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ToT_WaterCollider_P.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AToT_WaterCollider_P::AToT_WaterCollider_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisonBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetRelativeScale3D(FVector(1.f, 1.f, 0.3));
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AToT_WaterCollider_P::PlayerOverlapping);
	
	Damage = 2; 
}

// Called when the game starts or when spawned
void AToT_WaterCollider_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToT_WaterCollider_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToT_WaterCollider_P::PlayerOverlapping(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(PlayerBlueprint))
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

