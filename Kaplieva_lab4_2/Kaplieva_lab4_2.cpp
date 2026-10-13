#include <iostream>
#include <fstream>


const int n = 35;
const int m = 15;
const int LEN = 255;

// interface

int check_file(std::ifstream& file);
int create_matrix(std::ifstream& file, char matrix[][m]);
void out_word(std::ofstream& file, char* word);
void out_matrix(std::ofstream& file, char matrix[][m], int row);

// task

bool is_vowel(char c);
bool correct_word(char* word);
void swap_words(char* word1, char* word2);
void simple_choice_sort(char matrix[][m], int row);
void task(std::ifstream& input, std::ofstream& output);

int main()
{
	std::ifstream input("inp.txt");
	switch (check_file(input))
	{
	case -1:
		std::cout << "File not found\n";
		break;
	case 0:
		std::cout << "Empty file\n";
		break;
	default:
		std::cout << "Correct file\n";
		std::ofstream output("out.txt");
		task(input, output);
		output.close();
	}
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

int create_matrix(std::ifstream& file, char matrix[][m])
{
	int row{};
	char* context{}, *ptr{}, line[LEN];
	while (file.getline(line, LEN) && row < n)
	{
		ptr = strtok_s(line, " ,.;:-", &context);
		while (ptr && row < n)
		{
			strcpy_s(matrix[row], m, ptr);
			ptr = strtok_s(0, " ,.;:-", &context);
			if (correct_word(matrix[row]))
				++row;
		}
	}
	return row;
}

void out_word(std::ofstream& file, char* word)
{
	size_t len = strlen(word);
	for (size_t i{}; i < len; ++i)
		file << word[i];
	file << '\n';
}

void out_matrix(std::ofstream& file, char matrix[][m], int row)
{
	for (int i{}; i < row; ++i)
		out_word(file, matrix[i]);
}

// task

bool is_vowel(char c)
{
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'y' || c == 'Y';
}

bool correct_word(char* word)
{
	int i{}; 
	size_t len{ strlen(word) };
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

void swap_words(char* word1, char* word2) 
{
	char temp[m];
	strcpy_s(temp, sizeof(temp), word1);
	strcpy_s(word1, sizeof(word1), word2);
	strcpy_s(word2, sizeof(word2), temp);
}

void simple_choice_sort(char matrix[][m], int row)
{
	for (int i{}; i < row; ++i)
		for (int j{}; j < row - i - 1; ++j)
		{
			if (strcmp(matrix[j], matrix[j + 1]) > 0)
				swap_words(matrix[j], matrix[j + 1]);
		}
}

void task(std::ifstream& input, std::ofstream& output)
{
	char matrix[n][m];
	int row = create_matrix(input, matrix);
	simple_choice_sort(matrix, row);
	out_matrix(output, matrix, row);
}


