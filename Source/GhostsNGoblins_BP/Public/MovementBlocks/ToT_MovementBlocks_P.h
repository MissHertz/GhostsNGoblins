// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToT_MovementBlocks_P.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UToT_MovementBlocks_P : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GHOSTSNGOBLINS_BP_API IToT_MovementBlocks_P
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AtDownGraveyard();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AtUpperGraveyard();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AtCryptGraveyard();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AtCryptStart();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AtCryptMiddle();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AtCryptEnd();
};
