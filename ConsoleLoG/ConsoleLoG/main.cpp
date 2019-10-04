#include "CellularAutomata.h"
#include <iostream>
#include <ctime>
#define TIME 100


void search(int x, int y, bool** field, int size)
{
	if (x >= size)
	{
		x = 0;
		y++;
	}
	else x++;
	if (y >= size)
	{
		GameOfLife gol = GameOfLife(size, size);
		gol.field = field;
		//gol.Show();
		int steps = 0;
		int alive = 1;
		clock_t time;
		time = clock();
		while (alive != gol.SumAlive() && alive != 0)
		{
			steps++;
			alive = gol.SumAlive();
			gol.Loop();
			//gol.Show();
			if (steps > 200)
			{
				
				while (true)
	{
		while (static_cast<float>(clock() - time) < TIME)
		{
		}
		system("cls");
		gol.Show();
		gol.Loop();
		time = clock();
		//system("pause");
	}
				break;
			}
			//std::cout << steps << std::endl;
		}
		//gol.Show();
		//std::cout << steps << std::endl;
	}
	else
	{
		field[y][x] = true;
		search(x, y, field, size);
		field[y][x] = false;
		search(x, y, field, size);
	}
}

int main()
{
	
	//GameOfLife gol = GameOfLife(1000, 1000);
	
	system("color F0");
	int size = 11;
	bool** field = new bool* [size];
	for (int i = 0; i < size; ++i)
	{
		field[i] = new bool[size];
		for (int j = 0; j < size; ++j)
			field[i][j] = true;
	}
	search(0, 0, field, size);
	auto gene = std::vector<bool>(countGenes, false);
	//birth(2, gene);
	//gene[2] = true;
	//gene[3] = true;
	//gene[4] = true;
	//gol.SetSurviveGene(gene);
	//gene[0] = true;

	clock_t time;
	time = clock();
	//gol.Loop();
	std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";

/*
	CellularAutomata gen = CellularAutomata(30);
	gen.Generate();*/


	//while (true)
	//{
	//	while (static_cast<float>(clock() - time) < TIME)
	//	{
	//	}
	//	system("cls");
	//	//gol.Show();
	//	gen.Generate();
	//	

	//	//gol.Loop();
	//	
	//	time = clock();
	//	system("pause");
	//}




	system("pause");
	return 0;
}