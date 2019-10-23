// Fill out your copyright notice in the Description page of Project Settings.


#include "GoLUser.h"
#include "GameOfLife.h"


// Sets default values
AGoLUser::AGoLUser()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

////

AGoLUser::~AGoLUser()
{
	for (int i = 0; i < _height; ++i) {
		delete[] GoLField[i];
	}
	delete[] GoLField;
	_birth = {};
	_survive = {};
	LavaPieces = {};
}

void AGoLUser::GenerateGoL(int width, int height, TArray<bool> birth, TArray<bool> survive)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_width = width;
	_height = height;

	if (birth.Num() != 9) {
		for (int i = 0; i < 9; ++i) _birth[i] = defaultBirth[i];
		printf("Number of bools in birth is incorrect. Set default value.");
	}
	else {
		for (int i = 0; i < 9; ++i) _birth[i] = birth[i];
	}

	if (survive.Num() != 9) {
		for (int i = 0; i < 9; ++i) _survive[i] = defaultSurvive[i];
		printf("Number of bools in survive is incorrect. Set default value.");
	}
	else {
		for (int i = 0; i < 9; ++i) _survive[i] = survive[i];
	}
	
	std::vector<bool> bgene = std::vector<bool>();
	std::vector<bool> sgene = std::vector<bool>();
	for (int i = 0; i < 9; ++i) {
		bgene.push_back(_birth[i]);
		sgene.push_back(_survive[i]);
	}

	GameOfLife* GoL = new GameOfLife(_width, _height);
	GoL->SetBirthGene(bgene);
	GoL->SetSurviveGene(sgene);

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			if ((double)rand() / RAND_MAX < birthChance) GoL->Summon(i, j); else GoL->Kill(i, j);
			if (i == 0 || j == 0 || i == _height - 1 || j == _width - 1) GoL->Summon(i, j);
		}
	}

	GoLField = GoL->GetFieldCopy();

	delete GoL;
}

void AGoLUser::UpdateGoL(TArray<bool> birth, TArray<bool> survive)
{
	if (birth.Num() != 9) {
		for (int i = 0; i < 9; ++i) _birth[i] = defaultBirth[i];
		printf("Number of bools in birth is incorrect. Set default value.");
	}
	else {
		for (int i = 0; i < 9; ++i) _birth[i] = birth[i];
	}

	if (survive.Num() != 9) {
		for (int i = 0; i < 9; ++i) _survive[i] = defaultSurvive[i];
		printf("Number of bools in survive is incorrect. Set default value.");
	}
	else {
		for (int i = 0; i < 9; ++i) _survive[i] = survive[i];
	}

	std::vector<bool> bgene = std::vector<bool>();
	std::vector<bool> sgene = std::vector<bool>();
	for (int i = 0; i < 9; ++i) {
		bgene.push_back(_birth[i]);
		sgene.push_back(_survive[i]);
	}

	GameOfLife* GoL = new GameOfLife(_width, _height);

	GoL->SetBirthGene(bgene);
	GoL->SetSurviveGene(sgene);

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			if (GoLField[i][j]) GoL->Summon(i, j); else GoL->Kill(i, j);
		}
	}

	GoL->Loop();

	GoLField = GoL->GetFieldCopy();

	delete GoL;
}

TArray<AActor*> AGoLUser::PutLavaPiecesOnField() {
	return LavaPieces;
}