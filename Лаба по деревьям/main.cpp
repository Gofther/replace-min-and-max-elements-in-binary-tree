#include <iostream>
#include "BinaryTree.h"
#include <fstream>

void task(BinaryTree& tree);
Tree find_max(Tree& root, Tree& Max);
Tree find_min(Tree& root, Tree& Min);
void Switch (Tree & root, Tree & Max, Tree & Min, BinaryTree& t);
Tree find_father(Tree& root, Tree& son);
Tree Switch_place(Tree& root, Tree& left_min, Tree& right_min, Tree& father_min, Tree& left_max, Tree& right_max, Tree& father_max, Tree& Max, Tree& Min, bool is_fatherMax_left, bool is_fatherMin_left);

int main()
{
	std::ifstream file ("data.txt");
	setlocale(LC_ALL, "rus");
	BinaryTree tree (file);
	tree.print(tree.get_root(), 1);
	task(tree);
	return 0;
}

void task(BinaryTree& tree)
{
	Tree root = tree.get_root();
	Tree Max, Min;
	Max = find_max(root,root);
	root = tree.get_root();
	Min = find_min(root, root);
	Switch (root, Max, Min, tree);

}
Tree find_max (Tree& root,Tree& Max)
{
	if (root)
	{
		if (root->info > Max->info)
		{
			Max = root;
		}
		find_max(root->right,Max);
		find_max(root->left,Max);
	}
	return Max;
};
Tree find_min(Tree& root, Tree& Min)
{
	if (root)
	{
		if (root->info < Min->info)
		{
			Min = root;
		}
		find_min(root->right, Min);
		find_min(root->left, Min);
	}
	return Min;
};
void Switch(Tree& root, Tree& Max, Tree& Min, BinaryTree& t)
{
	Tree left_min=nullptr, right_min = nullptr,father_min=nullptr, left_max = nullptr, right_max = nullptr, father_max=nullptr;
	bool is_fatherMax_left=false, is_fatherMin_left=false;
	if (Max == root || Min == root) // Проверяем не корень ли дерева мин или мах
	{
		if (Max == root)
		{
			left_max = Max->left;
			right_max = Max->right;
		}
		else {
			father_max = find_father(root, Max); //если нет, то ищем их предшественника
			if (father_max->left == Max)
			{
				left_max = Max->left;
				right_max = Max->right;
				is_fatherMax_left = true;
			}
			if (father_max->right == Max)
			{
				left_max = Max->left;
				right_max = Max->right;
				is_fatherMax_left = false;
			}
		}
		if (Min == root)
		{
			left_min = Min->left;
			right_min = Min->right;
		}
		else {
			father_min = find_father(root, Min);

			if (father_min->left == Min)
			{
				left_min = Min->left;
				right_min = Min->right;
				is_fatherMin_left = true;
			}
			if (father_min->right == Min)
			{
				left_min = Min->left;
				right_min = Min->right;
				is_fatherMin_left = false;
			}
		}
	}
	root = t.get_root();
	root= Switch_place(root, left_min, right_min, father_min, left_max, right_max, father_max, Max, Min, is_fatherMax_left, is_fatherMin_left);
	t.print(root, 1);
}
Tree find_father(Tree& root,Tree& son)
{
	if (root)
	{
		if (root->left == son || root->right == son)
		{
			return root;
		}
		else
		{
			find_father(root->left, son);
			find_father(root->right, son);

		}
	}
}
bool flag_min = true, flag_max = true; // изменяем в функции, чтобы макс и мин элементы не обрабатывались дважды
Tree Switch_place(Tree& root, Tree& left_min, Tree& right_min, Tree& father_min, Tree& left_max, Tree& right_max, Tree& father_max, Tree& Max, Tree& Min, bool is_fatherMax_left, bool is_fatherMin_left)
{
	if (root)
	{

			if ((root== father_min && flag_min) || (root == father_max && flag_max))
			{
				if (root == father_min)
				{
					if (is_fatherMin_left)
					{
						root->left = Max;
						root->left->left = left_min;
						root->left->right = right_min;
						flag_min = false;
					}
					else
					{
						root->right = Max;
						root->right->left = left_min;
						root->right->right = right_min;
						flag_min = false;
					}
				}
				if (root == father_max)
				{
					if (is_fatherMax_left)
					{
						root->left = Min;
						root->left->left = left_max;
						root->left->right = right_max;
						flag_max = false;
					}
					else
					{
						root->right = Min;
						root->right->left = left_max;
						root->right->right = right_max;
						flag_max = false;
					}
				}
			}
			else if ((root == Min && father_min==nullptr && flag_min) || (root == Max && father_max==nullptr && flag_max))
			{
				if (root == Min)
				{
					root = Max;
					root->left = left_min;
					root->right = right_min;
					flag_min = false;
				}
				else /*(root == Max)*/
				{
					root = Min;
					root->left = left_max;
					root->right = right_max;
					flag_max = false;
				}
			}
			Switch_place(root->left, left_min, right_min, father_min, left_max, right_max, father_max, Max, Min, is_fatherMax_left, is_fatherMin_left);
			Switch_place(root->right, left_min, right_min, father_min, left_max, right_max, father_max, Max, Min, is_fatherMax_left, is_fatherMin_left);
	}
	return root;
};