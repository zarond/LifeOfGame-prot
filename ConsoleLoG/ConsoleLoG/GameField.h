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
	block,
	count_types
};


class GameField
{
public:
	GameField(bool**, int, int, start_finish_t);
	~GameField();

	const bool* const* GetField() const;
	int Height() const;
	int Width() const;
	
	void AddObjects(int, const obj_t, std::function<bool(int)> const&);
	FVector const* GetObjects(obj_t type, int&) const;

private:
	bool** field;
	int height;
	int width;
	int** supportField;
	FVector** objects;
	int* countObjects;
};

