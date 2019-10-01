#include "GameOfLife.h"
#include "CellularAutomata.h"
#include <iostream>
#include <ctime>
#define TIME 500


int main()
{
	std::srand(std::time(0));
	//GameOfLife gol = GameOfLife(1000, 1000);
	system("color F0");
	//auto gene = std::vector<bool>(countGenes, false);
	//gene[2] = true;
	//gene[3] = true;
	//gene[4] = true;
	//gol.SetSurviveGene(gene);
	//gene[0] = true;

	////gol.SetBirthGene(gene);
	//Pattern pattern = Pattern(1);
	//for (size_t j = 0; j < 10; j++)
	//{
	//	for (size_t i = 0; i < 15; i++)
	//	{
	//		pattern = Pattern(2 * i + 1);
	//		gol.InsertPattern(100 * j, i * 10, pattern);

	//		pattern = Pattern(2 * i + 2);
	//		gol.InsertPattern(100 * j + 50,  i * 10, pattern);
	//	}
	//}

	//pattern = Pattern(31);
	//gol.InsertPattern(0, 0, pattern);

	clock_t time;
	time = clock();
	//gol.Loop();
	std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";


	CellularAutomata gen = CellularAutomata(30);
	gen.Generate();


	while (true)
	{
		while (static_cast<float>(clock() - time) < TIME)
		{
		}
		system("cls");
		//gol.Show();
		gen.Generate();
		

		//gol.Loop();
		
		time = clock();
		system("pause");
	}
	system("pause");
	return 0;
}