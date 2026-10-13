#include <queue>
#include "FTree.h"

Tree copy(const Tree& root)
{
	Tree result = nullptr;
	if (root)
	{
		result = new NODE(root->info);
		result->left = copy(root->left);
		result->right = copy(root->right);
	}
	return result;
}

void change(Tree root)
{
	if (root->info == '*')
	{
		if (root->left->info == '+' || root->left->info == '-') // если имеем + или - слева, то надо менять
		{
			Tree tmp = new NODE('*', root->left->right, nullptr);
			tmp->right = copy(root->right);
			root->left->right = nullptr;
			root->info = root->left->info;
			root->left->info = '*';
			root->left->right = root->right;
			root->right = tmp;
		}
		if (root->right->info == '+' || root->right->info == '-') // зеркальный случай
		{
			Tree tmp = new NODE('*', nullptr, root->right->left);
			tmp->left = copy(root->left);
			root->right->left = nullptr;
			root->info = root->right->info;
			root->right->info = '*';
			root->right->left = root->left;
			root->left = tmp;
		}
	}
}

void task(Tree root)
{
	Tree t = root;
	std::queue <Tree> Que;
	Que.push(root);
	while (!Que.empty())
	{
		t = Que.front();
		Que.pop();
		change(t);
		if (t->left != nullptr && (t->left->info == '*' || t->left->info == '+' || t->left->info == '-'))
			Que.push(t->left);
		if (t->right != nullptr && (t->right->info == '*' || t->right->info == '+' || t->right->info == '-'))
			Que.push(t->right);
	}
}

int main()
{
    std::ifstream file("data.txt");
    FTree formula(file);
    formula.print();
	task(formula.get_root());
	formula.print();
}
