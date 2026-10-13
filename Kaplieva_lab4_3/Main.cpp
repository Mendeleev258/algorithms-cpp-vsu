#include <iostream>
#include <fstream>
#include "FLIST.h"

int compare(ptrBook bookA, ptrBook bookB);
std::string max_count_by_spec(FLIST& list);
FLIST task(FLIST& list);

int main()
{
    std::ifstream file("data.txt");
    FLIST list(file);
    
    std::cout << "\n\nSORTED:\n\n\n";
    list.sorting(compare);
    list.print("");
 
    FLIST res = task(list);
    
    // constructor and operator demo
    std::cout << '\n';
    FLIST tmp(res); // copy constructor
    FLIST tmp1;
    tmp1 = res; // copy operator
    FLIST tmp2(std::move(tmp)); // move constructor
    FLIST tmp3; 
    tmp3 = std::move(tmp1); // move operator

    std::cout << "\nRESULT:\n\n";
    tmp3.print("");
}



int compare(ptrBook bookA, ptrBook bookB)
{
    return strcmp(bookA->get_spec(), bookB->get_spec());
}

std::string max_count_by_spec(FLIST& list)
{
    int count{ 1 }, max_count{};
    std::string res{};
    ptrNODE ptr = list.get_head()->next;
    while (ptr->next)
    {
        if (compare(ptr->info, ptr->next->info) == 0)
            count++;
        else
        {
            if (max_count == count)
                res += ptr->info->get_spec();
            if (max_count < count)
            {
                max_count = count;
                res = ptr->info->get_spec();
            }
            count = 1;
        }
        ptr = ptr->next;
    }
    if (max_count == count)
        res += ptr->info->get_spec();
    if (max_count < count)
    {
        max_count = count;
        res = ptr->info->get_spec();
    }
    return res;
}

FLIST task(FLIST& list)
{
    ptrNODE beg = list.get_head()->next;
    ptrNODE ptr = beg;
    FLIST resList;
    int count{}, max_count{};
    while (ptr)
    {
        if (compare(beg->info, ptr->info) == 0)
            count++;
        else
        {
            if (count > max_count)
            {
                max_count = count;
                resList.clear();
                resList.copy(beg, ptr);
            }
            else
            {
                if (count == max_count)
                    resList.copy(beg, ptr);
                else
                    beg = ptr;
            }
            count = 1;
        }
        ptr = ptr->next;
    }
    if (count == max_count)
        resList.copy(beg, ptr);
    return resList;
}
