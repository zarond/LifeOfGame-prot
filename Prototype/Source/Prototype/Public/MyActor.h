// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class PROTOTYPE_API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	bool **Matrix;
	int Width;
	int Height;
	FVector *ArrayOfEnemies;
	FVector* ArrayOfBlocks;
	int NumberOfEnemies;
	int NumberOfBlocks;
	FVector Start;
	FVector Finish;

public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*UFUNCTION(BlueprintCallable, Category = "Game")
	void Test();*/

public:
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	bool GetCell(int i, int j);
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	void GenerateLevel();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetWidth();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetHeight();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetNumberOfEnemies();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FVector GetEnemyPosition(int i);
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetNumberOfBlocks();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FVector GetBlockPosition(int i);
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FVector GetStartPosition();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FVector GetFinishPosition();


};
