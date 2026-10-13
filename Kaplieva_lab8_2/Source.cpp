#include <functional>
#include "DLIST.h"


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int check_file(std::ifstream& file);
int task_menu();

int compare(File f1, File f2);
void task(DLIST& list);

constexpr int str_maxlen = 35;


int main()
{
	setlocale(LC_ALL, "Russian");
	bool correctfile{ false };
	do
	{
		char filename[str_maxlen];
		std::cout << "Введите имя файла\n>>> ";
		std::cin.getline(filename, str_maxlen);
		std::ifstream inp_file(filename);
		switch (check_file(inp_file))
		{
		case -1:
			std::cout << "Файл не найден\n";
			break;
		case 0:
			std::cout << "Файл пуст\n";
			break;
		default:
			correctfile = true;
			std::cout << "Корректный файл\n";
			DLIST list(filename, compare);
			int choice{};
			do
			{
				choice = task_menu();
				switch (choice)
				{
				case 1:
					list.print();
					break;
				case 2:
				{
					std::ofstream out_file("output.txt");
					list.print(out_file);
					break;
				}
				case 3:
					task(list);
					std::cout << "Задача выполнена\n";
				default:
					break;
				}
			} while (choice != 4);
		}
	} while (!correctfile);
}


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
	std::cout << message << "\n>>> ";
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
}

int check_file(std::ifstream& file)
{
	int res = 1;
	if (!file)
	{
		res = -1; // Файл не найден!
	}
	else
		if (file.peek() == EOF)
			res = 0; // Файл пустой!
	return res;
}

int task_menu()
{
	std::cout << "\n-----------------------------------------------------\n";
	std::cout << "1. Вывести список на экран\n";
	std::cout << "2. Вывести список в файл\n";
	std::cout << "3. Выполнить задачу\n";
	std::cout << "4. Выход из программы\n";
	std::cout << "-----------------------------------------------------\n";

	std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 4; };
	int choice;
	validation(choice, foo, "");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int compare(File f1, File f2)
{
	int result{ -1 };
	if (f1.get_spec()[0] == '~' && f2.get_spec()[0] == '~')
		result = 0;
	else
		if (f1.get_spec()[0] != '~' && f2.get_spec()[0] == '~')
			result = 1;
	return result;
}

void task(DLIST& list)
{
	ptrDNODE ptr = list.get_head();
	while (ptr && ptr->info->get_spec()[0] == '~')
		list.remove(ptr);
}
