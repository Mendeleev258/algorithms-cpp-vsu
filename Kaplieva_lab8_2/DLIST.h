#pragma once
#include "DNODE.h"
#include <functional>

using ptrDNODE = DNODE*;

struct DLIST
{
private:
    ptrDNODE head, tail;
    size_t size;
public:
    DLIST() { head = nullptr, tail = nullptr; }
    DLIST(const char* file_name);
    DLIST(const char* file_name, std::function<int(File, File)> compare);
    ~DLIST();
    void first_node(ptrFile file);
    void print(std::ostream& stream = std::cout);
    void remove(ptrDNODE& ptr);
    void insert_after(ptrDNODE ptr, ptrFile elem);
    void insert_before(ptrDNODE ptr, ptrFile elem);
    bool empty();
    ptrFile get_elem(const ptrDNODE ptr)
    {
        return ptr->info;
    }
    ptrDNODE get_head()
    {
        return head;
    }
};