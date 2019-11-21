// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticsActor.h"

// Sets default values
AStatisticsActor::AStatisticsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStatisticsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatisticsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

