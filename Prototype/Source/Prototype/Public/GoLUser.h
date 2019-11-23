// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameOfLife.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoLUser.generated.h"

UCLASS()
class PROTOTYPE_API AGoLUser : public AActor
{
	GENERATED_BODY()
	
private:
	int _width;
	int _height;
	TArray<bool> _birth;
	TArray<bool> _survive;
	TArray<AActor*> LavaPieces;
	//GameOfLife* GoL; /////////////////////////////////////////////////////////////////////////////// - было так
	bool** GoLField;
	bool** VisibleGoLField;
	const double birthChance = 0.47;
	const TArray<bool> defaultBirth = { false, false, false, true, false, false, false, false, false };
	const TArray<bool> defaultSurvive = { false, false, true, true, false, false, false, false, false };

public:
    GameOfLife* GoL; /////// было в private
    int get_width() {return _width;}
    int get_height() {return _height;}
    
    
	// Sets default values for this actor's properties
	AGoLUser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	~AGoLUser();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	void GenerateGoL(int width, int height, TArray<bool> birth, TArray<bool> survive, AMyActor* GlobalActor, int range = 3, bool needClearSpace = true);
	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	void ClearCreaturesSpace(AMyActor* GlobalActor, int range = 3);
	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	void UpdateGoL(TArray<bool> birth, TArray<bool> survive, AMyActor* GlobalActor, int range = 3, bool needClearSpace = true);
	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	bool IsAlive(int x, int y) const;
	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	bool WillBeAlive(int x, int y) const;
	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
	TArray<AActor*> UpdateLavaPiecesOnField(int polygon_size);
	void ClearSpace(int x, int y, int range = 3);
    
};
