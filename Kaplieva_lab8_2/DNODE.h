#pragma once
#include "File.h"

using ptrFile = File*;
struct DNODE
{
    ptrFile info;
    DNODE* next, * prev;
    DNODE() {}
    DNODE(ptrFile info, DNODE* next = nullptr, DNODE* prev = nullptr) :
        info(info), next(next), prev(prev) {}
    ~DNODE() { next = nullptr; prev = nullptr; }
};