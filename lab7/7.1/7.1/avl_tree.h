#pragma once

#include <stdlib.h>
#include <math.h>
#include "binary_tree.h"
using namespace std;

template <typename T>
class AVL_tree : public Binary_tree<T>
{
private:
	struct tree_node
	{
		T key;
		int	height;
		tree_node* left;
		tree_node* right;
	};

	tree_node*		root;
	int	rotations;

	int	 height(tree_node* node);
	int  bfactor(tree_node* node);
	bool find_node(tree_node* node, T val);
	void delete_tree(tree_node* node);
	void fix_height(tree_node* node);
	void tree_print(tree_node* curr, int depth);

	tree_node* create_tree(T val);
	tree_node* balance(tree_node* node);
	tree_node* find_min(tree_node* node);
	tree_node* rotate_left(tree_node* node);
	tree_node* rotate_right(tree_node* node);
	tree_node* delete_min(tree_node* node);
	tree_node* add_node(tree_node* node, T val);
	tree_node* delete_node(tree_node* node, T val);

public:
	AVL_tree(StrategyComparator<T>* compare) : Binary_tree<T>::Binary_tree(compare)
	{
		root = nullptr;
		rotations = 0;
	}
	~AVL_tree()
	{
		if (root != nullptr)
			delete_tree(this->root);
	}

	bool find_node(T &&val)		override;
	void add_node(T &&val)		override;
	void delete_node(T &&val)	override;
	bool is_empty();
	void print_tree();
	void clear_tree();
	int get_rotations();
};


template <typename T>
bool AVL_tree<T>::find_node(tree_node* node, T val)
{
	if (node != nullptr) {
		if (this->comparator->compare(val, (*node).key) == 0)
			return (true);
		if (this->comparator->compare(val, (*node).key) < 0)
			return find_node(node->left, val);
		else
			return find_node(node->right, val);
	}
	return (false);
}

template <typename T>
int AVL_tree<T>::height(tree_node* node)
{
	if (node == nullptr)
		return (0);
	return node->height;
}

template <typename T>
int	AVL_tree<T>::bfactor(tree_node* node)
{
	return (height(node->right) - height(node->left));
}

template <typename T>
void AVL_tree<T>::fix_height(tree_node* node)
{
	node->height = max(height(node->left), height(node->right)) + 1;
}

template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::create_tree(T val)
{
	tree_node* new_node = new tree_node;

	new_node->key = val;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->height = 0;
	return new_node;
}

template <typename T>
void AVL_tree<T>::tree_print(tree_node* curr, int depth)
{
    int i;
	int loc[1000]{0};

    if (curr == nullptr)
		return ;

    for (i = 0; i < depth; i++) {
        if (i == depth - 1)
			cout << (!loc[depth-1] ? " L " : " | ") << "------";
        else 
			cout << (!loc[i] ? "      " : "  ") << "   ";
	}

	cout << " " << *((*curr).key) << "\n\n";
    loc[depth] = 1;
    tree_print(curr->left, depth+1);
    loc[depth] = 0;
    tree_print(curr->right, depth+1);
}

template <typename T>
void AVL_tree<T>::delete_tree(tree_node* node) 
{
	if (node != nullptr) {
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}

template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::rotate_right(tree_node* x)
{
	tree_node* y;
	
	y = x->left;
	x->left = y->right;
	y->right = x;
	fix_height(x);
	fix_height(y);
	rotations++;
	return (y);
}

template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::rotate_left(tree_node* y)
{
	tree_node* x;
	
	x = y->right;
	y->right = x->left;
	x->left = y;
	fix_height(y);
	fix_height(x);
	rotations++;
	return x;
}

template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::balance(tree_node* node)
{
	fix_height(node);
	if (bfactor(node) == 2) { 
		if (bfactor(node->right) < 0)
			node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	if (bfactor(node) == -2) {
		if (bfactor(node->left) > 0)
			node->left = rotate_left(node->left);
		return rotate_right(node);
	}
	return node;
}

template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::find_min(tree_node* node)
{
	if (node->left != nullptr)
		return (find_min(node->left));
	return node;
}

template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::delete_min(tree_node* node)
{
	if (node->left == nullptr)
		return (node->right);
	node->left = delete_min(node->left);
	return balance(node);
}



template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::add_node(tree_node* node, T val)
{
	if (node == nullptr)
		node = create_tree(val);
	else if (this->comparator->compare(val, (*node).key) < 0) // правило добавления
		node->left = add_node(node->left, val);
	else
		node->right = add_node(node->right, val);
	return balance(node);
}

//в правом поддереве находим узел min с наименьшим ключом и заменяем удаляемый узел на найденный узел min
template <typename T>
typename AVL_tree<T>::tree_node* AVL_tree<T>::delete_node(tree_node* node, T val) 
{
	tree_node* temp;

	if (node == nullptr)
		return nullptr;
	else if (this->comparator->compare(val, node->key) < 0)
		node->left = delete_node(node->left, val);
	else if (this->comparator->compare(val, node->key) > 0)
		node->right = delete_node(node->right, val);
	else if (node->left && node->right) {
		temp = find_min(node->right);
		node->key = temp->key;
		node->right = delete_node(node->right, node->key);
	}
	else {
		temp = node;
		if (node->left == nullptr)
			node = node->right;
		else if (node->right == nullptr)
			node = node->left;
		delete temp;
	}
	if (node == nullptr)
		return (node);
	return balance(node);
}


template <typename T>
bool AVL_tree<T>::find_node(T &&val)
{
	return find_node(root, val);
}

template <typename T>
bool AVL_tree<T>::is_empty()
{
	return (root == nullptr);
}

template <typename T>
void AVL_tree<T>::add_node(T &&val)
{
	root = add_node(root, val);
}

template <typename T>
void AVL_tree<T>::delete_node(T &&val)
{
	if (root->left == nullptr && root->right == nullptr) {
		delete root;
		root = nullptr;
	}
	else
		root == delete_node(root, val);
}

template <typename T>
void AVL_tree<T>::print_tree()
{
	if (root != nullptr)
		tree_print(this->root, 0);
}

template <typename T>
void AVL_tree<T>::clear_tree()
{
	if (root != nullptr)
		delete_tree(root);
	root = nullptr;
	rotations = 0;
}

template <typename T>
int AVL_tree<T>::get_rotations()
{
	return rotations;
}
