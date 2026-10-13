#include <iostream>
#include <fstream>
#include "Flist.h"

bool add_sizes(FLIST& list);
void task(std::ifstream& input, std::ofstream& output);

int main()
{
	std::ifstream file("file.txt");
	std::ofstream output_file("output.txt");
	task(file, output_file);
}

bool add_sizes(FLIST& list)
{
	bool result{ false };
	TInfo cnt{ 1 };
	ptrNODE ptr = list.get_head();
	ptrNODE tmp_ptr = nullptr;
	while (ptr->next->next)
	{
		if (ptr->next->info == ptr->next->next->info)
		{
			if (!tmp_ptr)
				tmp_ptr = ptr;
			cnt++;
			result = true;
		}
		else
		{
			if (cnt > 1)
			{
				list.add_after(tmp_ptr, cnt);
				cnt = 1;
				tmp_ptr = nullptr;
			}
		}
		ptr = ptr->next;
	}
	if (cnt > 0)
		list.add_after(tmp_ptr, cnt);
	return result;
}

void task(std::ifstream& input, std::ofstream& output)
{
	FLIST list;
	list.create_by_queue(input);
	bool no_flag = !add_sizes(list);
	ptrNODE ptr = list.get_head()->next;
	while (ptr)
	{
		output << ptr->info << ' ';
		ptr = ptr->next;
	}
	if (no_flag)
		output << "\nNO!";

}
