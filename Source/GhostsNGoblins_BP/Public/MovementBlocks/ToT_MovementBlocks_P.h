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
	void InDownGraveyard(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InUpperGraveyard(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InCryptGraveyard(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InCryptStart(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InCryptMiddle(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InCryptEnd(AActor* Instigator);
};
