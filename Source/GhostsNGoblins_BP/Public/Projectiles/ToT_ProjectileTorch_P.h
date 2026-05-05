// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "ToT_ProjectileParent_P.h"
#include "ToT_ProjectileTorch_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_ProjectileTorch_P : public AToT_ProjectileParent_P
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AToT_ProjectileTorch_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool ExistingFire;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* Fire;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> FireballGroundFire;
	
	UFUNCTION()
	void OnHittingEnemy(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
