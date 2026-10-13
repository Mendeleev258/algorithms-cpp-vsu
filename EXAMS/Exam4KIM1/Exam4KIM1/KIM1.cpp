#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <thread>
#include "HT1.h"

std::unordered_map<std::string, int> task1(std::ifstream &file, 
	std::function<bool(std::string)> lambda, int& max_count) 
{
	std::string str{};
	std::unordered_map<std::string, int> result;
	while (file >> str)
	{
		if (lambda(str))
		{
			result[str]++;
			if (result[str] > max_count)
				max_count = result[str];
		}
	}
	return result;
}

bool task2(HashTableInt& hash_table, const std::string key)
{
	bool deleted = false;
	int index = hash_table.hash(key);
	while (!(hash_table.table[index].used == 0 || hash_table.table[index].used == 1 && hash_table.table[index].info.first == key))
		index = (index + 1) % hash_table.max_size;
	if (hash_table.table[index].used == 1)
	{
		deleted = true;
		hash_table.table[index].used = -1;
	}
	return deleted;
}


constexpr const int N = 10;
int matrix[N][N];

int count_of_zeroes{};
int sum = matrix[0][0];

int max_sum{}, min_sum{ -1 };

void task3(int i, int j)
{
	if (i == N - 1 && j == N - 1 && count_of_zeroes == 2)
	{
		if (sum > max_sum)
			max_sum = sum;
		if (sum < min_sum || min_sum == -1)
			min_sum = sum;
	}
	else
	{
		if (i < N - 1)
		{
			sum += matrix[i + 1][j];
			if (matrix[i + 1][j] == 0)
				count_of_zeroes++;

			task3(i + 1, j);

			sum -= matrix[i + 1][j];
			if (matrix[i + 1][j] == 0)
				count_of_zeroes--;
		}
		if (j < N - 1)
		{
			sum += matrix[i][j + 1];
			if (matrix[i][j + 1] == 0)
				count_of_zeroes++;

			task3(i, j + 1);

			sum -= matrix[i][j + 1];
			if (matrix[i][j + 1] == 0)
				count_of_zeroes--;
		}
	}
}


const size_t COUNT = 555;
const size_t NTHREADS = 4;
volatile LONG global_max;
volatile LONG global_index;

void local_max(int* arr, size_t left, size_t right)
{
	int max_value = arr[left];
	size_t index = left;
	for (size_t i = left + 1; i < right; ++i)
	{
		if ((abs(arr[i]) % 2) != 0 && (abs(max_value) % 2 == 0 || arr[i] >= max_value))
		{
			max_value = arr[i];
			index = i;
		}

		LONG current_max_value = InterlockedCompareExchange(&global_max, 0, 0);
		if (max_value > current_max_value || max_value == current_max_value && index > global_index || current_max_value % 2 == 0)
		{
			InterlockedCompareExchange(&global_max, max_value, current_max_value);
			InterlockedExchange(&global_index, index);
		}
	}
}

size_t task4(int* arr)
{
	std::thread t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;

	global_max = arr[0];
	global_index = 0;

	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::thread(local_max, arr, block * i, block * (i + 1));
	}

	local_max(arr, block * (NTHREADS - 1), COUNT);
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();

	return global_index;
}


int main()
{
	// task 1
	std::cout << "task 1:\n";
	std::ifstream file("data.txt");
	int max_count = 0;
	std::unordered_map<std::string, int> map = task1(file, [](std::string str) { return str.find("o") != std::string::npos; }, max_count);
	for (const auto& pair : map)
	{
		if (pair.second == max_count)
			std::cout << pair.first << " (" << pair.second << ")\n";
	}

	// task 2
	std::cout << "\ntask 2:\n";
	std::ifstream file2("Data_2.txt");
	HashTableInt hash_table(15);
	hash_table.fill(file2);
	hash_table.print();
	if (task2(hash_table, "sdff"))
		std::cout << "Key 'sdff' deleted successfully.\n";
	else
		std::cout << "Key 'sdff' not found.\n";
	hash_table.print();
	
	// task 3
	std::cout << "\ntask3:\n";
	std::ifstream file3("Matrix3_1.txt");
	
	for (int i{}; i < N; ++i)
		for (int j{}; j < N; ++j)
			file3 >> matrix[i][j];

	task3(0, 0);
	std::cout << "Max cost: " << max_sum << '\n';
	std::cout << "Min cost: " << min_sum << '\n';

	// task 4
	std::cout << "\ntask 4:\n";
	std::ifstream file4("Numbers_4.txt");

	int* arr = new int[COUNT];
	for (int i{}; i < COUNT; ++i)
		file4 >> arr[i];

	std::cout << "Answer: " << task4(arr) << '\n';

	return 0;
}