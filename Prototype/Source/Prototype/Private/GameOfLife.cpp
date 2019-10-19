#include "GameOfLife.h"
//#include <windows.h>
#include "Windows/MinWindows.h"
#include <iostream>


GameOfLife::GameOfLife(const int width, const int height)
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

bool GameOfLife::isWall(int row, int column) const
{
	return (row == 0 || column == 0 || row == fHeight - 1 || column == fWidth - 1);
}

bool GameOfLife::CellStatusNextLoop(int row, int column) const
{
	int aliveNeighbors = 0;
	bool itIsAlive;
	// calculating alive neighbors
	for (int i = -1; i < 2; ++i)
	{
		int x;
		int y;
		for (int j = -1; j < 2; ++j)
		{
			//
			x = row + i;
			y = column + j;
			if (x < 0) x += fHeight;
			if (x >= fHeight) x -= fHeight;
			if (y < 0) y += fWidth;
			if (y >= fWidth) y -= fWidth;
			itIsAlive = field[x][y];
			//
			if ((i != 0 || j != 0) && itIsAlive)
				aliveNeighbors++;
		}
	}
	// checking if cell is already alive
	if (row < 0) row += fHeight;
	if (row >= fHeight) row -= fHeight;
	if (column < 0) column += fWidth;
	if (column >= fWidth) column -= fWidth;
	itIsAlive = field[row][column];
	// approving with rules
	return (birth[aliveNeighbors] && !itIsAlive) || (survive[aliveNeighbors] && itIsAlive);
}

void GameOfLife::Loop()
{
	// writing to field copy new state
	for (int i = 0; i < fHeight; ++i)
		for (int j = 0; j < fWidth; ++j)
		{
			// CellStatusNextLoop
			int aliveNeighbors = 0;
			bool itIsAlive;
			for (int k = -1; k < 2; ++k)
			{
				int x;
				int y;
				for (int t = -1; t < 2; ++t)
				{
					if (t != 0 || k != 0)
					{
						// isAlive
						x = i + k;
						y = j + t;
						if (x < 0) x += fHeight;
						if (x >= fHeight) x -= fHeight;
						if (y < 0) y += fWidth;
						if (y >= fWidth) y -= fWidth;
						//
						if  (field[x][y])
							aliveNeighbors++;
					}
				}
			}
			// isAlive
			if (i < 0) i += fHeight;
			if (i >= fHeight) i -= fHeight;
			if (j < 0) j += fWidth;
			if (j >= fWidth) j -= fWidth;
			itIsAlive = field[i][j];
			//
			bool cellStatusNextLoop = (birth[aliveNeighbors] && !itIsAlive) || (survive[aliveNeighbors] && itIsAlive);
			if (immortalWalls) // it can be faster
				cellStatusNextLoop = cellStatusNextLoop || isWall(i, j);
			fieldCopy[i][j] = cellStatusNextLoop;
			//
		}
	// writing to field from field copy
	bool** temp = fieldCopy;
	fieldCopy = field;
	field = temp;
}

void GameOfLife::Loop(const int count)
{
	for (int i = 0; i < count; ++i)
	{
		Loop();
	}
}

const bool*const* GameOfLife::GetField() const
{
	return field;
}

bool** GameOfLife::GetFieldCopy() const
{
	auto exportField = new bool* [fHeight];
	for (size_t i = 0; i < fHeight; i++)
	{
		exportField[i] = new bool[fWidth];
		for (size_t j = 0; j < fWidth; j++)
		{
			exportField[i][j] = field[i][j];
		}
	}
	return exportField;
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

//void GameOfLife::Show() const
//{
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	for (int i = 0; i < fHeight; ++i)
//	{
//		for (int j = 0; j < fWidth; ++j)
//		{
//			
//			if (field[i][j])
//				SetConsoleTextAttribute(hConsole, (WORD)((4 << 4 | 4)));
//			else
//				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 15)));
//				std::cout << ' ';
//		}
//		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
//		std::cout << std::endl;
//	}
//}

void GameOfLife::Summon(int row, int column)
{
	if (row < 0) row += fHeight;
	if (row >= fHeight) row -= fHeight;
	if (column < 0) column += fWidth;
	if (column >= fWidth) column -= fWidth;
	field[row][column] = true;
}

void GameOfLife::Kill(int row, int column)
{
	if (row < 0) row += fHeight;
	if (row >= fHeight) row -= fHeight;
	if (column < 0) column += fWidth;
	if (column >= fWidth) column -= fWidth;
	field[row][column] = false;
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

void GameOfLife::SetImmortalWalls(bool areImmortal)
{
	immortalWalls = areImmortal;
}