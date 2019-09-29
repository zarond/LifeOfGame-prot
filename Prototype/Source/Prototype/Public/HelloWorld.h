// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelloWorld.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UHelloWorld : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Hello World", CompactNodeTitle = "HelloWorld"), Category = Game)
    static FString GetProjectVersion();
};
