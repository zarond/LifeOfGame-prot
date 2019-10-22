#pragma once
#include "GameOfLife.h"
#include "GameField.h"



constexpr auto birthChance = 0.47;
constexpr int minRoomSquare = 20;


class CellularAutomata
{
public:
	CellularAutomata(int height, int width);
	~CellularAutomata();

	GameField* Generate();
	void Show();
private:
	GameOfLife* gol = nullptr;
	bool** field = nullptr;
	start_finish_t startAndFinish;
	int floorWidth;
	int floorHeight;
	
	vector_cord_t GetRoom(int, int);
	void ConnectNearestRoom(vector_cord_t&, std::vector<vector_cord_t>&);
	void ConnectRooms();
	void ConnectTwoRooms(vector_cord_t&, int, int, int, int);
	void CreateStartFinish(vector_cord_t&);
};
