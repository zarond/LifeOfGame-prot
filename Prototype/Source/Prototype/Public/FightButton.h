// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FightButton.generated.h"

UCLASS()
class PROTOTYPE_API AFightButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFightButton();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = fightButton)
    int x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = fightButton)
    int y;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
