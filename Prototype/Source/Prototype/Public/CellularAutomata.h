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
	start_finish startAndFinish;
	int floorWidth;
	int floorHeight;
	void CreateLine(vectorOfIndex&, int, int, int, int);
	vectorOfIndex GetRoom(int, int);
	void ConnectNearestRoom(vectorOfIndex&, std::vector<vectorOfIndex>&);
	void ConnectRooms();
	void CreateStartFinish(vectorOfIndex&);
public:
	CellularAutomata(int height, int width);
	void Generate();
	void Step();
	void Show();

	bool** GetFloorMap() const;
	start_finish GetStartFinishIndex() const;
	int GetFloorWidth() const;
	int GetFloorHeight() const;
};
