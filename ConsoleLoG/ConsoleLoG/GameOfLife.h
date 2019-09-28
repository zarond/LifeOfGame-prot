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
	bool isAlive(int, int) const;
public:
	void InitField(const int, const int);
	
	bool CellStatusNextLoop(int, int) const;
	const bool* const* const GetField() const;
	const boolXbool GetFieldVectors() const;
	void Loop();
	void Loop(const int);
	void Show() const;
	void Summon(int, int);
	void InsertPattern(const int, const int, const Pattern&);
	void SetBirthGene(const std::vector<bool>&);
	void SetSurviveGene(const std::vector<bool>&);
};

