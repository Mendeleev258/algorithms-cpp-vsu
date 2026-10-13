#pragma once
#include <iostream>
#include <fstream>

constexpr short LEN = 100;
using ushort = unsigned short;
using uint = unsigned int;

class Book
{
private:
	static inline uint count = 0;
	char author[LEN];
	char title[LEN];
	ushort year;
	ushort pages;
	char spec[LEN];
public:
	Book() {}
	Book(std::ifstream& file);
	void print() const;
	void up_count() { count++; }
	uint get_count() const { return count; }
	char* get_spec() { return spec; }
};