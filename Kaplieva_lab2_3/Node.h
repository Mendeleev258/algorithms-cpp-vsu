using TInfo = char;

struct NODE
{
    TInfo info;
    NODE* left, * right;
    NODE(TInfo info = 0, NODE* ptr_left = nullptr, NODE* ptr_right = nullptr)
    {
        this->info = info;
        left = ptr_left;
        right = ptr_right;
    }
    ~NODE()
    {
        clear();
    }
    void clear()
    {
        if (left)
        {
            delete left;
            left = nullptr;
        }
        if (right)
        {
            delete right;
            right = nullptr;
        }
    }
};