#include "File.h"

File::File(std::ifstream& file)
{
	file.getline(catalogue_name, LEN, '/');
	file.getline(file_name, LEN, '.');
	file.getline(spec, LEN);
	for (int i{}; i < 3; ++i)
	{
		file >> date[i];
		file.ignore();
	}
	file >> size;
	file.ignore();
	if (!file.eof())
	{
		char delim_line[255];
		file.getline(delim_line, 255);
	}
}

void File::print(std::ostream& stream)
{
	stream << catalogue_name << '/' << file_name << '.' << spec << '\n';
	for (int i{}; i < 3; ++i)
	{
		stream << date[i];
		if (i < 2)
			stream << '/';
	}
	stream << '\n' << size << " bytes\n\n";
}