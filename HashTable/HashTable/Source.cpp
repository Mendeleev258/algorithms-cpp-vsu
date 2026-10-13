#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <Windows.h>
#include <functional>
#include "Wagon.h"
#include "HashTable0.h"


void fill_table(std::ifstream& file, HashTable0& hash_table) // cargo wagons only
{
	while (!file.eof())
	{
		Cargo newWagon(file);
		Pair pair(newWagon.get_id(), newWagon.get_type());
		hash_table.add(pair);
	}
}

int main()
{
    HashTable0 hash_table(5);
    std::ifstream file("Wagons.txt");
    fill_table(file, hash_table);
    std::cout << "Original table:\n";
    hash_table.print();
    std::cout << "-------------------------\n";

    // Тест метода add()
    std::cout << "Testing add() method:\n";
    hash_table.add({ 135, "Tank" });
    hash_table.print();
    std::cout << "-------------------------\n";

    // Тест метода find()
    std::cout << "Testing find() method:\n";
    Pair found_pair;
    if (hash_table.find(162, found_pair))
        std::cout << "Found: " << to_string(found_pair) << '\n';
    else
        std::cout << "Key 162 not found.\n";

    if (hash_table.find(999, found_pair))
        std::cout << "Found: " << to_string(found_pair) << '\n';
    else
        std::cout << "Key 999 not found.\n";
    std::cout << "-------------------------\n";

    // Тест метода remove()
    std::cout << "Testing remove() method:\n";
    if (hash_table.remove(162))
        std::cout << "Key 162 removed successfully.\n";
    else
        std::cout << "Key 162 not found for removal.\n";

    if (hash_table.remove(999))
        std::cout << "Key 999 removed successfully.\n";
    else
        std::cout << "Key 999 not found for removal.\n";

    hash_table.print();
    std::cout << "-------------------------\n";

    return 0;
}

