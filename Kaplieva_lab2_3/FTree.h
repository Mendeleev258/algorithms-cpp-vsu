#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>

using Tree = NODE*;

struct FTree
{
    Tree root;
    FTree();
    FTree(std::ifstream& file);
    ~FTree();
    void clear();
    Tree get_root();
    std::string to_string();
    void print();
    int calculate();
};