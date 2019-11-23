// Fill out your copyright notice in the Description page of Project Settings.


#include "GoLUser.h"
#include "GameOfLife.h"
#include "MyActor.h"


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
		delete[] VisibleGoLField[i];
	}
	delete GoL;
	delete[] GoLField;
	delete[] VisibleGoLField;
	_birth = {};
	_survive = {};
	LavaPieces = {};
}

void AGoLUser::GenerateGoL(int width, int height, TArray<bool> birth, TArray<bool> survive, AMyActor* GlobalActor, int range, bool needClearSpace)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	//Generate GoL

	_width = width;
	_height = height;

	if (birth.Num() != 9) {
		_birth = TArray<bool>(defaultBirth);
		printf("Number of bools in birth is incorrect. Set default value.");
	}
	else {
		_birth = TArray<bool>(birth);
	}

	if (survive.Num() != 9) {
		_survive = TArray<bool>(defaultSurvive);
		printf("Number of bools in survive is incorrect. Set default value.");
	}
	else {
		_survive = TArray<bool>(survive);
	}
	
	std::vector<bool> bgene = std::vector<bool>();
	std::vector<bool> sgene = std::vector<bool>();
	for (int i = 0; i < 9; ++i) {
		bgene.push_back(_birth[i]);
		sgene.push_back(_survive[i]);
	}

	GoL = new GameOfLife(_width, _height);
	GoL->SetBirthGene(bgene);
	GoL->SetSurviveGene(sgene);

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			if ((double)rand() / RAND_MAX < birthChance) GoL->Summon(i, j); else GoL->Kill(i, j);
			if (i == 0 || j == 0 || i == _height - 1 || j == _width - 1) GoL->Summon(i, j);
		}
	}

	GoLField = GoL->GetFieldCopy();


	//Generate Visible GoL

	bool** matrix = new bool* [_height];
	for (int i = 0; i < _height; ++i) {
		matrix[i] = new bool[_width];
		for (int j = 0; j < _width; ++j) {
			matrix[i][j] = (GoLField[i][j] && GlobalActor->GetCell_IsOccupied(i, j) != 1 && GlobalActor->GetCell_IsOccupied(i, j) != 3);
		}
	}

	VisibleGoLField = matrix;

	if (needClearSpace) ClearCreaturesSpace(GlobalActor);
}

void AGoLUser::ClearCreaturesSpace(AMyActor* GlobalActor, int range) {
	FIntVector vect;
	for (int k = 0; k < GlobalActor->GetNumberOfEnemies(); ++k) {
		vect = GlobalActor->GetEnemyPosition(k);
		ClearSpace(vect[0], vect[1], range);
	}

	vect = GlobalActor->GetStartPosition();
	ClearSpace(vect[0], vect[1], range);

	vect = GlobalActor->GetFinishPosition();
	ClearSpace(vect[0], vect[1], range);
}

void AGoLUser::UpdateGoL(TArray<bool> birth, TArray<bool> survive, AMyActor* GlobalActor, int range, bool needClearSpace)
{

	//Update GoL

	if (birth.Num() != 9) {
		_birth = TArray<bool>(defaultBirth);
		printf("Number of bools in birth is incorrect. Set default value.");
	}
	else {
		_birth = TArray<bool>(birth);
	}

	if (survive.Num() != 9) {
		_survive = TArray<bool>(defaultSurvive);
		printf("Number of bools in survive is incorrect. Set default value.");
	}
	else {
		_survive = TArray<bool>(survive);
	}


	std::vector<bool> bgene = std::vector<bool>();
	std::vector<bool> sgene = std::vector<bool>();
	for (int i = 0; i < 9; ++i) {
		bgene.push_back(_birth[i]);
		sgene.push_back(_survive[i]);
	}

	GoL->SetBirthGene(bgene);
	GoL->SetSurviveGene(sgene);

	GoL->Loop();

	GoLField = GoL->GetFieldCopy();


	//Update Visible GoL

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			VisibleGoLField[i][j] = (GoLField[i][j] && GlobalActor->GetCell_IsOccupied(i, j) != 1 && GlobalActor->GetCell_IsOccupied(i, j) != 3);
		}
	}

	if (needClearSpace) {
		FIntVector vect;
		vect = GlobalActor->GetStartPosition();
		ClearSpace(vect[0], vect[1], range);

		vect = GlobalActor->GetFinishPosition();
		ClearSpace(vect[0], vect[1], range);
	}
}

bool AGoLUser::IsAlive(int x, int y) const {
	return VisibleGoLField[x][y];
}

bool AGoLUser::WillBeAlive(int x, int y) const {
	return GoL->CellStatusNextLoop(x, y);
}

void AGoLUser::ClearSpace(int x, int y, int range) {
	for (int i = 1 - range; i < range; ++i) {
		for (int j = 1 - range; j < range; ++j) {
			if (x + i >= 0 && y + j >= 0 && x + i < _height && y + j < _width) {
				VisibleGoLField[x + i][y + j] = false;
			}
		}
	}
}

TArray<AActor*> AGoLUser::UpdateLavaPiecesOnField(int polygon_size) {
	for (int i = 0; i < LavaPieces.Num(); ++i)
	{
		LavaPieces[i]->Destroy();
	}

	LavaPieces.Empty();

	LavaPieces = TArray<AActor*>();
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			if (VisibleGoLField[i][j]) {
				//FVector Location((i + 0.5) * polygon_size, (j + 0.5) * polygon_size, 0.25 * polygon_size);
                FVector Location((i + 0.5) * polygon_size, (j + 0.5) * polygon_size, -0.1 * polygon_size);
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AActor* piece = GetWorld()->SpawnActor<AActor>(ToSpawn, Location, Rotation, SpawnInfo);
				LavaPieces.Add(piece);
			}
		}
	}

	return LavaPieces;
}



