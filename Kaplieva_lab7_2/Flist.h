#pragma once
#include "Node.h"
#include <iostream>

using ptrNODE = NODE*;

struct FLIST
{
private:
    ptrNODE head, tail;
    size_t size;
    void adding_by_pointer(ptrNODE& ptr, TInfo elem)
    {
        ptr = new NODE(elem, ptr);
        ++size;
    }
    void deleting_by_pointer(ptrNODE& ptr)
    {
        ptrNODE p = ptr;
        ptr = p->next;
        delete p;
        --size;
    }
public:
    FLIST()
    {
        tail = head = new NODE(0);
        size = 0;
    }
    ~FLIST();
    ptrNODE get_head()
    {
        return head;
    }
    ptrNODE get_tail()
    {
        return tail;
    }
    void set_tail(ptrNODE ptr)
    {
        tail = ptr;
    }
    TInfo get_elem(ptrNODE ptr)
    {
        return ptr->info;
    }
    size_t get_size()
    {
        return size;
    }
    bool empty()
    {
        return !head->next;
    }
    void add_to_head(TInfo elem);
    void add_to_tail(TInfo elem);
    void add_after(ptrNODE ptr, TInfo elem);
    void del_from_head();
    void create_by_queue(std::ifstream& file);
    void print(const char* message, std::ostream& stream = std::cout);
};