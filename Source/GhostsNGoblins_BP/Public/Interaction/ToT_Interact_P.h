// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToT_Interact_P.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UToT_Interact_P : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GHOSTSNGOBLINS_BP_API IToT_Interact_P
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// Functions for different types of interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(ACharacter* CharacterInstigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Rotate();
};
