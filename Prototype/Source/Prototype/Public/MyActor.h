// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class PROTOTYPE_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	struct Cell {
		unsigned char isOccupied;
		unsigned char floorID;
	};

private:
	Cell **Matrix;
	int Width;
	int Height;
	TArray<FIntVector> ArrayOfEnemies;
	TArray<FIntVector> ArrayOfBlocks;
	FIntVector Start;
	FIntVector Finish;
	TArray<bool> Birth;
	TArray<bool> Survive;
public:	
	// Sets default values for this actor's properties
	AMyActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetCell_IsOccupied(int i, int j) const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	void SetCell_IsOccupied(int i, int j, int ch);
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	void GenerateLevel(int h, int w);
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetWidth() const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetHeight() const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetNumberOfEnemies() const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	int GetNumberOfBlocks() const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FIntVector GetEnemyPosition(int i) const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FIntVector GetBlockPosition(int i) const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	FIntVector GetStartPosition() const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")

	FIntVector GetFinishPosition() const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	bool CheckIfBlocked(FIntVector coord) const;
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	TArray<bool> GetBirth();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	TArray<bool> GetSurvive();
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	void SetBirth(TArray<bool> _birth);
	UFUNCTION(BlueprintCallable, Category = "Game Field")
	void SetSurvive(TArray<bool> _survive);
	
};
