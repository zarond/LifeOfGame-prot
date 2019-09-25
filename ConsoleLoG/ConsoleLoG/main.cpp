#include "GameOfLife.h"
#include <iostream>
#include <ctime>
#define TIME 400


int main()
{
	GameOfLife gol = GameOfLife();
	system("color F0");
	gol.InitField(150, 20);
	Pattern pattern = Pattern(1);
	for (size_t i = 0; i < 15; i++)
	{
		pattern = Pattern(2 * i + 1);
		gol.InsertPattern(0, i * 10, pattern);

		pattern = Pattern(2 * i + 2);
		gol.InsertPattern(10, i * 10, pattern);
	}

	clock_t time;
	time = clock();

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
	return 0;
}