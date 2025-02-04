#include "Pattern.h"
#include <fstream>
#include <regex>
#include <stdlib.h>
#include <sstream>

//using namespace Custom;

std::vector<std::string> split(const std::string& s) {
	typedef std::string::const_iterator iter;
	std::vector<std::string> ret;
	int i = 0;
	while (i < s.length()) {
		int j = i;
		while (j < s.length() && s[j] != ' ')
			++j;
		ret.push_back(s.substr(i, j - i));
		i = j + 1;
	}
	return ret;
}

bool Custom::Pattern::IsCorrectInput(const std::string& str)
{
	std::cmatch result;
	std::regex reg(
		"[1-9]([0-9])*[[:space:]]"
		"([[:alnum:]-])*[[:space:]]"
		"[1-9]([0-9])*[[:space:]]"
		"[1-9]([0-9])*[[:space:]]"
		"(([1-9][0-9]*)|[ob])"
		"([1-9]([0-9])*|[ob\\$])*"
		"\\$"
	);
	return regex_match(str.c_str(), result, reg);
}

/// make 2D array for pattern
boolXbool Custom::Pattern::PreparePatrernArr(const std::string& figure, size_t x, size_t y)
{
	// init vectors
	auto pattern = boolXbool(x);
	size_t str_iter = 0; // string iterator
	for (size_t i = 0; i < x; i++)
	{
		pattern[i] = std::vector<bool>(y, false);
	}

	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			if (figure[str_iter] == '$') // false for all to end line
			{
				break;
			}
			else if (figure[str_iter] == 'o') // insert a cell
			{
				pattern[i][j] = true;
				++str_iter;
			}
			else if (figure[str_iter] == 'b') 
			{
				++str_iter;
			}
			else // find a number
			{
				size_t t = 1;
				while (figure[str_iter + t] != 'b' && figure[str_iter + t] != 'o' && figure[str_iter + t] != '$')
					++t;
				size_t count = std::atoi(figure.substr(str_iter, t).c_str());
				str_iter += t + 1;
				if (figure[str_iter - 1] == '$') // scip count lines
				{
					i += count;
					break;
				}
				else if (figure[str_iter - 1] == 'o') // insert true to count columns
				{
					for (;count > 0; --count)
					{
						pattern[i][j] = true;
						++j;
					}
					--j;
				}
				else // scip count columns
				{
					j += count - 1;
				}
				
			}
		}
		if (figure[str_iter] == '$')
			++str_iter;
	}

	return pattern;
}

Custom::Pattern::Pattern(std::string& _name)
{
	auto file = std::ifstream("Patterns.txt");
	std::string newPattern = "";
	std::vector<std::string> vectorOfWord;
	while (!file.eof())
	{
		//file >> newPattern;
		std::getline(file, newPattern);
		// checking input line
		if (!IsCorrectInput(newPattern))
			continue;

		vectorOfWord = split(newPattern);
		if (vectorOfWord.size() != 5)
			continue;

		if (vectorOfWord[1] == _name)
		{
			id = std::atoi(vectorOfWord[0].c_str());
			name = _name;
			height = std::atoi(vectorOfWord[3].c_str());
			width = std::atoi(vectorOfWord[2].c_str());
			pattern = PreparePatrernArr(vectorOfWord[4], height, width);
			break;
		}
	}
	file.close();
}

Custom::Pattern::Pattern(int _id)
{
	// make string id
	std::string str_id;
	std::stringstream out;
	out << _id;
	str_id = out.str();

	auto file = std::ifstream("Patterns.txt");
	std::string newPattern = "";
	std::vector<std::string> vectorOfWord;
	while (!file.eof())
	{
		//file >> newPattern;
		std::getline(file, newPattern);
		// checking input line
		if (!IsCorrectInput(newPattern))
			continue;

		vectorOfWord = split(newPattern);
		if (vectorOfWord.size() != 5)
			continue;

		if (vectorOfWord[0] == str_id)
		{
			id = _id;
			name = vectorOfWord[1];;
			height = std::atoi(vectorOfWord[3].c_str());
			width = std::atoi(vectorOfWord[2].c_str());
			pattern =  PreparePatrernArr(vectorOfWord[4], height, width);
			break;
		}
	}
	file.close();
}

size_t Custom::Pattern::Height() const
{
	return height;
}

size_t Custom::Pattern::Width() const
{
	return width;
}

size_t Custom::Pattern::ID() const
{
	return id;
}

boolXbool Custom::Pattern::GetPattern() const
{
	return pattern;
}

std::string Custom::Pattern::Name() const
{
	return name;
}

void Custom::Pattern::Rotate()
{
	auto newPattern = boolXbool(width);
	size_t str_iter = 0; // string iterator
	for (size_t i = 0; i < width; i++)
	{
		newPattern[i] = std::vector<bool>(height, false);
		for (size_t j = 0; j < height; j++)
		{
			newPattern[i][j] = pattern[j][i];
		}
	}
	std::swap(newPattern, pattern);
	std::swap(height, width);
}
