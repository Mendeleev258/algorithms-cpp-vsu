#include "Trie_Tree.h"

void add(ttree::ptrNODE& t, const std::string word, short i)
{
	if (!t)
	{
		t = new ttree::NODE();
	}
	if (short(word.length()) - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

ttree::TTREE::TTREE(const char* file_name)
{
	root = nullptr;
	std::ifstream file(file_name);
	std::string word;
	while (!file.eof())
	{
		std::getline(file, word);
		if (word.length())
			add(root, word, 0);
	}
}

bool ttree::TTREE::empty()
{
	return !root;
}

bool is_all_prts_empty(ttree::ptrNODE t)
{
	bool result = true;
	int i = 0;
	while (i < 26 && result)
		if (!t->ptrs[i])
			i++;
		else
			result = false;
	return result;
}

bool ttree::TTREE::all_prts_empty(ptrNODE t)
{
	return is_all_prts_empty(t);
}

void clear(ttree::ptrNODE& t)
{
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

ttree::TTREE::~TTREE()
{
	clear(root);
}

void print_words(ttree::ptrNODE t, std::string word)
{
	if (t->eow)
		std::cout << word << std::endl;
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			print_words(t->ptrs[i], word + char(i + 'a'));
}

void print_vines(ttree::ptrNODE t, std::string word)
{
	if (is_all_prts_empty(t))
		std::cout << word << std::endl;
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			print_vines(t->ptrs[i], word + char(i + 'a'));
}

void ttree::TTREE::print(bool words, std::ostream& stream)
{
	if (words)
		print_words(root, "");
	else
		print_vines(root, "");
}

void ttree::printW(ttree::ptrNODE t, std::string word)
{
	if (t->eow)
		std::cout << word << std::endl;
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			printW(t->ptrs[i], word + char(i + 'a'));
}
