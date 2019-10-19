// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class TestGenerator
{
public:

	struct FVector {
		float X;
		float Y;
		float Z;
	};

	struct Cell {
		bool isEnemy;
		bool isBlock;
		bool isStart;
		bool isFinish;
	};

private:
	int Width;
	int Height;
	Cell** Cells;
	

public:
	TestGenerator();
	TestGenerator(int m, int n);
	~TestGenerator();

	bool** GetBlocks(); //we shouldn't use this in game; it's only for prototype
	int GetWidth();
	int GetHeight();
	int GetNumberOfEnemies();
	int GetNumberOfBlocks();
	FVector* GetArrayOfEnemies();
	FVector* GetArrayOfBlocks();
	FVector* GetStartAndFinish();

};
