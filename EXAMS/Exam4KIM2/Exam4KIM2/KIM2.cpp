#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <functional>
#include <future>
#include <atomic>
#include "HT2.h"

std::unordered_map<std::string, int> task1(std::ifstream& file, std::function<bool(std::string)> lambda)
{
	std::unordered_map<std::string, int> result;
	std::string str{};

	while (file >> str)
		if (lambda(str))
			result[str]++;
	return result;
}

std::string task2(HashTableBool& ht, std::string key)
{
	std::string result{};
	int index = ht.hash(key);

	while (!(ht.table[index].used == false || ht.table[index].info.first == key && ht.table[index].used == true))
		index = (index + 1) % ht.max_size;

	if (ht.table[index].used)
		result = ht.table[index].info.second;

	return result;
}

constexpr const int N = 10;
int matrix[N][N];
int ways_count{ 1 }, sum{ matrix[0][0] }, max_sum{};

void task3(int i, int j)
{
	if (i == N - 1 && j == N - 1)
	{
		if (sum > max_sum)
		{
			max_sum = sum;
			ways_count = 1;
		}
		if (sum == max_sum)
			ways_count++;
	}

	if (i < N - 1)
	{
		sum += matrix[i + 1][j];
		task3(i + 1, j);
		sum -= matrix[i + 1][j];
	}
	if (j < N - 1)
	{
		sum += matrix[i][j + 1];
		task3(i, j + 1);
		sum -= matrix[i][j + 1];
	}
}

const size_t COUNT = 10;
const size_t NTHREADS = 4;

void min_local(int* arr, size_t left, size_t right, std::atomic_int& result)
{
	for (size_t i = left; i < right; ++i)
	{
		if (abs(arr[i]) % 2 == 0)
		{
			int curr = result.load();
			if (abs(curr) % 2 || arr[i] <= curr)
				result.compare_exchange_weak(curr, arr[i]);
		}
	}
}

int task4(int* arr)
{
	std::future<void> t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;

	std::atomic_int global_min{ arr[0] };

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i] = std::async(std::launch::async, min_local, arr, block * i, block * (i + 1), std::ref(global_min));

	min_local(arr, block * (NTHREADS - 1), COUNT, std::ref(global_min));
	
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].get();

	return global_min;
}

int main()
{
	// task 1
	std::cout << "task 1:\n";
	std::ifstream file("Text_1.txt");
	std::string c = "v";
	std::unordered_map<std::string, int> map = task1(file, [c](std::string x) { return x.substr(x.length() - 1) == c; });

	for (const auto& x : map)
		if (x.second == 1)
			std::cout << x.first << ' ';
	std::cout << '\n';

	// task 2
	std::cout << "\ntask 2:\n";
	std::ifstream file2("Data_2.txt");

	HashTableBool ht(15);
	ht.fill(file2);
	ht.print();

	std::string info = task2(ht, "dg");
	if (info.empty())
		std::cout << "Not found\n";
	else
		std::cout << info << '\n';

	// task 3
	std::cout << "\ntask 3:\n";
	std::ifstream file3("Matrix3_2.txt");

	for (int i{}; i < N; ++i)
		for (int j{}; j < N; ++j)
			file3 >> matrix[i][j];

	task3(0, 0);
	std::cout << "Max cost: " << max_sum << "\nCount of ways: " << ways_count << '\n';

	// task 4
	std::cout << "\ntask 4:\n";
	std::ifstream file4("Numbers_4.txt");

	int* arr = new int[COUNT];
	for (int i{}; i < COUNT; ++i)
		file4 >> arr[i];

	std::cout << "Answer: " << task4(arr) << '\n';
}