#include "DLIST.h"

DLIST::DLIST(const char* file_name)
{
    std::ifstream data_file(file_name);
    ptrFile file = new File(data_file);
    first_node(file);
    while (!data_file.eof())
    {
        file = new File(data_file);
        insert_after(tail, file);
    }
    data_file.close();
}

DLIST::DLIST(const char* file_name, std::function<int(File, File)> compare)
{
    std::ifstream data_file(file_name);
	ptrFile file = new File(data_file);
    first_node(file);

    auto find_place = [this, compare](ptrFile file)->ptrDNODE
        {
            ptrDNODE p = head;
            while (p && compare(*(p->info), *file) < 0)
                p = p->next;
            return p;
        };
    ptrDNODE place{};
    while (!data_file.eof())
    {
        file = new File(data_file);
        place = find_place(file);
        if (place)
            insert_before(place, file);
        else
            insert_after(tail, file);
    }
    data_file.close();
}

DLIST::~DLIST()
{
    while (!empty())
        remove(head);
}

void DLIST::first_node(ptrFile file)
{
    head = new DNODE(file);
    tail = head;
}

void DLIST::print(std::ostream& stream)
{
    ptrDNODE p = head;
    while (p)
    {
        (p->info)->print(stream);
        p = p->next;
    }
}

void DLIST::insert_after(ptrDNODE ptr, ptrFile elem)
{
    ptrDNODE ptr1 = new DNODE(elem, ptr->next, ptr);
    if (ptr == tail)
        tail = ptr1;
    else
        ptr->next->prev = ptr1;
    ptr->next = ptr1;
}

void DLIST::insert_before(ptrDNODE ptr, ptrFile elem)
{
    ptrDNODE p = new DNODE(elem, ptr, ptr->prev);
    if (ptr == head)
        head = p;
    else
        ptr->prev->next = p;
    ptr->prev = p;
}

bool DLIST::empty()
{
    return head == nullptr;
}

void DLIST::remove(ptrDNODE& ptr)
{
    ptrDNODE p = ptr;
    if (ptr == head)
    {
        head = p->next;
        ptr = head;
        if (p->next)
            p->next->prev = nullptr;
    }
    else
        if (ptr == tail)
        {
            tail = p->prev;
            ptr = tail;
            if (p->prev)
                p->prev->next = nullptr;

        }
        else
        {
            ptr = ptr->next;
            p->next->prev = p->prev;
            p->prev->next = p->next;
        }
    delete p;
}
