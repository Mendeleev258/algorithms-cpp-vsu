#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <Windows.h>
#include <functional>
#include "Wagon.h"


using Pair = std::pair <uint, std::string>;
std::string to_string(const Pair& pair)  
{  
   return std::to_string(pair.first) + " " + pair.second;  
}

using List = std::list<Pair>;
using Vector = std::vector<List>;


class HashTable0
{
	Vector table;
	size_t max_size;
	const static size_t LIST_MAX_SIZE = 3;

	size_t hash(uint key)
	{
		return key % max_size;
	}

	void rehash();

public:
	HashTable0(size_t max_size) : max_size(max_size)
	{
		table.resize(max_size);
	}

	void fill(std::ifstream& file)
	{
		Pair elem;
		while (file >> elem.first >> elem.second)
		{
			add(elem);
		}
	}
	
	bool find(uint key, Pair& pair);
	
	bool add(const Pair& pair);
	
	bool remove(uint key);
	
	void print();
};

bool HashTable0::find(uint key, Pair& pair)
{
	bool result{ false };
	size_t index = hash(key);
	List::iterator it = std::find_if(table[index].begin(),
		table[index].end(),
		[key](Pair temp) { return temp.first == key; });
	if (it != table[index].end())
	{
		result = true;
		pair = *it;
	}
	return result;
}

bool HashTable0::add(const Pair& pair)
{
	bool result{ false };
	size_t index = hash(pair.first);
	List::iterator it = std::find_if(table[index].begin(), table[index].end(), [pair](Pair temp) { return temp.first == pair.first; });
	if (it == table[index].end())
	{
		result = true;
		table[index].push_back(pair);
		if (table[index].size() >= LIST_MAX_SIZE)
			rehash();
	}
	return result;
}

bool HashTable0::remove(uint key)
{
	bool result{ false };
	size_t index = hash(key);
	List::iterator it = std::find_if(table[index].begin(),
		table[index].end(),
		[key](Pair temp) { return temp.first == key; });
	if (it != table[index].end())
	{
		table[index].erase(it);
		result = true;
	}
	return result;
}

void HashTable0::print()
{
	size_t index{};
	for (auto lst : table)
	{
		if (!lst.empty())
			for (auto pair : lst)
				std::cout << index << ": " << to_string(pair) << '\n';
		++index;
	}
}

void HashTable0::rehash()
{
	Vector new_table;
	new_table.resize(max_size * 2);
	for (auto lst : table)
	{
		for (auto pair : lst)
		{
			size_t index = hash(pair.first);
			new_table[index].push_back(pair);
		}
	}
	table = new_table;
	max_size *= 2;
}
