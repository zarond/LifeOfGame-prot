#include "CellularAutomata.h"
#include <iostream>
#include <list>
#include <math.h>
#include <windows.h>

CellularAutomata::CellularAutomata(int size)
{
	floorSize = size;
	gol = new GameOfLife(floorSize, floorSize);
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

void CellularAutomata::Generate()
{
	
	for (size_t i = 0; i < floorSize; ++i)
	{
		for (size_t j = 0; j < floorSize; ++j)
		{
			if ((double)rand() / RAND_MAX < birthChance) gol->Summon(i, j); else gol->Kill(i, j);
			if (i == 0 || j == 0 || i == floorSize - 1 || j == floorSize - 1) gol->Summon(i, j);
		}
	}
	for (int i = 0; i < 20; ++i)
		gol->Loop();
	
	ConnectRooms();
}

void CellularAutomata::CreateLine(vectorOfIndex& room, int x1, int y1, int x2, int y2)
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
					room.push_back(std::pair<int, int>(x1 + k, y1 + t));
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

vectorOfIndex CellularAutomata::GetRoom(int x, int y)
{
	auto room = vectorOfIndex();
	room.push_back(std::pair<int, int>(x, y));
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
					room.push_back(std::pair<int, int>(x + j, y));
					++currentStep;
				}
				if (!field[x][y + j])
				{
					field[x][y + j] = true;
					room.push_back(std::pair<int, int>(x, y + j));
					++currentStep;
				}
			}

		}
		countAddOnStep = currentStep;
	}
	return room;
}

void CellularAutomata::ConnectNearestRoom(vectorOfIndex& room, std::vector<vectorOfIndex>& rooms)
{
	// finding room to connect
	int minDistance = floorSize * floorSize;
	int indexInRoom = 0;
	int indexInRooms = 0;
	int indexInNearestRoom = 0;

	for (size_t i = 0; i < rooms.size(); i++)
	{
		for (size_t j = 0; j < room.size(); j++)
		{
			for (size_t k = 0; k < rooms[i].size(); k++)
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

	CreateLine(room, x1, y1, x2, y2);

}

void CellularAutomata::ConnectRooms()
{
	field = gol->GetFieldCopy();
	auto rooms = std::vector<vectorOfIndex>();
	for (size_t i = 1; i < floorSize - 1; i++)
	{
		for (size_t j = 1; j < floorSize - 1; j++)
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
	field = gol->GetFieldCopy();
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
}

void CellularAutomata::Step()
{
	gol->Loop();
}

void CellularAutomata::Show()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < floorSize; ++i)
	{
		for (int j = 0; j < floorSize; ++j)
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