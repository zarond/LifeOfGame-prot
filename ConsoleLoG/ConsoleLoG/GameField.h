#pragma once
#include <vector>
#include <functional>

typedef std::pair<int, int> cord_t;
typedef std::vector<std::pair<int, int>> vector_cord_t;
typedef std::pair<std::pair<int, int>, std::pair<int, int>> start_finish_t;

struct FVector {
	float X;
	float Y;
	float Z;
};

enum class obj_t
{
	start_finish,
	enemy,
	npc,
	chest,
	count_types
};

class Factory
{
public:
	Factory(obj_t _type) : type{_type} {}

	const obj_t type;
	void MakeObject(int i, int j) const { return; }
private:

};

class GameField
{
public:
	GameField(bool**, int, int, start_finish_t);
	FVector* GetArrayOfBlocks(int&) const;
	int Height() const;
	int Width() const;
	
	void AddObjects(int, Factory const*, std::function<bool(int)> const&);
	FVector const* GetObjects(obj_t type) const;

private:
	bool** field;
	int height;
	int width;
	int** supportField;
	FVector** objects;

};

