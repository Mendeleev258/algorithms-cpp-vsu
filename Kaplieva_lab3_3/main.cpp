#include "TrieTree.h"
#include <functional>
#include <stack>


void task(ttree::ptrNODE root, std::string find_word, std::string cur_word, int j)
{
	for (int i{}; i < 26; ++i)
	{
		if (root->ptrs[i])
		{
			if (j >= find_word.length())
				j = 0;
			if (char(i + 'a') == find_word[j])
			{
				if (root->ptrs[i]->eow && j == find_word.length() - 1)
					std::cout << cur_word + char(i + 'a') << '\n';
				task(root->ptrs[i], find_word, cur_word + char(i + 'a'), j + 1);
			}
			else
				task(root->ptrs[i], find_word, cur_word + char(i + 'a'), j);
		}
	}
}


int main()
{
	ttree::TTREE tree("data.txt");
	tree.print(true);
	std::string word = "obr";
	std::string cur_word = "";
	std::cout << "Words which end is " << word << ":\n";
	task(tree.get_root(), word, cur_word, 0);
}