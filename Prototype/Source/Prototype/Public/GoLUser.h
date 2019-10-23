//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "GoLUser.generated.h"
//
//UCLASS()
//class PROTOTYPE_API AGoLUser : public AActor
//{
//	GENERATED_BODY()
//	
//private:
//	int _width;
//	int _height;
//	TArray<bool> _birth;
//	TArray<bool> _survive;
//	TArray<AActor*> LavaPieces;
//	bool** GoLField;
//	const double birthChance = 0.47;
//	const TArray<bool> defaultBirth = { false, false, false, true, false, false, false, false, false };
//	const TArray<bool> defaultSurvive = { false, false, true, true, false, false, false, false, false };
//
//public:	
//	// Sets default values for this actor's properties
//	AGoLUser();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//public:
//	~AGoLUser();
//	/*UFUNCTION(BlueprintCallable, Category = "Game Of Life")
//	void GenerateGoL(int width, int height, TArray<bool> birth = {}, TArray<bool> survive = {});
//	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
//	void UpdateGoL(TArray<bool> birth = {}, TArray<bool> survive = {});*/
//	UFUNCTION(BlueprintCallable, Category = "Game Of Life")
//	TArray<AActor*> PutLavaPiecesOnField();
//};
