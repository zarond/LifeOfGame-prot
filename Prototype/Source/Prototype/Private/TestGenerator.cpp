// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGenerator.h"
#include <time.h>
#include <stdlib.h>

TestGenerator::TestGenerator(int m, int n) {
	Width = m;
	Height = n;
	Cells = new Cell * [Width];
	for (int i = 0; i < Width; ++i) {
		Cells[i] = new Cell[Height];
		for (int j = 0; j < Height; ++j) {
			Cells[i][j].isBlock = false;
			Cells[i][j].isEnemy = false;
			Cells[i][j].isStart = false;
			Cells[i][j].isFinish = false;
		}
	}
}

TestGenerator::TestGenerator() {
	srand(time(NULL));
	Width = rand() % 253 + 4;
	Height = rand() % 253 + 4;
	Cells = new Cell * [Width];
	for (int i = 0; i < Width; ++i) {
		Cells[i] = new Cell[Height];
		for (int j = 0; j < Height; ++j) {
			Cells[i][j].isBlock = false;
			Cells[i][j].isEnemy = false;
			Cells[i][j].isStart = false;
			Cells[i][j].isFinish = false;
		}
	}
}

TestGenerator::~TestGenerator() {
	for (int i = 0; i < Width; ++i) delete[] Cells[i];
	delete[] Cells;
}

bool** TestGenerator::GetBlocks() {
	srand(time(NULL));
	bool** matrix = new bool*[Width];

	for (int i = 0; i < Width; ++i) {
		matrix[i] = new bool[Height];
		for (int j = 0; j < Height; ++j) {
			Cells[i][j].isBlock = matrix[i][j] = false;
		}
	}

	int count = GetNumberOfBlocks();
	int k, l;

	for (int counter = 0; counter < count; ++counter) {
		k = rand() % Width;
		l = rand() % Height;
		if (!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish) {
			Cells[k][l].isBlock = matrix[k][l] = true;
		}
		else {
			--counter;
		}
	}

	return matrix;
}

int TestGenerator::GetWidth() {
	return TestGenerator::Width;
}

int TestGenerator::GetHeight() {
	return TestGenerator::Height;
}

int TestGenerator::GetNumberOfEnemies() {
	return Width * Height / 50 + 1;
}

int TestGenerator::GetNumberOfBlocks() {
	return Width * Height / 5;
}

TestGenerator::FVector* TestGenerator::GetArrayOfEnemies() {
	srand(time(NULL));
	
	for (int i = 0; i < Width; ++i) {
		for (int j = 0; j < Height; ++j) {
			Cells[i][j].isEnemy = false;
		}
	}

	int count = GetNumberOfEnemies();
	int k, l;

	FVector* ArrayOfEnemies = new FVector[count];
	for (int counter = 0; counter < count; ++counter) {
		k = rand() % Width;
		l = rand() % Height;
		if (!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish) {
			Cells[k][l].isEnemy = true;
			ArrayOfEnemies[counter].X = k;
			ArrayOfEnemies[counter].Y = l;
			ArrayOfEnemies[counter].Z = 0.;
		}
		else --counter;
	}

	return ArrayOfEnemies;
}

TestGenerator::FVector* TestGenerator::GetArrayOfBlocks() {
	srand(time(NULL));

	for (int i = 0; i < Width; ++i) {
		for (int j = 0; j < Height; ++j) {
			Cells[i][j].isBlock = false;
		}
	}

	int count = GetNumberOfBlocks();
	int k, l;

	FVector* ArrayOfBlocks = new FVector[count];
	for (int counter = 0; counter < count; ++counter) {
		k = rand() % Width;
		l = rand() % Height;
		if (!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish) {
			Cells[k][l].isBlock = true;
			ArrayOfBlocks[counter].X = k;
			ArrayOfBlocks[counter].Y = l;
			ArrayOfBlocks[counter].Z = 0.;
		}
		else --counter;
	}

	return ArrayOfBlocks;
}

TestGenerator::FVector* TestGenerator::GetStartAndFinish() {
	srand(time(NULL));

	for (int i = 0; i < Width; ++i) {
		for (int j = 0; j < Height; ++j) {
			Cells[i][j].isStart = false;
			Cells[i][j].isFinish = false;
		}
	}

	int k, l;
	FVector* Points = new FVector[2];
	switch (rand() % 4) {
	case 0:
	{
		do {
			k = 0;
			l = rand() % Height;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish));
		int oldl = l;
		Points[0].X = k;
		Points[0].Y = l;
		Points[0].Z = 0;
		Cells[k][l].isStart = true;

		do {
			k = Width - 1;
			l = rand() % Height;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish && abs(oldl - l) > Height / 4));
		Points[1].X = k;
		Points[1].Y = l;
		Points[1].Z = 0;
		Cells[k][l].isFinish = true;
		break;
	}
	case 1:
	{
		do {
			k = rand() % Width;
			l = Height - 1;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish));
		int oldk = k;
		Points[0].X = k;
		Points[0].Y = l;
		Points[0].Z = 0;
		Cells[k][l].isStart = true;

		do {
			k = rand() % Width;
			l = 0;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish && abs(oldk - k) > Width / 4));
		Points[1].X = k;
		Points[1].Y = l;
		Points[1].Z = 0;
		Cells[k][l].isFinish = true;
		break;
	}
	case 2:
	{
		do {
			k = Width - 1;
			l = rand() % Height;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish));
		int oldl = l;
		Points[0].X = k;
		Points[0].Y = l;
		Points[0].Z = 0;
		Cells[k][l].isStart = true;

		do {
			k = 0;
			l = rand() % Height;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish && abs(oldl - l) > Height / 4));
		Points[1].X = k;
		Points[1].Y = l;
		Points[1].Z = 0;
		Cells[k][l].isFinish = true;
		break;
	}
	case 3:
	{
		do {
			k = rand() % Width;
			l = 0;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish));
		int oldk = k;
		Points[0].X = k;
		Points[0].Y = l;
		Points[0].Z = 0;
		Cells[k][l].isStart = true;

		do {
			k = rand() % Width;
			l = Height - 1;
		} while (!(!Cells[k][l].isBlock && !Cells[k][l].isEnemy && !Cells[k][l].isStart && !Cells[k][l].isFinish && abs(oldk - k) > Width / 4));
		Points[1].X = k;
		Points[1].Y = l;
		Points[1].Z = 0;
		Cells[k][l].isFinish = true;
		break;
	}
	}
	return Points;
}
