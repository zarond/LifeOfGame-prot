#pragma once
#include "Pattern.h"

#define countGenes 9

class GameOfLife
{
private:
	bool** fieldCopy;
	bool** field;
	bool* birth;
	bool* survive;
	int fHeight;
	int fWidth;
	bool immortalWalls = false;
	bool isAlive(int, int) const;
	bool isWall(int, int) const;
public:
	GameOfLife(const int, const int);
	
	bool CellStatusNextLoop(int, int) const;
	const bool* const* GetField() const;
	bool** GetFieldCopy() const;
	const boolXbool GetFieldVectors() const;
	void Loop();
	void Loop(const int);
	void Show() const;
	void Summon(int, int);
	void Kill(int, int);
	void InsertPattern(const int, const int, const Pattern&);
	void SetBirthGene(const std::vector<bool>&);
	void SetSurviveGene(const std::vector<bool>&);
	void SetImmortalWalls(bool);
};

