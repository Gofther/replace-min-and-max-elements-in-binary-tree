#pragma once
#include <fstream>
#include <iostream>

using TInfo = int;

struct NODE
{
	TInfo info;
	NODE* left, * right;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) :info(info), left(left), right(right)
	{}
	~NODE()
	{
		left = right = nullptr;
	}
};

using Tree = NODE*;

struct BinaryTree
{
private:
	Tree root;
public:
	BinaryTree(std::ifstream& file) {
		int count;
		file >> count;
		root = BuildBalance(count, file);
	}
	~BinaryTree() {
		clear(root);
	}
	Tree get_root() 
	{
		return root;
	}
	Tree BuildBalance(int count, std::ifstream& file);
	void print(Tree t, int level);
	void clear(Tree& t);
};


