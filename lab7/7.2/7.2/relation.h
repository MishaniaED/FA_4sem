#pragma once

#include <forward_list>
#include <algorithm>
#include "red-black_tree.h"
#include "avl_tree.h"
using namespace std;

template <typename T>
class Relation
{
private:
	forward_list<T*> data;
	forward_list<Binary_tree<T*>*> indexed_tree;

public:
	Relation() {}
	~Relation() {}

	void print_data();
	bool find_data(T &val);
	void add_data(T &val);
	void delete_data(T &val);
	void add_index(Binary_tree<T*>* ptr_node);
	void delete_index(Binary_tree<T*>* ptr_node);
};

template <typename T>
void Relation<T>::print_data()
{
	for (auto obj : data)
		cout << *obj << " ";
	cout << endl;
}

template <typename T>
bool Relation<T>::find_data(T &val)
{
	for (auto it = indexed_tree.begin(); it != indexed_tree.end(); it++)
		if ((*it)->find_node(&val))
			return true;
	return false;
}

template <typename T>
void Relation<T>::add_data(T &val)
{
	data.push_front(&val);
	for (auto it = indexed_tree.begin(); it != indexed_tree.end(); it++)
		(*it)->add_node(&val);
}

template <typename T>
void Relation<T>::delete_data(T &val)
{
	data.remove(&val);
	for (auto it = indexed_tree.begin(); it != indexed_tree.end(); it++)
		(*it)->delete_node(&val);
}

template <typename T>
void Relation<T>::add_index(Binary_tree<T*>* ptr_node)
{
	for (auto it = data.begin(); it != data.end(); it++)
		ptr_node->add_node(&**it);
	indexed_tree.push_front(ptr_node);
}

template <typename T>
void Relation<T>::delete_index(Binary_tree<T*>* ptr_node)
{
	indexed_tree.remove(ptr_node);
}
