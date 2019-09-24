#pragma once
class GameOfLife
{
private:
	bool** field;
	int fHeight;
	int fWidth;
	bool isAlive(int row, int column);
public:
	void InitField(int width, int height);
	bool CellStatusNextLoop(int row, int column);
	void Loop();
	void Show();
	void Summon(int row, int column);
};

