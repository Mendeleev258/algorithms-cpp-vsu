#include "FLIST.h"

bool good_row(int* begin, int m)
{
	int cnt{};
	for (int* ptr = begin; ptr != begin + m - 1; ++ptr)
	{
		if ((*ptr % 7 == 0 && *(ptr + 1) % 7 != 0) || (*ptr % 7 != 0 && *(ptr + 1) % 7 == 0))
			cnt++;
	}
	return cnt % 2 == 0 && cnt > 0;
}

int task1(int** matr, int n, int m)
{
	bool flag{};
	int i{};
	while (i < n && !flag)
	{
		if (good_row(matr[i], m))
			flag = true;
		else
			++i;
	}
	if (!flag)
		i = -1;
	return i;
}

constexpr int str_maxlen = 500;
constexpr int word_maxlen = 25;

void task2(std::ifstream& file, int n)
{
	auto lambda = [](char* word)
		{
			size_t len = strlen(word);
			return len % 2 == 0 && !memchr(word, word[len - 1], len - 1);
		};
	char* word{}, *context{}, line[str_maxlen];
	int row{}, cnt{};
	while (file.getline(line, str_maxlen) && cnt < 20)
	{
		word = strtok_s(line, " ", &context);
		while (word)
		{
			if (lambda(word))
				cnt++;
			word = strtok_s(0, " ", &context); // перейти к следующему слову
		}
		if (cnt >= n)
			std::cout << row << ' ';
		cnt = 0;
		row++;
	}
}

bool task3_range(FLIST& list, ptrNODE& begin, ptrNODE& end, std::function<bool(int)> lambda)
{
	ptrNODE ptr = list.get_head()->next;
	begin = nullptr;
	end = nullptr;
	while (ptr)
	{
		if (lambda(ptr->info))
		{
			begin = end;
			end = ptr;
		}
		ptr = ptr->next;
	}
	return begin;
}

void task3(FLIST& list)
{
	ptrNODE begin{}, end{}, ptr{};
	if (task3_range(list, begin, end, [](int x) {return abs(x) > 9 && abs(x) < 100; }))
		ptr = begin->next;
	while (ptr && ptr != end)
	{
		if (ptr->info % 3 == 0)
		{
			list.adding_by_pointer(ptr->next, ptr->info);
			ptr = ptr->next;
		}
		ptr = ptr->next;
	}
}

ptrNODE findmin(FLIST& list)
{
	ptrNODE ptr = list.get_head()->next;
	ptrNODE min = ptr;
	while (ptr->next)
	{
		if (ptr->next->info < min->next->info)
			min = ptr;
		ptr = ptr->next;
	}
	return min;
}

void task4(FLIST& list)
{
	ptrNODE min_prev = findmin(list);
	if (min_prev)
	{
		ptrNODE tail{}, ptr = list.get_head();
		while (ptr) // tail = list.get_tail();
		{
			if (!ptr->next)
				tail = ptr;
			ptr = ptr->next;
		}
		tail->next = min_prev->next;
		ptrNODE tmp = min_prev->next;
		min_prev->next = min_prev->next->next;
		tmp->next = nullptr;
		list.set_tail(tmp);
	}
}

void task5(ptrNODE startptr, FLIST& newlist, int& cnt)
{
	if (startptr)
	{
		task5(startptr->next, newlist, cnt);
		if (cnt % 2 == 0)
			newlist.adding_by_pointer(newlist.get_head()->next, startptr->info);
		cnt++;
	}
}

int main()
{
	// task 1
	/*std::ifstream fmatrix("matrix_1.txt");
	int n{}, m{};
	fmatrix >> n >> m;

	int** matr = new int* [n];
	for (int i{}; i < m; ++i)
		matr[i] = new int[m];
	
	for (int i{}; i < n; ++i)
		for (int j{}; j < m; ++j)
			fmatrix >> matr[i][j];

	for (int i{}; i < n; ++i)
	{
		for (int j{}; j < m; ++j)
			std::cout << matr[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << "task 1: " << task1(matr, n, m) << '\n';*/

	// task 2
	/*std::ifstream ftext("text_1.txt");
	task2(ftext, 2);*/

	// task 3
	/*std::ifstream fnumbers("numbers_1.txt");
	FLIST list;
	list.create_by_queue(fnumbers);
	list.print("");
	ptrNODE begin{}, end{};
	task3(list);
	list.print("");*/

	// task 4
	/*std::ifstream fnumbers("numbers_1.txt");
	FLIST list;
	list.create_by_queue(fnumbers);
	list.print("");
	task4(list);
	list.print("");*/

	// task 5 includes 1st member of list (idk why)
	/*std::ifstream fnumbers("numbers_1.txt");
	FLIST list;
	list.create_by_queue(fnumbers);
	list.print("");
	FLIST newlist;
	int cnt = 1;
	task5(list.get_head(), newlist, cnt);
	newlist.print("");*/
}