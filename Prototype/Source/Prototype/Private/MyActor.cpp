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
    UE_LOG(LogTemp, Warning,TEXT("width: %i, height: %j"),Width,Height);//////////////
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
	

	int number = gen.GetNumberOfEnemies();
	vectorOfIndex points = gen.GetArrayOfEnemies();
	ArrayOfEnemies = TArray<FIntVector>();
	for (int i = 0; i < number; ++i) {
		ArrayOfEnemies.Add(FIntVector(points[i].first, points[i].second, 0));
	}
	
	number = gen.GetNumberOfBlocks();
	points = gen.GetArrayOfBlocks();
	ArrayOfBlocks = TArray<FIntVector>();
	for (int i = 0; i < number; ++i) {
		ArrayOfBlocks.Add(FIntVector(points[i].first, points[i].second, 0));
	}
}

int AMyActor::GetCell_IsOccupied(int i, int j) const {
	//UE_LOG(LogTemp, Warning, TEXT("Some variable values: i: %d, j: %d"), i, j);
	return Matrix[i][j].isOccupied;
}

void AMyActor::SetCell_IsOccupied(int i, int j, int ch) {
	Matrix[i][j].isOccupied = ch;
}

int AMyActor::GetWidth() const  {
	return Width;
}

int AMyActor::GetHeight() const {
	return Height;
}

int AMyActor::GetNumberOfEnemies() const {
	return ArrayOfEnemies.Num();
}

int AMyActor::GetNumberOfBlocks() const {
	return ArrayOfBlocks.Num();
}

FIntVector AMyActor::GetEnemyPosition(int i) const {
	return ArrayOfEnemies[i];
}

FIntVector AMyActor::GetBlockPosition(int i) const  {
	return ArrayOfBlocks[i];
}

FIntVector AMyActor::GetStartPosition() const  {
	return Start;
}

FIntVector AMyActor::GetFinishPosition() const  {
	return Finish;
}

bool AMyActor::CheckIfBlocked(FIntVector coord) const {
    //coord[1];
    //if (Height == 0 ) return false;
	if (coord[0] < 0 || coord[0] >= Height || coord[1] < 0 || coord[1] >= Width) return false;
	if (Matrix[coord[0]][coord[1]].isOccupied == 0) return true;
	else return false;
    //return true; //?
    //return false;

}

TArray<bool> AMyActor::GetBirth()
{
	return Birth;
}

TArray<bool> AMyActor::GetSurvive()
{
	return Survive;
}

void AMyActor::SetBirth(TArray<bool> _birth)
{
	if (_birth.Num() == 9)
	{
		Birth = TArray<bool>(_birth);
	}
}

void AMyActor::SetSurvive(TArray<bool> _survive)
{
	if (_survive.Num() == 9)
	{
		Survive = TArray<bool>(_survive);
	}
}
