#pragma once
#include "GameOfLife.h"

typedef std::vector<std::pair<int, int>> vectorOfIndex;
typedef std::pair<std::pair<int, int>, std::pair<int, int>> start_finish;
constexpr auto birthChance = 0.47;
constexpr int minRoomSquare = 20;


class CellularAutomata
{
private:
	GameOfLife* gol;
	bool** field;
	start_finish start_finish;
	int floorSize;
	void CreateLine(vectorOfIndex&, int, int, int, int);
	vectorOfIndex GetRoom(int, int);
	void ConnectNearestRoom(vectorOfIndex&, std::vector<vectorOfIndex>&);
	void ConnectRooms();
	void CreateStartFinish(vectorOfIndex&);
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