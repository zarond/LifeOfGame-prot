#pragma once
#include <string>
#include <vector>
typedef std::vector<std::vector<bool>> boolXbool;

class Pattern
{
private:
	int id = 0;
	std::string name = "";
	boolXbool pattern;
	int height = 0;
	int width = 0;

	static boolXbool PreparePatrernArr(const std::string&, int, int);

	bool IsCorrectInput(const std::string&);
public:
	Pattern(std::string&);
	Pattern(int);
	
	int Height()const;
	int Width()const;
	int ID()const;
	boolXbool GetPattern() const;
	std::string Name() const;
	void Rotate();
};