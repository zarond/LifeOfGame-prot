// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "CellularAutomata.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::GenerateLevel(int h, int w) {
	CellularAutomata gen(h, w);
	gen.Generate();
	Width = gen.GetFloorWidth();
	Height = gen.GetFloorHeight();
	bool** _Matrix = gen.GetFloorMap();
	NumberOfEnemies = gen.GetNumberOfEnemies();
	NumberOfBlocks = gen.GetNumberOfBlocks();
	
	Matrix = new Cell * [Height];
	for (int i = 0; i < Height; ++i) {
		Matrix[i] = new Cell[Width];
		for (int j = 0; j < Width; ++j) {
			Matrix[i][j].floorID = 1;
			Matrix[i][j].isOccupied = _Matrix[i][j] ? 1 : 0;
		}
	}

	start_finish sf = gen.GetStartFinishIndex();
	Start[0] = sf.first.first;
	Start[1] = sf.first.second;
	Start[2] = 0;
	Finish[0] = sf.second.first;
	Finish[1] = sf.second.second;
	Finish[2] = 0;
	
	vectorOfIndex points = gen.GetArrayOfEnemies();
	ArrayOfEnemies = new FVector[NumberOfEnemies];
	for (int i = 0; i < NumberOfEnemies; ++i) {
		ArrayOfEnemies[i][0] = points[i].first;
		ArrayOfEnemies[i][1] = points[i].second;
		ArrayOfEnemies[i][2] = 0;
		Matrix[points[i].first][points[i].second].isOccupied = 2;
	}

	/*vectorOfIndex points = gen.GetArrayOfBlocks();
	ArrayOfBlocks = new FVector[NumberOfBlocks];
	for (int i = 0; i < NumberOfBlocks; ++i) {
		ArrayOfBlocks[i][0] = points[i].first;
		ArrayOfBlocks[i][1] = points[i].second;
		ArrayOfBlocks[i][2] = 0;
		Matrix[points[i].first][points[i].second].isOccupied = 1;
	}*/
}

int AMyActor::GetCell_IsOccupied(int i, int j) {
	return Matrix[i][j].isOccupied;
}

void AMyActor::SetCell_IsOccupied(int i, int j, int ch) {
	Matrix[i][j].isOccupied = ch;
}

int AMyActor::GetWidth() {
	return Width;
}

int AMyActor::GetHeight() {
	return Height;
}

int AMyActor::GetNumberOfEnemies() {
	return NumberOfEnemies;
}

FVector AMyActor::GetEnemyPosition(int i) {
	return ArrayOfEnemies[i];
}

int AMyActor::GetNumberOfBlocks() {
	return NumberOfBlocks;
}

FVector AMyActor::GetBlockPosition(int i) {
	return ArrayOfBlocks[i];
}

FVector AMyActor::GetStartPosition() {
	return Start;
}

FVector AMyActor::GetFinishPosition() {
	return Finish;
}

