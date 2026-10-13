#pragma once
#include <iostream>
#include <fstream>
#include <string>

using uint = unsigned int;
class Wagon
{
protected:
	uint id_number;
	uint year_of_release;
public:
	Wagon() {}
	Wagon(uint id_number, uint year_of_release) : id_number(id_number), year_of_release(year_of_release) {}
	Wagon(std::ifstream& file);
	virtual void print() const { std::cout << "ID: " << id_number << "\nYear: " << year_of_release << '\n'; }
	uint get_id() const { return id_number; }
};

class Passenger : public Wagon
{
private:
	std::string type;
	uint count_of_seats;
	bool shower;
public:
	Passenger() {}
	Passenger(uint id_number, uint year_of_release, std::string type, uint count_of_seats, bool shower) :
		Wagon(id_number, year_of_release), type(type), count_of_seats(count_of_seats), shower(shower) {}
	Passenger(std::ifstream& file);
	void print() const override;
	bool get_shower() const { return shower; }
	std::string get_type() const { return type; }
};

class Cargo : public Wagon
{
private:
	std::string type;
	uint tonnage;
public:
	Cargo() {}
	Cargo(uint id_number, uint year_of_release, std::string type, uint tonnage) : 
		Wagon(id_number, year_of_release), type(type), tonnage(tonnage) {}
	Cargo(std::ifstream& file);
	void print() const override;
	std::string get_type() const { return type; }
};

Wagon::Wagon(std::ifstream& file)
{
	file >> id_number >> year_of_release;
}

Passenger::Passenger(std::ifstream& file) : Wagon(file)
{
	std::string delim_line{};
	file >> type >> count_of_seats >> shower >> delim_line;
}

void Passenger::print() const
{
	std::cout << "ID: " << id_number << "\nYear: " << year_of_release <<
		"\nType: " << type << "\nCount of seats: " << count_of_seats << "\nHas a shower: " << std::boolalpha << shower << '\n';
}

Cargo::Cargo(std::ifstream& file) : Wagon(file)
{
	std::string delim_line{};
	file >> type >> tonnage >> delim_line;
}

void Cargo::print() const
{
	std::cout << "ID: " << id_number << "\nYear: " << year_of_release <<
		"\nType: " << type << "\nTonnage: " << tonnage << '\n';
}