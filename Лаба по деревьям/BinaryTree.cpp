#include "BinaryTree.h"


void BinaryTree::print(Tree t, int level)
{
	if (t)
	{
		print(t->right, level + 1);
		for (int i = 0; i < level; ++i)
			std::cout << "   ";
		std::cout << t->info << '\n';
		print(t->left, level + 1);
	}
}

void BinaryTree::clear(Tree& t)
{
	if (t)
	{
		clear(t->left);
		clear(t->right);
		delete t;
		t = nullptr;
	}
}

Tree BinaryTree::BuildBalance(int count, std::ifstream& file)
{
	Tree result = nullptr;
	if (count)
	{
		int cnt_left = count / 2;
		int cnt_right = count - cnt_left - 1;
		int x;
		file >> x;
		result = new NODE(x);
		result->left = BuildBalance(cnt_left, file);
		result->right = BuildBalance(cnt_right, file);
	}
	return result;
}
