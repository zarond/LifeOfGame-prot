#pragma once
#include "GameOfLife.h"

typedef std::vector<std::pair<int, int>> vectorOfIndex;
constexpr auto birthChance = 0.47;
constexpr int minRoomSquare = 20;


class CellularAutomata
{
private:
	GameOfLife* gol;
	bool** field;
	int floorSize;
	void CreateLine(vectorOfIndex&, int, int, int, int);
	vectorOfIndex GetRoom(int, int);
	void ConnectNearestRoom(vectorOfIndex&, std::vector<vectorOfIndex>&);
	void ConnectRooms();
public:
	CellularAutomata(int size);
	void Generate();
	void Step();
	void Show();
};

/* 
struct cell
{
	floor id
	object/enemy
	wallidright
	walliddown




}








*/