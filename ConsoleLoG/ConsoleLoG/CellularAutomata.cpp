#include "CellularAutomata.h"
#include <iostream>

CellularAutomata::CellularAutomata(int size)
{
	floorSize = size;
	gol = new GameOfLife(floorSize, floorSize);
	auto rule = std::vector<bool>(countGenes, true);
	rule[0] = false;
	rule[1] = false;
	rule[2] = false;
	rule[3] = false;
	rule[4] = false;
	gol->SetSurviveGene(rule);
	rule[5] = false;
	gol->SetBirthGene(rule);
	rule[6] = false;
	gol->SetImmortalWalls(true);
}

void CellularAutomata::Generate()
{
	
	for (size_t i = 0; i < floorSize; ++i)
	{
		for (size_t j = 0; j < floorSize; ++j)
		{
			if ((double)rand() / RAND_MAX < birthChance) gol->Summon(i, j);
			if (i == 0 || j == 0 || i == floorSize - 1 || j == floorSize - 1) gol->Summon(i, j);
		}
	}
}

void CellularAutomata::Step()
{
	gol->Loop();
}

void CellularAutomata::Show()
{
	gol->Show();
}