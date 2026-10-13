#include <iostream>
#include <string>
#include <fstream>

std::string token(" ,.:;-");
const int n = 35;
const int m = 15;


// interface

int check_file(std::ifstream& file);
int create_matrix(std::ifstream& file, std::string matrix[n]);
void out_matrix(std::ofstream& file, std::string matrix[n], int row);

// task

bool is_vowel(char c);
bool correct_word(const std::string& word);
void simple_choice_sort(std::string matrix[n], int row);
void task(std::ifstream& input, std::ofstream& output);

int main()
{
	bool correctfile{ false };
	do
	{
		std::string filename;
		std::cout << "Enter file name\n>>> ";
		std::cin >> filename;
		std::cin.ignore();
		std::ifstream input(filename);
		switch (check_file(input))
		{
		case -1:
			std::cout << "File not found\n";
			break;
		case 0:
			std::cout << "Empty file\n";
			break;
		default:
			correctfile = true;
			std::cout << "Correct file\n";
			std::ofstream output("out.txt");
			task(input, output);
			input.close();
			output.close();
		}
	} while (!correctfile);
}

// interface

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

int create_matrix(std::ifstream& file, std::string matrix[n])
{
	int row{};
	std::string line;
	while (getline(file, line) && row < n)
	{
		size_t start{}, end{};
		while ((start = line.find_first_not_of(token, end)) != std::string::npos && row < n)
		{
			end = line.find_first_of(token, start);
			matrix[row] = line.substr(start, end - start);
			if (correct_word(matrix[row]))
				row++;
		}
	}
	return row;
}

void out_matrix(std::ofstream& file, std::string matrix[n], int row)
{
	for (int i{}; i < row; ++i)
		file << matrix[i] << '\n';
}

// task 

bool is_vowel(char c)
{
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'y' || c == 'Y';
}

bool correct_word(const std::string& word)
{
	int i{};
	size_t len{ size(word) };
	bool res{ true };
	while (i < len && res)
	{
		if (i % 2 == 0)
			res = !is_vowel(word[i]);
		else
			res = is_vowel(word[i]);
		++i;
	}
	return res;
}

void simple_choice_sort(std::string matrix[n], int row)
{
	for (int i{}; i < row; ++i)
		for (int j{}; j < row - i - 1; ++j)
		{
			if (matrix[j].compare(matrix[j + 1]) > 0)
				std::swap(matrix[j], matrix[j + 1]);
		}
}

void task(std::ifstream& input, std::ofstream& output)
{
	std::string matrix[n];
	int row = create_matrix(input, matrix);
	simple_choice_sort(matrix, row);
	out_matrix(output, matrix, row);
}


