#pragma once
#include "Worker.h"

using ptrWorker = Worker*;

struct Array
{
	ptrWorker* arr;
	size_t size;
	Array() {}
	Array(std::ifstream& file);
	void print();
	void soritng();
	bool to_binary(const char* file_name);
	~Array()
	{
		for (size_t i{}; i < size; ++i)
			delete arr[i];
		delete arr;
	}
};