// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatisticsActor.generated.h"

UCLASS()
class PROTOTYPE_API AStatisticsActor : public AActor
{
	GENERATED_BODY()
	
private:
	std::string fileNameLast = "level_last.dat"; //results for the last walkthrough
	std::string fileNameBest = "level_best.dat"; //best results for all time
	std::string fileNameTotal = "level_total.dat"; //total results for all time
	
	//it shouldn't be here, but it is okay for now
	//should be less than 32 char
	std::string playerName = "Player";

	unsigned int duration = 0;
	
	int killedNPC = 0;

	int inflictedDamagePoints = 0;

	int receivedDamagePoints = 0;
	int gotIntoLavaTimes = 0;

	bool hasDied = false;
	bool hasWon = false;

public:	
	// Sets default values for this actor's properties
	AStatisticsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintCallable, Category = "Statistics|Duration")
	void StartTimer();
	UFUNCTION(BlueprintCallable, Category = "Statistics|Duration")
	void StopTimer();

	UFUNCTION(BlueprintCallable, Category = "Statistics|File")
	void UpdateLastFile() const;
	UFUNCTION(BlueprintCallable, Category = "Statistics|File")
	void UpdateBestFile() const;
	UFUNCTION(BlueprintCallable, Category = "Statistics|File")
	void UpdateTotalFile() const;
	UFUNCTION(BlueprintCallable, Category = "Statistics|File")
	void ClearStatisticsInFiles() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Clear")
	void ClearStatisticsOnLevel();

	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Killed")
	void IncreaseKilledNPC();

	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Did Damage")
	void IncreaseInflictedDamagePoints(int points);

	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Receive Damage")
	void IncreaseReceiveDamagePoints(int points);
	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Receive Damage")
	void IncreaseGotIntoLavaTimes();

	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Passed Level Without Death")
	void YouDied();

	UFUNCTION(BlueprintCallable, Category = "Statistics|Achivement|Won Game")
	void YouWon();

	TArray<TArray<std::string>> FromLastFileToStrings() const;
	TArray<TArray<std::string>> FromBestFileToStrings() const;
	TArray<TArray<std::string>> FromTotalFileToStrings() const;
};
