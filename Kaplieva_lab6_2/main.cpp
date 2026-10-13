#include "Array.h"

std::string exp_post(std::ifstream& file_bin, int& count);

int main()
{
	
	std::ifstream file_txt("workers.txt");
	if (file_txt)
	{
		// Array arr(file_txt);
		// arr.print();
		// std::cout << "\n=======SORTED=======\n";
		// arr.soritng();
		// arr.print();
		// arr.to_binary("workers_bin.txt");
		std::ifstream file_bin("workers_bin.txt", std::ios::binary);
		if (file_bin)
		{
			int count{};
			std::string res = exp_post(file_bin, count);
			if (count > 1)
				std::cout << "There are " << count << " most paid posts: " << res << '\n';
			else
				std::cout << "Most paid post is: " << res << '\n';
		}
		else std::cout << "bin file error\n";
	}
	else std::cout << "text file error\n";

}

std::string exp_post(std::ifstream& file_bin, int& count)
{
	std::string result = "";
	Worker worker;
	count = 1;
	int max{};
	while (file_bin.read((char*)(&worker), sizeof(Worker)))
	{
		if (worker.get_salary() > max)
		{
			count = 1;
			max = worker.get_salary();
			result = worker.get_post();
		}
		else 
			if (worker.get_salary() == max)
			{
				if (result.find(worker.get_post()) == std::string::npos)
				{
					count++;
					result += ", " + worker.get_post();
				}
			}
	}
	return result;
}
