#pragma once
#include <iostream>
#include <fstream>
#include <string>

const int m = 35;	// max length of str

struct Worker
{
private:
	char name[m];
	char post[m];
	int days;
public:
	Worker() {}
	Worker(std::ifstream& file);
	void print();
	int compare(const Worker& worker);
	char* get_name()
	{
		return name;
	}
	int get_days()
	{
		return days;
	}
	char* get_post()
	{
		return post;
	}
};
