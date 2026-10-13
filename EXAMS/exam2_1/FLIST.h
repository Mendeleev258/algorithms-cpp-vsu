#pragma once
#include "NODE.h";
#include <iostream>
#include <fstream>
#include <functional>

using ptrNODE = NODE*;

struct FLIST
{
private:
    ptrNODE head, tail;
    size_t size;
public:
    FLIST()
    {
        tail = head = new NODE(0);
        size = 0;
    }
    ~FLIST();
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
    void del_after(ptrNODE ptr);
    void create_by_queue(std::ifstream& file);
    void print(const char* message, std::ostream& stream = std::cout);
    void sotring();

    void clear_fragment(ptrNODE begin, ptrNODE end = nullptr);
    void del_from_tail();
    ptrNODE find_if(ptrNODE begin, ptrNODE end, std::function<bool(TInfo)> condition);
};

