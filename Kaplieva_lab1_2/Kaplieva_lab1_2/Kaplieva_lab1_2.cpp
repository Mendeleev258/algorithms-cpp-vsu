// КИМ 12
// Дана целочисленная квадратная матрица.
// 1) Проверить, есть ли в матрице хотя бы два симметричных столбца, если есть, вывести их номера.
// 2) Переместить вниз строки, содержащие числа, оканчивающиеся на заданную цифру, 
// остальные строчки заполнить нулями. Среди оставшихся строк, сохранить исходный взаимный порядок.

#include <iostream>
#include <iomanip>
#include <fstream>

const int size = 4;

// static matrix
void fillarr(int* arr, int a, int b);
void fillarr(int* arr, std::istream& stream);
void fillmatrix(int matr[][size], int a, int b);
void fillmatrix(int matr[][size], std::istream& stream);
void printarr(int* arr);
void printmatrix(int matr[][size]);

// dynamic matrix
int** memory_allocation(int size_d);
void free_memory(int**& matr, int size_d);
void fillarr(int* arr, int a, int b, int size_d);
void fillarr(int* arr, std::istream& stream, int size_d);
void fillmatrix(int** matr, int a, int b, int size_d);
void fillmatrix(int** matr, std::istream& stream, int size_d);
void printarr(int* arr, int size_d);
void printmatrix(int** matr, int size_d);

// task 1
void transposition(int matr[][size]);
bool is_simmetric(int* arr);
int task1(int matr[][size]);

// task 2
bool last_digit(int x, int digit);
void fill_null(int* arr, int size_d);
bool condition(int* arr, int size_d, int digit);
void task2(int** matr, int size_d, int n);

// user interface
void main_menu(int& choice);
void source_menu(int& source);
int exit();


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int choice, source;
	do
	{
		main_menu(choice);
		if (choice == 1)
		{
			int matrix[size][size];
			std::ifstream file("file.txt");
			std::cout << "Статическая матрица, размерность = " << size;
			source_menu(source);
			switch (source)
			{
			case 1:
				fillmatrix(matrix, std::cin);
				break;

			case 2:
				fillmatrix(matrix, file);
				break;
			default:
				int a, b;
				std::cout << "\nВведите левый и правый край диапазона:\n>>> ";
				std::cin >> a >> b;
				std::cout << '\n';
				fillmatrix(matrix, a, b);
				break;
			}
			printmatrix(matrix);
			if (!task1(matrix))
				std::cout << "Недостаточно столбцов\n";
		}
		else
			if (choice == 2)
			{
				int size_d;
				int n;
				std::cout << "Введите размер матрицы\n>>> ";
				std::cin >> size_d;
				int** matrix = memory_allocation(size_d);
				std::ifstream file("file.txt");
				source_menu(source);
				switch (source)
				{
				case 1:
					fillmatrix(matrix, std::cin, size_d);
					break;

				case 2:
					fillmatrix(matrix, file, size_d);
					break;
				default:
					int a, b;
					std::cout << "\nВведите левый и правый край диапазона:\n>>> ";
					std::cin >> a >> b;
					std::cout << '\n';
					fillmatrix(matrix, a, b, size_d);
					break;
				}
				std::cout << "Введите n\n>>> ";
				std::cin >> n;
				printmatrix(matrix, size_d);
				task2(matrix, size_d, n);
				std::cout << "=====================\n";
				printmatrix(matrix, size_d);
			}
		choice = exit();
	} while (choice != 3);
}



// static matrix
void fillarr(int* arr, int a, int b)
{
	for (int i{}; i < size; ++i)
		arr[i] = a + rand() % (b - a);
}

void fillarr(int* arr, std::istream& stream)
{
	for (int i{}; i < size; ++i)
		stream >> arr[i];
}

void fillmatrix(int matr[][size], int a, int b)
{
	for (int i{}; i < size; ++i)
		fillarr(matr[i], a, b);
}

void fillmatrix(int matr[][size], std::istream& stream)
{
	for (int i{}; i < size; ++i)
		fillarr(matr[i], stream);
}

void printarr(int* arr)
{
	for (int i{}; i < size; ++i)
		std::cout << std::setw(4) << arr[i];
	std::cout << '\n';
}

void printmatrix(int matr[][size])
{
	for (int i{}; i < size; ++i)
		printarr(matr[i]);
}



// dynamic matrix
int** memory_allocation(int size_d)
{
	int** matr = new int* [size_d];
	for (int i{}; i < size_d; ++i)
		matr[i] = new int[size_d];
	return matr;
}

void free_memory(int**& matr, int size_d)
{
	for (int i{}; i < size_d; ++i)
		delete[]matr[i];
	delete[]matr;
}

void fillarr(int* arr, int a, int b, int size_d)
{
	for (int i{}; i < size_d; ++i)
		arr[i] = a + rand() % (b - a);
}

void fillarr(int* arr, std::istream& stream, int size_d)
{
	for (int i{}; i < size_d; ++i)
		stream >> arr[i];
}

void printarr(int* arr, int size_d)
{
	for (int i{}; i < size_d; ++i)
		std::cout << std::setw(4) << arr[i];
	std::cout << '\n';
}

void fillmatrix(int** matr, int a, int b, int size_d)
{
	for (int i{}; i < size_d; ++i)
		fillarr(matr[i], a, b, size_d);
}

void fillmatrix(int** matr, std::istream& stream, int size_d)
{
	for (int i{}; i < size_d; ++i)
		fillarr(matr[i], stream, size_d);
}

void printmatrix(int** matr, int size_d)
{
	for (int i{}; i < size_d; ++i)
		printarr(matr[i], size_d);
}



// task 1
void transposition(int matr[][size])
{
	for (int i{}; i < size - 1; ++i)
		for (int j = i + 1; j < size; ++j)
			std::swap(matr[i][j], matr[j][i]);
}

bool is_simmetric(int* arr)
{
	bool res{ 1 };
	int i{};
	while (i < size / 2 && res)
	{
		if (arr[i] != arr[size - i - 1])
			res = 0;
		else
			++i;
	}
	return res;
}

int task1(int matr[][size])
{
	transposition(matr);
	int count{};
	int x, y;
	int* ptr = *matr;
	while (ptr != matr[0] + size * size && count < 2)
	{
		if (is_simmetric(ptr))
		{
			count++;
			if (count == 1) x = (ptr - matr[0]) / size + 1;
			if (count == 2) y = (ptr - matr[0]) / size + 1;
		}
		ptr += size;
	}
	if (count >= 2)
		std::cout << "Симметричные столбцы: " << x << ' ' << y << '\n';
	return count;
}



// task 2
bool last_digit(int x, int digit)
{
	return x % 10 == digit;
}

void fill_null(int* arr, int size_d)
{
	for (int i{}; i < size_d; ++i)
		arr[i] = 0;
}

bool condition(int* arr, int size_d, int digit)
{
	bool res{ 0 };
	int i{};
	while (i < size_d && !res)
	{
		if (last_digit(arr[i], digit))
			res = 1;
		else
			++i;
	}
	return res;
}

void task2(int** matr, int size_d, int n)
{
	int row = size_d - 1;
	for (int i = size_d - 1; i >= 0; --i)
	{
		if (condition(matr[i], size_d, n))
		{
			int* tmp = matr[i];
			for (int j = i; j < row; ++j)
				matr[j] = matr[j + 1];
			matr[row] = tmp;
			row--;
		}
	}
	for (int i = row; i >= 0; --i)
		fill_null(matr[i], size_d);
}



// user interface
void main_menu(int& choice)
{
	std::cout << "\nЧто делаем?\n" <<
		"1. Проверить, есть ли в матрице хотя бы два симметричных столбца, если есть, вывести их номера. (Ст. матрица)\n" <<
		"2. Переместить вниз строки, содержащие числа, оканчивающиеся на заданную цифру, остальные строчки заполнить нулями.\n   Среди оставшихся строк сохранить исходный взаимный порядок. (Дин. матрица)\n" <<
		"3. Выход из программы\n>>> ";
	std::cin >> choice;
}

void source_menu(int& source)
{
	std::cout << "\nУкажите способ заполнения массива:\n" <<
		"1. Вводом с клавиатуры\n" <<
		"2. Чтением из файла\n" <<
		"3. Случайным образом\n>>> ";
	std::cin >> source;
}

int exit()
{
	char isExit;
	std::cout << "\nЗавершить работу? (Y/любая клавиша) ";
	std::cin >> isExit;
	std::cout << '\n';
	if (isExit == 'Y' || isExit == 'y')
		return 3;
}