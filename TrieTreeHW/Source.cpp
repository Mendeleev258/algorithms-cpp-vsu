#include <iostream>
#include <fstream>

struct NODE
{
    bool eow{};
    NODE* ptrs[26]{};
    NODE()
    {
        eow = false;
        for (int i{}; i < 26; ++i)
            ptrs[i] = nullptr;
    }
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
    root = nullptr;
}

bool empty(TrieTree& root)
{
    return root == nullptr;
}

void add(TrieTree& root, const std::string& word, int i)
{
    if (!root)
    {
        root = new NODE();
    }
    if (word.length() - 1 < i)  // все ли буквы размещены
        root->eow = true;
    else
        add(root->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptrs_empty(TrieTree& root)
{
    bool result{ true };
    int i{};
    while (i < 26 && result)
    {
        if (root->ptrs[i])
            result = false;
        else
            ++i;
    }
    return result;
}

void del(TrieTree& root, const std::string& word, int i)
{
    if (root)
    {
        if (i <= word.length() - 1)
            del(root->ptrs[word[i] - 'a'], word, i + 1);
        else
        {
            root->eow = false;
            if (all_ptrs_empty(root))
            {
                delete root;
                root = nullptr;
            }
        }
    }
}

void print(TrieTree& root, std::string word)
{
    if (root->eow)
        std::cout << word << '\n';
    for (int i{}; i < 26; ++i)
        if (root->ptrs[i])
            print(root->ptrs[i], word + char(i + 'a'));
}

void clear(TrieTree& root)  // постфиксный обязательно
{
    for (int i{}; i < 26; ++i)
        if (root->ptrs[i])
            clear(root->ptrs[i]);
    delete root;
    root = nullptr;
}

TrieTree copy(TrieTree& root)
{
    TrieTree result{};
    if (root)
    {
        result = new NODE;
        result->eow = root->eow;
        for (int i{}; i < 26; ++i)
            if (root->ptrs[i])
                result->ptrs[i] = copy(root->ptrs[i]);
    }
    return result;
}

// homework

void count_of_words(TrieTree root, int& res)
{
    if (root->eow)
        res++;
    for (int i{}; i < 26; ++i)
        if (root->ptrs[i])
            count_of_words(root->ptrs[i], res);
}

TrieTree find(TrieTree root, std::string& word_tree, std::string word_find)
{
    TrieTree res{};
    for (int i{}; i < 26; ++i)
    {
        if (root->ptrs[i])
        {
            word_tree += char(i + 'a');
            if (word_find.find(word_tree) == 0)
            {
                if (word_tree == word_find)
                    res = root->ptrs[i];
                else
                    find(root->ptrs[i], word_tree, word_find);
            }
            else
                word_tree.erase(word_tree.length() - 1);
        }
    }
    return res;
}

void count_of_words_from(TrieTree root, int res, std::string& word_tree, std::string word_find)
{
    TrieTree new_root = find(root, word_tree, word_find);
    return count_of_words(new_root, res);
}

int main()
{
    std::ifstream file("data.txt");
    if (file)
    {
        TrieTree root{};
        init(root);
        std::string word{};
        while (file >> word)
        {
            if (word.length())
                add(root, word, 0);
        }
        print(root, "");
        
        int count{};
        // task 1
        /*count_of_words(root, count);
        std::cout << count << '\n';*/

        // task 2
        std::string word_tree{};
        std::string word_find{ "ca" };
        file.close();
    }
    else
        std::cout << "FILE ERROR\n";
}
