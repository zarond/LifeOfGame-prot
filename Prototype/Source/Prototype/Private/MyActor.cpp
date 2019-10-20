// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "TestGenerator.h"
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

/*void AMyActor::Test() {
	UE_LOG(LogTemp, Warning, TEXT("Global Actor Func"));
}*/

void AMyActor::GenerateLevel() {
	//TestGenerator Generator;
	TestGenerator Generator(16, 32);
	CellularAutomata gen(20, 20);
	gen.Generate();
	Width = gen.GetFloorWidth();
	Height = gen.GetFloorHeight();
	Matrix = gen.GetFloorMap();
	NumberOfEnemies = Generator.GetNumberOfEnemies();
	NumberOfBlocks = Generator.GetNumberOfBlocks();

	//TestGenerator::FVector* points = Generator.GetStartAndFinish();
	
	//Start[0] = points[0].X; Start[1] = points[0].Y; Start[2] = points[0].Z;
	//Finish[0] = points[1].X; Finish[1] = points[1].Y; Finish[2] = points[1].Z;
	
	start_finish sf = gen.GetStartFinishIndex();
	Start[0] = sf.first.first;
	Start[1] = sf.first.second;
	Start[2] = 0;
	Finish[0] = sf.second.first;
	Finish[1] = sf.second.second;
	Finish[2] = 0;
	
	points = Generator.GetArrayOfEnemies();
	ArrayOfEnemies = new FVector[NumberOfEnemies];
	for (int i = 0; i < NumberOfEnemies; ++i) {
		ArrayOfEnemies[i][0] = points[i].X;
		ArrayOfEnemies[i][1] = points[i].Y;
		ArrayOfEnemies[i][2] = points[i].Z;
	}

	/*points = Generator.GetArrayOfBlocks();
	ArrayOfBlocks = new FVector[NumberOfBlocks];
	for (int j = 0; j < NumberOfBlocks; ++j) {
		ArrayOfBlocks[j][0] = points[j].X;
		ArrayOfBlocks[j][1] = points[j].Y;
		ArrayOfBlocks[j][2] = points[j].Z;
	}*/
}

bool AMyActor::GetCell(int i, int j) {
	return Matrix[i][j];
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

