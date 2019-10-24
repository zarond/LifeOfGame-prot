// Fill out your copyright notice in the Description page of Project Settings.


#include "Behaviour.h"

// Sets default values for this component's properties
UBehaviour::UBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBehaviour::BeginPlay()
{
	Super::BeginPlay();
	actions = new ActionNode * [3];
	for (int i = 0; i < 3; ++i)
	{
		actions[i] = new ActionNode[3];
		for (int j = 0; j < 3; ++j)
			actions[i][j] = ActionNode();
	}
	gol = new GameOfLife(5, 5);
	actions[0][1].Attack = 5;
	gol->Summon(1, 2);
	actions[1][0].Defense = 5;
	actions[1][1].Attack = 3;
	gol->Summon(2, 2);
	actions[1][2].Move = 3;
	actions[2][1].Move = 1;
	gol->Summon(3, 2);
	substeps = 3;
	// ...
	
}


// Called every frame
void UBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


int UBehaviour::GetAttack()
{
	int res = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (substeps > 0)
			{
				if (gol->GetField()[i + 1][j + 1] && actions[i][j].Attack > 0)
				{
					res += actions[i][j].Attack;
					substeps--;
				}
			}
	return res;
}

int UBehaviour::GetDefence()
{
	int res = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (substeps > 0)
			{
				if (gol->GetField()[i + 1][j + 1] && actions[i][j].Defense > 0)
				{
					res += actions[i][j].Defense;
					substeps--;
				}
			}
	return res;
}

int UBehaviour::GetMove()
{
	int res = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (substeps > 0)
			{
				if (gol->GetField()[i + 1][j + 1] && actions[i][j].Move > 0)
				{
					res += actions[i][j].Move;
					substeps--;
				}
			}
	return res;
}

void UBehaviour::NextStep()
{
	
	gol->Loop();
}

void UBehaviour::SetSubsteps(int val)
{
	substeps = val;
}

int UBehaviour::GetSubsteps()
{
	return substeps;
}