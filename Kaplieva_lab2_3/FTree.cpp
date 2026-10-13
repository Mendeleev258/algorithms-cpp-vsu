#include "FTree.h"

Tree Build_Formula(std::ifstream& file)
{
    char c = file.get();
    Tree t = new NODE();
    if (c >= '0' && c <= '9')
        t->info = c;
    else
    {
        t->left = Build_Formula(file);
        t->info = file.get();
        t->right = Build_Formula(file);
        c = file.get();
    }
    return t;
}

std::string print_to_string(Tree t)
{
    std::string result{};
    if (!t->left && !t->right)
        result = t->info;
    else
        result = '(' + print_to_string(t->left) + t->info + print_to_string(t->right) + ')';
    return result;
}

int Calculate(const Tree& t)
{
    int result;
    if (!t->left && !t->right)
        result = t->info - '0';
    else
    {
        int leftF{ Calculate(t->left) };
        int rightF{ Calculate(t->right) };
        switch (t->info)
        {
        case '+':
            result = leftF + rightF;
            break;
        case '-':
            result = leftF - rightF;
            break;
        case '*':
            result = leftF * rightF;
            break;
        default:
            break;
        }
    }
    return result;
}



FTree::FTree()
{
    root = nullptr;
}

FTree::FTree(std::ifstream& file)
{
    root = Build_Formula(file);
}

FTree::~FTree()
{
    clear();
}

void FTree::clear()
{
    if (root)
    {
        root->clear();
        root = nullptr;
    }
}

Tree FTree::get_root()
{
    return root;
}

std::string FTree::to_string()
{
    return print_to_string(root);
}

void FTree::print()
{
    std::cout << to_string() << '\n';
}

int FTree::calculate()
{
    return Calculate(root);
}
