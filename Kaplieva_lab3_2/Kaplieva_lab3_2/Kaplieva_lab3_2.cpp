#include <iostream>
#include <fstream>

const int n = 35;
const int m = 15;
const int LEN = 255;

// interface

bool is_token(char c);
void skip_token(std::ifstream& file, char& c);
int read_word(std::ifstream& file, char& c, char* word);
void create_matrix(std::ifstream& file, char matrix[][m], int len[], int& row);
int check_file(std::ifstream& file);
void out_word(std::ofstream& file, char* word, int len);
void out_matrix(std::ofstream& file, char matrix[][m], int len[], int row);

// task

bool is_vowel(char c);
bool correct_word(char* word, int len);
int compare(char word1[], int len1, char word2[], int len2);
template <typename T>
void my_swap(T& a, T& b);
void swap_words(char* word1, int len1, char* word2, int len2);
void simple_choice_sort(char matrix[][m], int len[], int row);
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

bool is_token(char c)
{
	return (c == ' ' || c == ',' || c == ';' || c == ':' || c == '\n' || c == '.' || c == '-' || c == EOF);
}

void skip_token(std::ifstream& file, char& c)
{
	while (!file.eof() && is_token(c))
		c = file.get();
}

int read_word(std::ifstream& file, char& c, char* word)
{
	int len{};
	while (!file.eof() && !is_token(c))
	{
		word[len++] = c;
		c = file.get();
	}
	return len;
}

void create_matrix(std::ifstream& file, char matrix[][m], int len[], int& row)
{
	row = 0;
	char c = file.get();
	while (!file.eof())
	{
		skip_token(file, c);
		if (!is_token(c))
		{
			len[row] = read_word(file, c, matrix[row]);
			if (correct_word(matrix[row], len[row]))
				row++;
		}
	}
}

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

void out_word(std::ofstream& file, char* word, int len)
{
	for (int i{}; i < len; ++i)
		file << word[i];
	file << '\n';
}

void out_matrix(std::ofstream& file, char matrix[][m], int len[], int row)
{
	for (int i{}; i < row; ++i)
		out_word(file, matrix[i], len[i]);
}


// task

bool is_vowel(char c)
{
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'y' || c == 'Y';
}

bool correct_word(char* word, int len)
{
	int i{};
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

int compare(char word1[], int len1, char word2[], int len2)
{
	auto signL = [](int x) {return x == 0 ? 0 : x / abs(x); };
	int len = len1 < len2 ? len1 : len2;
	int result{}, i{};
	while (i < len && word1[i] == word2[i])
		++i;
	if (i < len)
		result = signL(word1[i] - word2[i]);
	else
		result = signL(len1 - len2);
	return result;
}

template <typename T>
void my_swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

void swap_words(char* word1, int len1, char* word2, int len2)
{
	int max_len = (len1 > len2) ? len1 : len2;
	for (int i = 0; i < max_len; ++i)
		my_swap(word1[i], word2[i]);
}

void simple_choice_sort(char matrix[][m], int len[], int row)
{
	for (int i{}; i < row; ++i)
		for (int j{}; j < row - i - 1; ++j)
			if (compare(matrix[j], len[j], matrix[j + 1], len[j + 1]) > 0)
			{
				my_swap(len[j], len[j + 1]);
				swap_words(matrix[j], len[j], matrix[j + 1], len[j + 1]);
			}
}

void task(std::ifstream& input, std::ofstream& output)
{
	char matrix[n][m];
	int len[n];
	int row{};
	create_matrix(input, matrix, len, row);
	simple_choice_sort(matrix, len, row);
	out_matrix(output, matrix, len, row);
}
