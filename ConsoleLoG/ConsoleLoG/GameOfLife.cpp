#include "GameOfLife.h"
#include <windows.h>
#include <iostream>

void GameOfLife::InitField(const int width, const int height)
{
	fWidth = width;
	fHeight = height;
	// initialization vectors and copy vectors

	field = new bool* [fHeight];
	fieldCopy = new bool* [fHeight];
	for (size_t i = 0; i < fHeight; i++)
	{
		field[i] = new bool[fWidth] {false};
		fieldCopy[i] = new bool[fWidth] {false};
	}
	birth = new bool[countGenes] {false};
	survive = new bool[countGenes] {false};

	birth[3] = true;
	survive[2] = true;
	survive[3] = true;
}

bool GameOfLife::isAlive(int row, int column) const
{
	if (row < 0) row += fHeight;
	if (row >= fHeight) row -= fHeight;
	if (column < 0) column += fWidth;
	if (column >= fWidth) column -= fWidth;
	return field[row][column];
}

bool GameOfLife::CellStatusNextLoop(const int row, const int column) const
{
	int aliveNeighbors = 0;
	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
		{
			if ((i != 0 || j != 0) && isAlive(row + i, column + j))
				aliveNeighbors++;
		}
	bool itIsAlive = isAlive(row, column);
	return (birth[aliveNeighbors] && ~itIsAlive) || (survive[aliveNeighbors] && itIsAlive);
}

void GameOfLife::Loop()
{
	// writing to field copy new state
	for (int i = 0; i < fHeight; ++i)
		for (int j = 0; j < fWidth; ++j)
			fieldCopy[i][j] = CellStatusNextLoop(i, j);
	// writing to field from field copy
	for (int i = 0; i < fHeight; ++i)
		for (int j = 0; j < fWidth; ++j)
			field[i][j] = fieldCopy[i][j];
}

void GameOfLife::Loop(const int count)
{
	for (int i = 0; i < count; ++i)
	{
		Loop();
	}
}

const bool*const* const GameOfLife::GetField() const
{
	return field;
}

const boolXbool GameOfLife::GetFieldVectors() const
{
	auto exportField = boolXbool(fHeight, std::vector<bool>(fWidth));
	for (size_t i = 0; i < fHeight; i++)
	{
		for (size_t j = 0; j < fWidth; j++)
		{
			exportField[i][j] = field[i][j];
		}
	}
	return exportField;
}

void GameOfLife::Show() const
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

void GameOfLife::InsertPattern(const int x, const int y, const Pattern& pattern)
{const
	auto figure = pattern.GetPattern();
	size_t hei = pattern.Height();
	size_t wid = pattern.Width();
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

void GameOfLife::SetBirthGene(const std::vector<bool>& gene)
{
	for (size_t i = 0; i < countGenes && i < gene.size(); i++)
	{
		birth[i] = gene[i];
	}
}

void GameOfLife::SetSurviveGene(const std::vector<bool>& gene)
{
	for (size_t i = 0; i < countGenes && i < gene.size(); i++)
	{
		survive[i] = gene[i];
	}
}