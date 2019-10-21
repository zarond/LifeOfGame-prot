// Fill out your copyright notice in the Description page of Project Settings.


#include "GoLUser.h"

// Sets default values
AGoLUser::AGoLUser(const int width, const int height)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_width = width;
	_height = height;


	GOL = new GameOfLife(width, height);
	GOL->InsertPattern(width / 2, height / 2, Pattern(0));

}

AGoLUser::~AGoLUser()
{
	delete GOL;
}

void AGoLUser::UpdateWorld()
{
	GOL->Loop();
	const bool* const* Field = GOL->GetField();
	for (int i=0;i<_height;++i)
		for (int j = 0; j < _width; ++j) {
			Field[1][2] == false;
		}
}

// Called when the game starts or when spawned
void AGoLUser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoLUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

