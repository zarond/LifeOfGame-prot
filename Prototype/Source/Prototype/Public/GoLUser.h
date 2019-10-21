// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameOfLife.cpp"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoLUser.generated.h"

UCLASS()
class PROTOTYPE_API AGoLUser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoLUser(const int width, const int height);
	~AGoLUser();
	void UpdateWorld();
	

	GameOfLife* GOL;
	TArray<AActor*> LavaPieces;
	int _width;
	int _height;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
