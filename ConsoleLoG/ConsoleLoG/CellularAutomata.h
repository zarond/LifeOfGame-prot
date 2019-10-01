#pragma once
#include "GameOfLife.h"


class CellularAutomata
{
private:
	GameOfLife* gol;
	double birthChance = 0.47;
	int floorSize;
public:
	CellularAutomata(int size);
	void Generate();
	void Step();
	void Show();
};

/* 
struct cell
{
	floor id
	object/enemy
	wallidright
	walliddown




}








*/