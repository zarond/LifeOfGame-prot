#pragma once
#include "Pattern.h"
class GameOfLife
{
private:
	bool** field;
	int fHeight;
	int fWidth;
	bool isAlive(int, int);
public:
	void InitField(int, int);
	
	bool CellStatusNextLoop(int, int);
	void Loop();
	void Show();
	void Summon(int, int);
	void InsertPattern(int, int, const Pattern&);
};

