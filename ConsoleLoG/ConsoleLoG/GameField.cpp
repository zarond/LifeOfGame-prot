#include "GameField.h"
#include <ctime>

namespace {
	constexpr int matrix[5][5] = {
		{1, 2, 4, 2, 1},
		{2, 6, 8, 6, 2},
		{4, 8, 0, 8, 4},
		{2, 6, 8, 6, 2},
		{1, 2, 4, 2, 1},
	};
}

GameField::GameField(bool** _field, int h, int w, start_finish_t sf) :
	field{ _field },
	height{ h },
	width{ w },
	supportField{ new int*[h] },
	objects{ new FVector * [(int)obj_t::count_types]{nullptr} },
	countObjects{ new int [(int)obj_t::count_types] }
{
	for (int i = 0; i < (int)obj_t::count_types; ++i)
		objects[i] = nullptr;
	objects[(int)obj_t::start_finish] = new FVector[2];
	objects[(int)obj_t::start_finish][0] = { (float)sf.first.first, (float)sf.first.second, 0. };
	objects[(int)obj_t::start_finish][1] = { (float)sf.second.first, (float)sf.second.second, 0. };
	countObjects[(int)obj_t::start_finish] = 2;
	for (int i = 0; i < height; i++)
		supportField[i] = new int[width];
	
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			supportField[i][j] = -1;

	for (int i = 1; i < height - 1; ++i)
		for (int j = 1; j < width - 1; ++j)
		{
			if (field[i][j])
				continue;
			int count = 0;

			for (int k = 0; k < 5; ++k)
				for (int l = 0; l < 5; ++l)
				{
					int x = i - 2 + k;
					int y = j - 2 + l;

					if (x < 0) x += h;
					if (x >= h) x -= h;
					if (i < 0) i += w;
					if (i >= w) i -= w;
					count += matrix[k][l] * field[x][y];
				}
			supportField[i][j] = count;
		}
	
	// mark start/finish
	for (int k = 0; k < 2; k++)
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				supportField[(int)objects[(int)obj_t::start_finish][k].X + i][(int)objects[(int)obj_t::start_finish][k].Y + j];
			}
}

GameField::~GameField()
{
	for (int i = 0; i < height; ++i)
	{
		delete[] field[i];
		delete[] supportField[i];
	}
	delete[] field;
	delete[] supportField;
	for (int i = 0; i < (int)obj_t::count_types; ++i)
	{
		delete[] objects[i];
	}
	delete objects;
	delete countObjects;
}

const bool* const* GameField::GetField() const
{
	return field;
}

int GameField::Height() const
{
	return height;
}

int GameField::Width() const
{
	return width;
}

void GameField::AddObjects
	(int count, const obj_t type, std::function<bool(int)> const& f)
{
	if (nullptr != objects[(int)type])
		return;

	auto vec = vector_cord_t();
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			if (f(supportField[i][j])) vec.push_back(cord_t(0, 0));

	if (count > vec.size())
		count = vec.size();

	objects[(int)type] = new FVector[count];
	std::srand((unsigned int)std::time(0));

	for (int i = 0; i < count; ++i)
	{
		int ind = rand() % vec.size();

		int x = vec[ind].first;
		int y = vec[ind].second;
		vec.erase(vec.begin() + ind);
		if (-1 == supportField[x][y])
		{
			count = std::_Min_value(count, (int)vec.size() + i);
			continue;
		}
		
		// marking cells
		for (int j = -1; j < 2; ++j)
			for (int k = -1; k < 2; ++k)
				supportField[x + j][y + k] = -1;

		objects[(int)type][i] = { (float)x, (float)y, 0. };
	}
	countObjects[(int)type] = count;
	return;
}

FVector const* GameField::GetObjects(obj_t type, int& size) const
{
	size = countObjects[(int)type];
	return objects[(int)type];
}