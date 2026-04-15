// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToT_EnemyInMovementBlock.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UToT_EnemyInMovementBlock : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GHOSTSNGOBLINS_BP_API IToT_EnemyInMovementBlock
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnemyInMovementBlock(AActor* Executor);
};
