#include "Array.h"

// returns an array (as an argument) with the average count of days in a business trip by posts
// INDEXES: 0 - Analyst, 1 - Manager, 2 - Programmer, 3 - Scrum-master, 4 - Tester
void avg_days(const Array& sorted_arr, int* res);

// prints an average count of days in a business trip by posts
void print_avg_days(const int* arr);

// prints workers which were in a business trips longer than average count of days by their post
void print_travelers(const Array& sorted_arr, int* arr_days);


int main()
{
	std::ifstream file("workers.txt");
	Array arr(file);
	file.close();

	arr.soritng();
	std::cout << "Full list of workers:\n";
	arr.print();
	std::cout << '\n';

	int* arr_days = new int[5];
	avg_days(arr, arr_days);
	print_avg_days(arr_days);
	std::cout << '\n';

	print_travelers(arr, arr_days);
	delete[] arr_days;
}


void avg_days(const Array& sorted_arr, int* res)
{
	int i{};
	int count_of_workers{ 1 };
	int post_index{};
	int sum_of_days{ sorted_arr.arr[i]->get_days() };
	while (i < sorted_arr.size - 1)
	{
		if (!strcmp(sorted_arr.arr[i]->get_post(), sorted_arr.arr[i + 1]->get_post()))
		{
			sum_of_days += sorted_arr.arr[i + 1]->get_days();
			count_of_workers++;
		}
		else
		{
			res[post_index] = sum_of_days / count_of_workers;
			count_of_workers = 1;
			sum_of_days = sorted_arr.arr[i + 1]->get_days();
			post_index++;
		}
		++i;
	}
	res[post_index] = sum_of_days / count_of_workers;
}

void print_avg_days(const int* arr)
{
	std::cout << "Average count of days in a business trip by posts:\n"
		<< "Analyst: " << arr[0] << '\n'
		<< "Manager: " << arr[1] << '\n'
		<< "Programmer: " << arr[2] << '\n'
		<< "Scrum-master: " << arr[3] << '\n'
		<< "Tester: " << arr[4] << '\n';
}

void print_travelers(const Array& sorted_arr, int* arr_days)
{
	std::cout << "Workers which were in business trips longer than average:\n";
	int i{}, post_index{};
	while (i < sorted_arr.size - 1)
	{
		if (sorted_arr.arr[i]->get_days() > arr_days[post_index])
			sorted_arr.arr[i]->print();
		if (strcmp(sorted_arr.arr[i]->get_post(), sorted_arr.arr[i + 1]->get_post()))
			post_index++;
		i++;
	}
	if (sorted_arr.arr[i]->get_days() > arr_days[post_index])
		sorted_arr.arr[i]->print();
}
