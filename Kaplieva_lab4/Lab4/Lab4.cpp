#include <iostream>
#include <fstream>
#include <functional>
#include <ctime>


template<typename T, typename Predicat>
void validation(T& x, T& y, Predicat condition, const char* message);
template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int checkfile(std::ifstream& file);

int main_menu();
int task_menu();
void ending(int n);
void print_answer(int result, int sum_res);

int task1(int n, std::istream& stream, int& cnt);
int task1(int n, int a, int b, int& cnt);
int task2(int n, std::istream& stream, int& sum_res);
int task2(int n, int a, int b, int& sum_res);

// 21

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int choice1;
	do
	{
		choice1 = main_menu();
		switch (choice1)
		{
		case 1:
		{
			int choice2 = task_menu();
			int n; // количество элементов
			switch (choice2)
			{
			case 1:
			{
				validation(n, [](int x) {return x > 0; }, "Введите количество элементов последовательности");
				std::cout << "Введите последовательность:\n";
				int cnt{};
				int res = task1(n, std::cin, cnt);
				print_answer(res, cnt);
			}
			break;
			case 2:
			{
				std::ifstream file("data.txt");
				if (checkfile(file) == 1)
				{
					int cnt{};
					int res = task1(10, file, cnt);
					print_answer(res, cnt);
				}
				else
				{
					if (checkfile(file) == 0)
						std::cout << "Файл пуст!\n";
					else
						std::cout << "Ошибка открытия файла!\n";
				}
				file.close();
			}
			break;
			default:
			{
				int a, b;
				int cnt{};
				validation(a, b, [](int x, int y) {return y >= x; }, "Введите диапазон [a, b]");
				validation(n, [](int x) {return x > 0; }, "Введите количество элементов последовательности");
				int res = task1(n, a, b, cnt);
				print_answer(res, cnt);
			}
			break;
			}

		}
		break;
		case 2:
		{
			int choice2 = task_menu();
			int n; // количество элементов
			switch (choice2)
			{
			case 1:
			{
				validation(n, [](int x) {return x > 0; }, "Введите количество элементов последовательности");
				std::cout << "Введите последовательность:\n";
				int sum_res = 0;
				int res = task2(n, std::cin, sum_res);
				print_answer(res, sum_res);
			}
			break;
			case 2:
			{
				std::ifstream file("data.txt");
				if (checkfile(file) == 1)
				{
					int sum_res = 0;
					int res = task2(10, file, sum_res);
					print_answer(res, sum_res);
				}
				else
				{
					if (checkfile(file) == 0)
						std::cout << "Файл пуст!\n";
					else
						std::cout << "Ошибка открытия файла!\n";
				}
				file.close();
			}
			break;
			default:
			{
				int a, b;
				validation(a, b, [](int x, int y) {return y >= x; }, "Введите диапазон [a, b]");
				validation(n, [](int x) {return x > 0; }, "Введите количество элементов последовательности");
				int sum_res = 0;
				int res = task2(n, a, b, sum_res);
				print_answer(res, sum_res);
				
			}
			break;
			}
		}
		break;
		default:
		{
			choice1 = 3;
		}
		break;
		}

	} while (choice1 != 3);
}



void ending(int n)
{
	if (n % 10 > 4 and n % 10 <= 9 or n % 10 == 0 or (n % 100 > 10 and n % 100 < 20)) std::cout << n << " элементов\n";
	else if (n % 10 != 1) std::cout << n << " элемента\n";
	else std::cout << n << " элемент\n";
}

void print_answer(int result, int sum_res)
{
	switch (result)
	{
	case -1:
	{
		std::cout << "Отсутствует первый элемент входа\n";
	}
	break;
	case 0:
	{
		std::cout << "Диапазон пустой\n";
	}
	break;
	case 1:
	{
		std::cout << "Отсутствует последний элемент входа\n";
	}
	break;
	default:
	{
		std::cout << "Ответ: " << sum_res << '\n';
	}
	}
}

int task1(int n, std::istream& stream, int& cnt)
{
	int x{}, res{}, lastMin{};
	cnt = 0;
	stream >> lastMin;
	for (int i = 1; i < n; ++i)
	{
		stream >> x;
		if (x <= lastMin)
		{
			lastMin = x;
			cnt = 0;
		}
		else
			if (x % 2 == 0)
				cnt++;
	}
	if (!cnt)
		res = 0;
	else res = 2;
	return res;
		
	// return 0 диапазон пустой
	// return 2 есть ответ
}

int task1(int n, int a, int b, int& cnt)
{
	std::cout << "Сгенерирована последовательность, содержащая ";
	ending(n);

	int x{}, res{}, lastMin{};
	cnt = 0;
	lastMin = rand() % (b - a) + a;
	std::cout << lastMin << ' ';
	for (int i = 1; i < n; ++i)
	{
		x = rand() % (b - a) + a;
		std::cout << x << ' ';
		if (x <= lastMin)
		{
			lastMin = x;
			cnt = 0;
		}
		else
			if (x % 2 == 0)
				cnt++;
	}
	std::cout << '\n';
	if (!cnt)
		res = 0;
	else res = 2;
	return res;
}

int task2(int n, std::istream& stream, int& sum_res)
{
	int x{}, sum{}, result = 2;
	int firsti{}, lasti{};
	sum_res = 0;
	for (int i = 0; i < n; ++i)
	{
		stream >> x;
		if (!firsti)
		{
			if (x % 7 == 0)
				firsti = i;
		}
		else
		{
			if (x % 7 == 0)
			{
				sum_res = sum;
				lasti = i;
			}
			if (x > 0)
				sum += x;
		}
	}
	if (!firsti)
		result = -1;
	else
	{
		if (!lasti)
			result = 1;
		else
		{
			if (firsti + 1 == lasti)
				result = 0;
		}
	}
	return result;
	// 0 пустой 
	// 1 ласт = 0
	// иначе 2
}

int task2(int n, int a, int b, int& sum_res)
{
	std::cout << "Сгенерирована последовательность, содержащая ";
	ending(n);
	
	int x{}, sum{}, result = 2;
	int firsti{}, lasti{};
	sum_res = 0;
	for (int i = 0; i < n; ++i)
	{
		x = rand() % (b - a) + a;
		std::cout << x << ' ';
		if (!firsti)
		{
			if (x % 7 == 0)
				firsti = i;
		}
		else
		{
			if (x % 7 == 0)
			{
				sum_res = sum;
				lasti = i;
			}
			if (x > 0)
				sum += x;
		}
	}
	if (!firsti)
		result = -1;
	else
	{
		if (!lasti)
			result = 1;
		else
		{
			if (firsti + 1 == lasti)
				result = 0;
		}
	}
	std::cout << '\n';
	return result;
}

template<typename T, typename Predicat>
void validation(T& x, T& y, Predicat condition, const char* message)
{
	std::cout << message << '\n';
	std::cout << ">>> ";
	std::cin >> x;
	std::cout << ">>> ";
	std::cin >> y;
	while (!(condition(x, y)))
	{
		std::cout << "Ошибка ввода!\n";
		std::cout << message << '\n';
		std::cout << ">>> ";
		std::cin >> x;
		std::cout << ">>> ";
		std::cin >> y;
		std::cout << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
}

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
	std::cout << message << "\n>>> ";
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода\n";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
}

int checkfile(std::ifstream& file)
{
	int res = 1;
	if (!file)
	{
		res = -1;
	}
	else
		if (file.peek() == EOF)
			res = 0;
	return res;
}

int main_menu()
{
	std::cout << "-----------------------------------------------------\n";
	std::cout << "1. Найти количество четных элементов, расположенных после последнего минимального\n";
	std::cout << "2. Найти сумму положительных чисел, расположенных между первым и последним числами кратными 7\n";
	std::cout << "3. Выход из программы\n";
	std::cout << "-----------------------------------------------------\n";

	std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 3; };
	int choice;
	validation(choice, foo, "");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int task_menu()
{
	std::cout << "-------------------------\n";
	std::cout << "1. Ввод с клавиатуры\n";
	std::cout << "2. Ввод из файла\n";
	std::cout << "3. Случайным образом\n";
	std::cout << "------------------------\n";

	std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 3; };
	int choice;
	validation(choice, foo, "Выберите способ ввода");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}
