#pragma once
#include "Book.h"

Book::Book(std::ifstream& file)
{
	file.getline(author, LEN);
	file.getline(title, LEN);
	file >> year;
	file.ignore();
	file >> pages;
	file.ignore();
	file.getline(spec, LEN);
	if (!file.eof())
	{
		char delim_line[255];
		file.getline(delim_line, 255);
	}
}

void Book::print() const
{
	std::cout << author << '\n' <<
		title << '\n' <<
		year << '\n' <<
		pages << '\n' <<
		spec << '\n' <<
		"====================\n";
}