#include <iostream>
#include <fstream>

using TInfo = int;

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
	void add(int elem);
	void clear();
	void print(int level);
};

using ptrNODE = NODE*;

ptrNODE Build_Balance(int count, std::ifstream& file)
{
	ptrNODE result{};
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		result = new NODE();
		file >> result->info;
		result->left = Build_Balance(count_left, file);
		result->right = Build_Balance(count_right, file);
	}
	return result;
}

struct BinTree
{
	ptrNODE root;
	BinTree();
	BinTree(int count, std::ifstream& file); // balanced
	BinTree(std::ifstream& file);			 // search
	~BinTree();
	void clear();
	void print();
};


// tasks

// find a sum of odd numbers on the current level (all after user_level)

int sum_odd_rec(const ptrNODE& root, int level)
{
	int result{};
	if (root && level >= 0)
		result = (root->info % 2 != 0 ? root->info : 0) + sum_odd_rec(root->right, level - 1) + sum_odd_rec(root->left, level - 1);
	return result;
}

// find a count of even numbers (all before user_level, cur_level = 0)

int count_even_rec2(const ptrNODE& root, int user_level, int cur_level)
{
	int result = 0;
	if (root)
	{
		result = (cur_level >= user_level && root->info % 2 == 0 ? 1 : 0) + count_even_rec2(root->left, user_level, cur_level + 1) + count_even_rec2(root->right, user_level, cur_level + 1);
	}
	return result;
}

// find a count of maximas (all after user_level)

void count_max_rec(const ptrNODE& root, int user_level, TInfo& max, int& count)
{
	if (root && user_level >= 0)
	{
		if (user_level == 0)
		{
			if (count == 0 || root->info > max)
			{
				max = root->info;
				count = 1;
			}
			else if (root->info == max)
				++count;
		}
		count_max_rec(root->left, user_level - 1, max, count);
		count_max_rec(root->right, user_level - 1, max, count);
	}
}

// find a level of max element

void max_elem_level(const ptrNODE& root, int level, int& max_level, int& max_elem)
{
	if (root)
	{
		if (root->info > max_elem)
		{
			max_elem = root->info;
			max_level = level;
		}
		else if (root->info == max_elem && level > max_level)
			max_level = level;
		max_elem_level(root->left, level + 1, max_level, max_elem);
		max_elem_level(root->right, level + 1, max_level, max_elem);
	}
}



int main()
{
	std::ifstream file("data.txt");
	if (!file)
		std::cout << "File Error!\n";
	else
	{
		/*int count{};
		file >> count;*/
		BinTree tree(file);
		tree.print();
		int max{}, count{};
		count_max_rec(tree.root, 0, count, max);
		std::cout << max << ' ' << count;
	}
}



void NODE::add(int elem)
{
	if (elem == info)
		return;
	if (elem > info)
	{
		if (left == nullptr)
			left = new NODE(elem);
		else
			left->add(elem);
	}
	else
	{
		if (right == nullptr)
			right = new NODE(elem);
		else
			right->add(elem);
	}
}

void NODE::clear()
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

void NODE::print(int level)
{
	if (left)
		left->print(level + 1);
	for (int i{}; i < level; ++i)
		std::cout << "   ";
	std::cout << info << '\n';
	if (right)
		right->print(level + 1);
}



BinTree::BinTree()
{
	root = nullptr;
}

BinTree::BinTree(int count, std::ifstream& file) // balanced
{
	root = Build_Balance(count, file);
}

BinTree::BinTree(std::ifstream& file) // search
{
	TInfo elem{};
	root = nullptr;
	while (file >> elem)
		if (!root) 
			root = new NODE(elem);
		else 
			root->add(elem);

}

BinTree::~BinTree()
{
	clear();
}

void BinTree::clear()
{
	if (root)
	{
		root->clear();
		root = nullptr;
	}
}

void BinTree::print()
{
	if (!root) std::cout << "Tree is empty!\n";
	else root->print(0);
}