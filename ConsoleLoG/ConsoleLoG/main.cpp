#include "GameOfLife.h"
#include <stdlib.h>



int main()
{
	GameOfLife gol = GameOfLife();
	system("color F0");
	gol.InitField(5, 5);
	gol.Summon(0, 0);
	gol.Summon(0, 1);
	gol.Summon(0, 2);
	for (int i = 0; i < 5; i++)
	{
		system("cls");
		gol.Show();
		
		gol.Loop();
		system("pause");
	}
	return 0;
}