#pragma once
#include <iostream>
#include <fstream>

constexpr int LEN = 35;
using uint = unsigned int;

struct File
{
private:
	char catalogue_name[LEN];
	char file_name[LEN];
	char spec[LEN];
	uint date[3];
	uint size;
public:
	File() {}
	File(std::ifstream& file);
	void print(std::ostream& stream = std::cout);
	char* get_spec()
	{
		return spec;
	}
};