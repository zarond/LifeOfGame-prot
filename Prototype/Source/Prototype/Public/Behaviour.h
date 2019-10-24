// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameOfLife.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Behaviour.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UBehaviour : public UActorComponent
{
	GENERATED_BODY()

private: 
	struct ActionNode
	{
		int Attack = 0;
		int Move = 0;
		int Defense = 0;
		int Cost = 1;
	};
	int substeps;
	ActionNode** actions;
	GameOfLife* gol;
public:	
	// Sets default values for this component's properties
	UBehaviour();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Behaviour")
	int GetAttack();
	UFUNCTION(BlueprintCallable, Category = "Behaviour")
	int GetDefence();
	UFUNCTION(BlueprintCallable, Category = "Behaviour")
	int GetMove();
	UFUNCTION(BlueprintCallable, Category = "Behaviour")
	void NextStep();
	UFUNCTION(BlueprintCallable, Category = "Behaviour")
	void SetSubsteps(int val);
	UFUNCTION(BlueprintCallable, Category = "Behaviour")
	int GetSubsteps();
};
