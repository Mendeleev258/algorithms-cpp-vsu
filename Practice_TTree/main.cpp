#include "Trie_Tree.h"
#include <functional>

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

// Ќайти все слова, имеющие заданное окончание
void print_words_ending(ttree::ptrNODE t, std::string find_word, std::string cur_word) // passed
{
    if (t->eow && cur_word.rfind(find_word) == cur_word.length() - find_word.length())
        std::cout << cur_word << std::endl;
    for (int i = 0; i < 26; i++)
        if (t->ptrs[i])
            print_words_ending(t->ptrs[i], find_word, cur_word + char(i + 'a'));
}

// ѕосчитать количество слов
int count_words(ttree::ptrNODE t)
{
    int res{};
    if (t->eow)
        res = 1;
    for (int i{}; i < 26; ++i)
        if (t->ptrs[i])
            res += count_words(t->ptrs[i]);
    return res;
}

// ѕосчитать количество слов, начинающихс€ с заданной подстроки
int count_words_beginning(ttree::ptrNODE t, std::string find_word, int i)
{
    int res{};
    if (t->ptrs[find_word[i] - 'a'])
    {
        if (find_word.length() > i)
            res = count_words_beginning(t->ptrs[find_word[i] - 'a'], find_word, i + 1);
        else
            res = count_words(t);
    }
    return res;
}

// ѕосчитать количество слов, содержащих заданную букву 'a'
int count_words_with(ttree::ptrNODE t, char c)
{
    int res{};
    for (int i{}; i < 26; ++i)
    {
        if (t->ptrs[i])
        {
            if (i == c - 'a')
                res = count_words(t->ptrs[i]);
            else
                res += count_words_with(t->ptrs[i], c);
        }
    }
    return res;
}


// ѕосчитать количество слов, которые содержат определенное количество 
bool is_vowel(int c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int count_words_vowels(ttree::ptrNODE t, int user_count, int count)
{
    int res{};
    for (int i{}; i < 26; ++i)
    {
        if (t->ptrs[i])
        {
            if (is_vowel(i + 'a'))
                res += count_words_vowels(t->ptrs[i], user_count, count + 1);
            else
                res += count_words_vowels(t->ptrs[i], user_count, count);
            if (t->ptrs[i]->eow && user_count == count)
                res += 1;
        }
    }
    return res;
}

void delete_all_with(ttree::ptrNODE t, std::string user_word, std::string word);


int main()
{
    ttree::TTREE tree("data.txt");
    tree.print(true);
    std::cout << count_words(tree.get_root()) << '\n';
    std::cout << count_words_beginning(tree.get_root(), "gar", 0) << '\n';
    std::cout << count_words_with(tree.get_root(), 'b') << '\n';
    std::cout << count_words_vowels(tree.get_root(), 1, 0) << '\n';
}

