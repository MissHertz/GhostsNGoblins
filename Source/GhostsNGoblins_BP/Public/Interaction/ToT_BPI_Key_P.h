// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToT_BPI_Key_P.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UToT_BPI_Key_P : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GHOSTSNGOBLINS_BP_API IToT_BPI_Key_P
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HasCryptKey();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HasLevelKey();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickedUpArmour();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HasBeatenSemiBoss();
};
