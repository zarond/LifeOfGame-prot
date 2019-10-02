#include "CellularAutomata.h"
#include <iostream>
#include <ctime>
#define TIME 0


int main()
{
	std::srand(std::time(0));
	//GameOfLife gol = GameOfLife(1000, 1000);
	system("color F0");

	clock_t time;
	time = clock();
	//gol.Loop();
	std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";


	auto gen = CellularAutomata(40);
	//gen.Generate();



	while (true)
	{
		while (static_cast<float>(clock() - time) < TIME)
		{
		}
		system("cls");
		//gol.Show();
		gen.Generate();
		gen.Show();
		std::cout << (static_cast<float>(clock() - time)) / 1000 << "  sec\n";
		//gol.Loop();
		
		system("pause");
		time = clock();
	}
	system("pause");
	return 0;
}