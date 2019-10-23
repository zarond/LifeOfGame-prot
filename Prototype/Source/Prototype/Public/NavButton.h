// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavButton.generated.h"

UCLASS()
class PROTOTYPE_API ANavButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavButton();
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NavButton)
    int x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NavButton)
    int y;
    unsigned char dir;
	//UPROPERTY(EditAnywhere)
    unsigned char steps;
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
