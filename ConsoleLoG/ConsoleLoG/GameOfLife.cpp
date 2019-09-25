#include "GameOfLife.h"
#include <windows.h>
#include <iostream>

void GameOfLife::InitField(int width, int height)
{
	fWidth = width;
	fHeight = height;
	field = new bool* [fHeight];
	for (int i = 0; i < fHeight; ++i)
	{
		field[i] = new bool[fWidth];
		for (int j = 0; j < fWidth; ++j)
			field[i][j] = false;
	}
}

bool GameOfLife::isAlive(int row, int column)
{
	if (row < 0) row += fHeight;
	if (row >= fHeight) row -= fHeight;
	if (column < 0) column += fWidth;
	if (column >= fWidth) column -= fWidth;
	return (field[row][column]);
}

bool GameOfLife::CellStatusNextLoop(int row, int column)
{
	int aliveNeighbors = 0;
	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
		{
			if ((i != 0 || j != 0) && isAlive(row + i, column + j))
				aliveNeighbors++;
		}
	return aliveNeighbors == 3 || (aliveNeighbors==2 && isAlive(row, column));
}

void GameOfLife::Loop()
{
	bool** tmp = new bool* [fHeight];
	for (int i = 0; i < fHeight; ++i)
	{
		tmp[i] = new bool[fWidth];
		for (int j = 0; j < fWidth; ++j)
			tmp[i][j] = CellStatusNextLoop(i, j);
	}
	field = tmp;
}

void GameOfLife::Show()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < fHeight; ++i)
	{
		for (int j = 0; j < fWidth; ++j)
		{
			
			if (field[i][j])
				SetConsoleTextAttribute(hConsole, (WORD)((4 << 4 | 4)));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 15)));
				std::cout << ' ';
		}
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
		std::cout << std::endl;
	}
	
}

void GameOfLife::Summon(int row, int column)
{
	if (row < 0) row += fHeight;
	if (row >= fHeight) row -= fHeight;
	if (column < 0) column += fWidth;
	if (column >= fWidth) column -= fWidth;
	field[row][column] = true;
}

void GameOfLife::InsertPattern(int x, int y, const Pattern& pattern)
{
	auto figure = pattern.GetPattern();
	size_t hei = pattern.X();
	size_t wid = pattern.Y();
	for (size_t i = 0; i < hei; i++)
	{
		for (size_t j = 0; j < wid; j++)
		{
			if (figure[i][j])
			{
				Summon(x + i, y + j);
			}
		}
	}
}