// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "ToT_FireWall_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_FireWall_P : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_FireWall_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Firewall;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBox; 
	
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<ACharacter> PlayerBlueprint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* FirewallTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FirewallCurve;
	
	FOnTimelineFloat FirewallDelegate;
	FOnTimelineEvent FirewallTimelineOver;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
	float ActorLocationZ; 
	
	UFUNCTION()
	void FirewallTimelineUpdate(float InValue);
	
	UFUNCTION()
	void FirewallTimelineEnded();
	
	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp,
	   AActor* OtherActor,
	   UPrimitiveComponent* OtherComp,
	   int32 OtherBodyIndex,
	   bool bFromSweep,
	   const FHitResult& SweepResult);
	
};
