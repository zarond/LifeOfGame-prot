#include "GameOfLife.h"
#include <iostream>
#include <ctime>
#define TIME 300


int main()
{
	GameOfLife gol = GameOfLife();
	system("color F0");
	gol.InitField(1000, 1000);
	auto gene = std::vector<bool>(countGenes, false);
	//gene[2] = true;
	//gene[3] = true;
	//gene[4] = true;
	//gol.SetSurviveGene(gene);
	//gene[0] = true;

	//gol.SetBirthGene(gene);
	Pattern pattern = Pattern(1);
	for (size_t j = 0; j < 10; j++)
	{
		for (size_t i = 0; i < 15; i++)
		{
			pattern = Pattern(2 * i + 1);
			gol.InsertPattern(100 * j, i * 10, pattern);

			pattern = Pattern(2 * i + 2);
			gol.InsertPattern(100 * j + 50,  i * 10, pattern);
		}
	}

	clock_t time;
	time = clock();
	gol.Loop();
	std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";


	while (false)
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
	system("pause");
	return 0;
}