#include <iostream>
#include <fstream>
#include <string>
#include <list>


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
};

class Passenger : public Wagon
{
private:
	std::string type;
	uint count_of_seats;
	bool shower;
public:
	Passenger() {}
	/*Passenger(uint id_number, uint year_of_release, std::string type, uint count_of_seats, bool shower) :
		Wagon(id_number, year_of_release), type(type), count_of_seats(count_of_seats), shower(shower) {}*/
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
	Cargo(std::ifstream& file);
	void print() const override;
};

class Depo
{
private:
	std::list<std::shared_ptr<Wagon>> list;
	struct Comparator {
		bool operator()(const std::shared_ptr<Wagon>& a,
			const std::shared_ptr<Wagon>& b) const {
			// ѕриводим указатели к типу Passenger
			auto a_passenger = dynamic_cast<Passenger*>(a.get());
			auto b_passenger = dynamic_cast<Passenger*>(b.get());

			// ѕровер€ем, €вл€етс€ ли 'a' пассажирским вагоном с душем
			bool a_has_shower = a_passenger && a_passenger->get_shower();
			bool b_has_shower = b_passenger && b_passenger->get_shower();

			// ¬агоны с душем должны идти первыми
			if (a_has_shower != b_has_shower) {
				return a_has_shower;
			}

			// ≈сли оба вагона с душем или без душа, сортируем по типу:
			// —начала пассажирские, затем грузовые
			bool a_is_passenger = (a_passenger != nullptr);
			bool b_is_passenger = (b_passenger != nullptr);

			if (a_is_passenger != b_is_passenger) {
				return a_is_passenger;
			}

			// ≈сли типы одинаковые, сохран€ем исходный пор€док
			return false;
		}
	};
public:
	Depo() {}
	Depo(std::ifstream& file);
	void print(const char* delim = "================");
	void sort() { list.sort(Comparator()); }
	std::list<std::shared_ptr<Wagon>> get_list() const { return list; }
};

int count_sv_with_shower(const Depo& depo)
{
	int count{};
	// some code
}

int main()
{
	std::ifstream inp_file("Wagons.txt");
	Depo wag_list(inp_file);
	wag_list.print();
	wag_list.sort();
	std::cout << "\n\nSORTED:\n";
	wag_list.print();
}

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

Depo::Depo(std::ifstream& file) 
{
	std::string child_type{};
	while (file >> child_type) 
	{
		if (child_type == "Passenger")
			list.push_back(std::make_shared<Passenger>(file));
		else
			list.push_back(std::make_shared<Cargo>(file));
	}
}

void Depo::print(const char* delim)
{
	for (auto i : list)
	{
		i.get()->print();
		std::cout << delim << '\n';
	}
}
