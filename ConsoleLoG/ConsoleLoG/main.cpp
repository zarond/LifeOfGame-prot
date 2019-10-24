#include "CellularAutomata.h"
#include <iostream>
#include <ctime>
#define TIME 0


int main()
{
	std::srand(std::time(0));
	GameOfLife gol = GameOfLife(5, 5);
	system("color F0");
	gol.Summon(1, 2);
	gol.Summon(2, 2);
	gol.Summon(3, 2);
	clock_t time;
	time = clock();
	//gol.Loop();
	std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";


	//auto gen = CellularAutomata(30,119);
	//gen.Generate();



	while (true)
	{
		while (static_cast<float>(clock() - time) < TIME)
		{
		}
		system("cls");
		//gol.Show();
		//gen.Generate();
		//gen.Show();
		//std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";
		//std::cout << gen.GetFloorHeight() << "  " << gen.GetFloorWidth() << std::endl;
		//std::cout << gen.GetStartFinishIndex().first.first << " " << gen.GetStartFinishIndex().first.second << std::endl;
		//std::cout << gen.GetStartFinishIndex().second.first << " " << gen.GetStartFinishIndex().second.second << std::endl;
		//gol.Loop();
		gol.Show();
		gol.Loop();
		system("pause");
		time = clock();
	}
	system("pause");
	return 0;
}