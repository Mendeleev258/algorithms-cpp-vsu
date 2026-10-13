#include "Worker.h"

Worker::Worker(std::ifstream& file)
{
	file.getline(name, m);
	file.getline(post, m);
	file >> salary;
	file.ignore();
	if (!file.eof())
	{
		char delim_line[255];
		file.getline(delim_line, 255);
	}
}

void Worker::print()
{
	std::cout << name << '\n' << post << '\n' << salary << '\n' << "====================\n";
}

int Worker::compare(const Worker& worker)
{
	return strcmp(post, worker.post);
}
