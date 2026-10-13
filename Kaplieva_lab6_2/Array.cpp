#include "Array.h"

Array::Array(std::ifstream& file)
{
	file >> size;
	file.ignore();
	arr = new ptrWorker[size];
	for (size_t i{}; i < size; ++i)
		arr[i] = new Worker(file);
	file.close();
}

void Array::print()
{
	for (size_t i{}; i < size; ++i)
		arr[i]->print();
}

void Array::soritng()
{
	for (int i{}; i < size; ++i)
		for (int j{}; j < size - i - 1; ++j)
		{
			if (arr[j]->compare(*arr[j + 1]) > 0)
				std::swap(arr[j], arr[j + 1]);
		}
}

bool Array::to_binary(const char* file_name)
{
	bool result{ true };
	std::ofstream file_bin(file_name, std::ios::binary);
	if (!file_bin.is_open())
		result = false;
	else
	{
		for (size_t i{}; i < size; ++i)
			file_bin.write((char*)&(*arr[i]), sizeof(Worker));
		file_bin.close();
	}
	return result;
}
