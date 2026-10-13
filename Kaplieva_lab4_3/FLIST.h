#pragma once
#include "Book.h"
#include <functional>

using ptrBook = Book*;

struct NODE
{
    ptrBook info;
    NODE* next;
    NODE(ptrBook info = nullptr, NODE* ptr = nullptr) : info(info), next(ptr) {}
    ~NODE() { next = nullptr; } // 0
};

using ptrNODE = NODE*;

struct FLIST
{
private:
    ptrNODE head, tail;
    size_t size;
    void adding_by_pointer(ptrNODE& ptr, ptrBook elem)
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
    FLIST(std::ifstream& file);
    FLIST(const FLIST& other);
    FLIST(FLIST&& tmp);    
    FLIST& operator=(const FLIST& other);
    FLIST& operator=(FLIST&& tmp);
    void copy(ptrNODE& beg, ptrNODE end);
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
    ptrBook get_elem(ptrNODE ptr)
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
    void add_to_head(ptrBook elem);
    void add_to_tail(ptrBook elem);
    void add_after(ptrNODE ptr, ptrBook elem);
    void del_from_head();
    void del_after(ptrNODE ptr);
    void print(const char* message, std::ostream& stream = std::cout);
    void sorting(std::function<int(ptrBook, ptrBook)> compare);
    void clear(ptrNODE& begin, ptrNODE& end);
    void clear();
};