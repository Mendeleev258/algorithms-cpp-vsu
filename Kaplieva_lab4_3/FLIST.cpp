#pragma once
#include "FLIST.h"

FLIST::FLIST(std::ifstream& file)
{
    head = new NODE();
    tail = head;
    while (!file.eof())
    {
        ptrBook book = new Book(file);
        add_to_tail(book);
        book->up_count();
    }
}

FLIST::FLIST(const FLIST& other)
{
    std::cout << "Constructor copy\n";
    tail = head = new NODE(0);
    size = 0;
    ptrNODE p = other.head;
    ptrNODE p1 = head;
    while (p->next)
    {
        p1->next = new NODE(new Book(*(p->next->info)));    
        p = p->next;
        p1 = p1->next;
        ++size;
    }
    tail = p1->next;
}

FLIST::FLIST(FLIST&& tmp)
{
    std::cout << "Constructor move\n";
    tail = tmp.tail;
    head = tmp.head;
    size = tmp.size;
    tmp.tail = nullptr;
    tmp.head = nullptr;
}

FLIST& FLIST::operator=(const FLIST& other)
{
    std::cout << "Copy operator\n";
    if (this != &other) {
        clear(head, tail);
        tail = head = new NODE(0);
        size = 0;
        ptrNODE p = other.head;
        ptrNODE p1 = head;
        while (p->next) {
            p1->next = new NODE(new Book(*(p->next->info)));
            p = p->next;
            p1 = p1->next;
            ++size;
        }
        tail = p1->next;
    }
    return *this;
}

FLIST& FLIST::operator=(FLIST&& tmp)
{
    std::cout << "Move operator\n";
    if (this != &tmp) {
        clear(head, tail);
        tail = tmp.tail;
        head = tmp.head;
        size = tmp.size;
        tmp.tail = nullptr;
        tmp.head = nullptr;
    }
    return *this;
}

void FLIST::copy(ptrNODE& beg, ptrNODE end)
{
    while (beg != end)
    {
        add_to_tail(beg->info);
        beg = beg->next;
    }
}

FLIST::~FLIST()
{
    while (head && !empty())
    {
        del_from_head();
    }
    delete head;
    head = tail = nullptr;
}

void FLIST::add_to_head(ptrBook elem)
{
    adding_by_pointer(head->next, elem);
    if (head == tail)
        tail = tail->next;
}

void FLIST::add_to_tail(ptrBook elem)
{
    adding_by_pointer(tail->next, elem);
    tail = tail->next;
}

void FLIST::add_after(ptrNODE ptr, ptrBook elem)
{
    if (ptr)
    {
        adding_by_pointer(ptr->next, elem);
        if (ptr == tail)
            tail = tail->next;
    }
}

void FLIST::del_from_head()
{
    if (head->next)
    {
        deleting_by_pointer(head->next);
        if (!head->next)
            tail = head;
    }
}

void FLIST::del_after(ptrNODE ptr)
{
    if (ptr && ptr->next)
    {
        if (ptr->next == tail)
            tail = ptr;
        deleting_by_pointer(ptr->next);
    }
}

void FLIST::print(const char* message, std::ostream& stream)
{
    ptrNODE p = head->next;
    while (p)
    {
        (p->info)->print();
        p = p->next;
    }
}

void FLIST::sorting(std::function<int(ptrBook, ptrBook)> compare)
{
    auto switch_pointers = [](ptrNODE q, ptrNODE p)
        {
            ptrNODE tmp = p->next;
            p->next = tmp->next;
            tmp->next = q->next;
            q->next = tmp;
        };
    auto find_place = [this, &compare](ptrBook elem)->ptrNODE
        {
            ptrNODE result = head;
            while (result->next && compare(result->next->info, elem) < 0) // <-- 
                result = result->next;
            return result;
        };
    ptrNODE hprev = head->next, h = head->next->next;
    while (h)
    {
        if (compare(hprev->info, h->info) >= 0) // <-- 
        {
            switch_pointers(find_place(h->info), hprev);
            h = hprev->next;
        }
        else
        {
            hprev = h;
            h = h->next;
        }
        tail = hprev;
    }
}

void FLIST::clear(ptrNODE& begin, ptrNODE& end)
{
    while (begin != end)
        del_after(begin);
    begin = end;
}

void FLIST::clear()
{
    while (head->next)
        del_after(head);
}
