#include "FLIST.h"

FLIST::~FLIST()
{
    while (!empty())
    {
        del_from_head();
    }
    delete head;
    head = tail = nullptr;
}

void FLIST::add_to_head(TInfo elem)
{
    adding_by_pointer(head->next, elem);
    if (head == tail) // если пустой список
        tail = tail->next;
}

void FLIST::add_to_tail(TInfo elem)
{
    adding_by_pointer(tail->next, elem);
    tail = tail->next;
}

void FLIST::add_after(ptrNODE ptr, TInfo elem)
{
    if (ptr) // если указатель когерентен
    {
        adding_by_pointer(ptr->next, elem);
        if (ptr == tail)
            tail = tail->next;
    }
}

void FLIST::del_from_head()
{
    if (head->next) // если список пустой
    {
        deleting_by_pointer(head->next);
        if (!head->next) // если список стал пустым
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

void FLIST::create_by_queue(std::ifstream& file)
{
    TInfo elem;
    while (file >> elem)
        add_to_tail(elem);
}

void FLIST::print(const char* message, std::ostream& stream)
{
    stream << message << '\n';
    ptrNODE ptr = head->next; // первый фактический элемент
    while (ptr)
    {
        stream << ptr->info << ' ';
        ptr = ptr->next;
    }
    stream << '\n';
}

void FLIST::sotring()
{
    auto switch_pointers = [](ptrNODE q, ptrNODE p)
        {
            ptrNODE tmp = p->next;
            p->next = tmp->next;
            tmp->next = q->next;
            q->next = tmp;
        };
    auto find_place = [this](TInfo elem)->ptrNODE
        {
            ptrNODE result = head;
            while (result->next && result->next->info < elem)
                result = result->next;
            return result;
        };
    ptrNODE hprev = head->next, h = head->next->next;
    while (h)
    {
        if (hprev->info > h->info)
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

void FLIST::clear_fragment(ptrNODE begin, ptrNODE end)
{
    if (!end)
    {
        ptrNODE ptr = head;
        while (ptr->next != begin)
            ptr = ptr->next;
        tail = ptr;
    }
    while (begin != end)
        deleting_by_pointer(begin);
}

void FLIST::del_from_tail()
{
    ptrNODE ptr = head;
    while (ptr)
    {
        if (ptr->next == tail)
            del_after(ptr);
        ptr = ptr->next;
    }
}

ptrNODE FLIST::find_if(ptrNODE begin, ptrNODE end, std::function<bool(TInfo)> condition)
{
    ptrNODE ptr = begin;
    ptrNODE resultptr = nullptr;
    while (ptr->next != end && !resultptr)
    {
        if (condition(ptr->info))
            resultptr = ptr;
        ptr = ptr->next;
    }
    return resultptr;
}