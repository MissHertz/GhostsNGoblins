// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateTree.h"
#include "CoreMinimal.h"
#include "ToT_EnemyParent_P.h"
#include "Components\StateTreeComponent.h"
#include "Interaction/ToT_BPI_Key_P.h"
#include "GameplayTagContainer.h"
#include "ToT_SemiBoss_P.generated.h"

UCLASS()
class GHOSTSNGOBLINS_BP_API AToT_SemiBoss_P : public AToT_EnemyParent_P, public IToT_BPI_Key_P
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AToT_SemiBoss_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Combat variables declaration
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DetectionRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsChargedAttackReady;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float ChargedAttackCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool IsSemiBossDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FStateTreeEvent Dead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* TakingDamageMontage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Tree")
	UStateTreeComponent* StateTreeComponent;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Tree")
	UStateTree* StateTree;*/
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, 
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};