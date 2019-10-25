#include "CellularAutomata.h"
#include <iostream>
#include <list>
#include <math.h>
//#include <windows.h>
#include <ctime>
#include <algorithm>

CellularAutomata::CellularAutomata(int height, int width)
{
	floorWidth = width;
	floorHeight = height;
	gol = new GameOfLife(floorWidth, floorHeight);
	auto rule = std::vector<bool>(countGenes, true);
	rule[0] = false;
	rule[1] = false;
	rule[2] = false;
	rule[3] = false;
	gol->SetSurviveGene(rule);
	rule[4] = false;
	gol->SetBirthGene(rule);
	rule[5] = false;
	rule[6] = false;
	gol->SetImmortalWalls(true);
}

CellularAutomata::~CellularAutomata()
{
	if (field != nullptr)
	{
		for (int i = 0; i < floorHeight; i++)
		{
			delete[] field[i];
		}
		delete[] field;
	}
	if (gol != nullptr)
		delete gol;
}

GameField* CellularAutomata::Generate()
{
	
	for (int i = 0; i < floorHeight; ++i)
		for (int j = 0; j < floorWidth; ++j)
		{
			if ((double)rand() / RAND_MAX < birthChance) 
				gol->SetCell(i, j, true);
			else 
				gol->SetCell(i, j, false);
			if (i == 0 || j == 0 || i == floorHeight - 1 || j == floorWidth - 1)
				gol->SetCell(i, j, true);
		}

	for (int i = 0; i < 20; ++i)
		gol->Loop();
	
	ConnectRooms();
	auto game = new GameField(field, floorHeight, floorWidth, startAndFinish);
	field = nullptr;
	return game;
}

void CellularAutomata::ConnectTwoRooms(vector_cord_t& room, int x1, int y1, int x2, int y2)
{
	int dx = 0;
	if (x1 != x2)
	{
		dx = (x2 - x1) / abs(x2 - x1);
	}
	int dy = 0;
	if (y1 != y2)
	{
		dy = (y2 - y1) / abs(y2 - y1);
	}
	
	while (x1 != x2 || y1 != y2)
	{

		for (int k = -1; k < 2; ++k)
		{
			for (int t = -1; t < 2; ++t)
			{
				if (field[x1 + k][y1 + t])
				{
					room.push_back(cord_t(x1 + k, y1 + t));
					field[x1 + k][y1 + t] = false;
				}
			}
		}
		if (x1 != x2)
		{
			x1 += dx;
		}
		if (y1 != y2)
		{
			y1 += dy;
		}
	}	
}

vector_cord_t CellularAutomata::GetRoom(int x, int y)
{
	auto room = vector_cord_t();
	room.push_back(cord_t(x, y));
	field[x][y] = true;
	int countAddOnStep = 1;
	// BFS
	while (countAddOnStep > 0)
	{
		int currentStep = 0;
		int vecSize = room.size();
		for (int i = vecSize - countAddOnStep; i < vecSize; ++i)
		{
			x = room[i].first;
			y = room[i].second;
			for (int j = -1; j < 2; j += 2)
			{
				if (!field[x + j][y])
				{
					field[x + j][y] = true;
					room.push_back(cord_t(x + j, y));
					++currentStep;
				}
				if (!field[x][y + j])
				{
					field[x][y + j] = true;
					room.push_back(cord_t(x, y + j));
					++currentStep;
				}
			}

		}
		countAddOnStep = currentStep;
	}
	return room;
}

void CellularAutomata::ConnectNearestRoom(vector_cord_t& room, std::vector<vector_cord_t>& rooms)
{
	// finding room to connect
	int minDistance = floorHeight * floorWidth;
	int indexInRoom = 0;
	int indexInRooms = 0;
	int indexInNearestRoom = 0;

	for (size_t i = 0; i < rooms.size(); ++i)
	{
		for (size_t j = 0; j < room.size(); ++j)
		{
			for (size_t k = 0; k < rooms[i].size(); ++k)
			{
				int x1 = room[j].first;
				int y1 = room[j].second;
				int x2 = rooms[i][k].first;
				int y2 = rooms[i][k].second;

				int dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
				if (minDistance > dist)
				{
					minDistance = dist;
					indexInRooms = i;
					indexInRoom = j;
					indexInNearestRoom = k;
				}
			}
		}
	}


	int x1 = room[indexInRoom].first;
	int y1 = room[indexInRoom].second;
	int x2 = rooms[indexInRooms][indexInNearestRoom].first;
	int y2 = rooms[indexInRooms][indexInNearestRoom].second;
	room.insert(room.end(), rooms[indexInRooms].begin(), rooms[indexInRooms].end());
	rooms.erase(rooms.cbegin() + indexInRooms);

	ConnectTwoRooms(room, x1, y1, x2, y2);

}

void CellularAutomata::ConnectRooms()
{
	field = gol->GetFieldCopy();
	auto rooms = std::vector<vector_cord_t>();
	for (int i = 1; i < floorHeight - 1; i++)
	{
		for (int j = 1; j < floorWidth - 1; j++)
		{
			if (!field[i][j])
			{
				auto room = GetRoom(i, j);
				if (room.size() >= minRoomSquare)
				{
					rooms.push_back(room);
				}
				//ConnectTwoRooms(room, GetRoom(fileld, i, j));
			}
		}
	}
	gol->GetFieldCopy(field);
	if (rooms.size() == 0)
	{
		return;
	}
	auto room = rooms[rooms.size() - 1];
	rooms.pop_back();
	while (rooms.size() > 0)
	{
		ConnectNearestRoom(room, rooms);
	}
	CreateStartFinish(room);
}

void CellularAutomata::CreateStartFinish(vector_cord_t& room)
{

	// divide field on 9 equal parts for finding (x,y) out center part
	int centerLeft = floorWidth / 3 - 1;
	int centerRight = floorWidth - centerLeft;
	double percentLength = 1.4;
	// finding broad cells
	auto broadcells = vector_cord_t();
	for (size_t i = 0; i < room.size(); ++i)
	{
		auto cell = room[i];
		int x = cell.first;
		int y = cell.second;
		if ((field[x + 1][y] || field[x - 1][y]
			|| field[x][y + 1] || field[x][y - 1])
			 && (x < centerLeft || x > centerRight || y < centerLeft || y > centerRight))
			broadcells.push_back(cell);
	}

	std::srand((unsigned int)std::time(0));

	auto cell = broadcells[rand() % broadcells.size()];
	int x = cell.first;
	int y = cell.second;

	std::sort(broadcells.begin(), broadcells.end(),
		[x, y](cord_t cell1, cord_t cell2)
		{
			int dist1 = (x - cell1.first) * (x - cell1.first) +
				abs(y - cell1.second) * abs(y - cell1.second);
			int dist2 = (x - cell2.first) * (x - cell2.first) +
				abs(y - cell2.second) * abs(y - cell2.second);
			return dist1 > dist2;
		});

	// get from 20% most far
	cell = broadcells[rand() % (broadcells.size() / 5)];
	x = cell.first;
	y = cell.second;
	startAndFinish.first.first = x;
	startAndFinish.first.second = y;

	std::sort(broadcells.begin(), broadcells.end(),
		[x, y](cord_t cell1, cord_t cell2)
		{
			int dist1 = (x - cell1.first) * (x - cell1.first) +
				abs(y - cell1.second) * abs(y - cell1.second);
			int dist2 = (x - cell2.first) * (x - cell2.first) +
				abs(y - cell2.second) * abs(y - cell2.second);
			return dist1 > dist2;
		});

	cell = broadcells[rand() % (broadcells.size() / 5)];
	startAndFinish.second.first = cell.first;
	startAndFinish.second.second = cell.second;
}

//void CellularAutomata::Show()
//{
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	for (int i = 0; i < floorHeight; ++i)
//	{
//		for (int j = 0; j < floorWidth; ++j)
//		{
//			if ((i == startAndFinish.first.first && 
//				j == startAndFinish.first.second)
//				|| (i == startAndFinish.second.first &&
//					j == startAndFinish.second.second))
//				SetConsoleTextAttribute(hConsole, (WORD)((2 << 4 | 2)));
//			else if (field[i][j])
//				SetConsoleTextAttribute(hConsole, (WORD)((4 << 4 | 4)));
//			else
//				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 15)));
//			std::cout << ' ';
//		}
//		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
//		std::cout << std::endl;
//	}
//}