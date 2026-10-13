#pragma once

using TInfo = int;

struct NODE
{
    TInfo info;
    NODE* next;
    NODE(TInfo info, NODE* ptr = nullptr) : info(info), next(ptr) {}
    ~NODE() { next = nullptr; } // 0
};