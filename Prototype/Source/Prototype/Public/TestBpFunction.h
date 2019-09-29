// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROTOTYPE_API TestBpFunction
{
public:
	TestBpFunction();
	~TestBpFunction();
    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetProjectVersion", CompactNodeTitle = "GetProjectVersion"), Category = Game)
    static FString GetProjectVersion();
};
