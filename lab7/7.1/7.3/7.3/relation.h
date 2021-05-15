#pragma once

#include <algorithm>
#include <forward_list>
#include "avl_tree.h"
#include "red_black_tree.h"

template <typename T>
class Relation
{
private:
	forward_list<T*>				data;
	forward_list<Binary_tree<T*>*>	indexed_tree;
	
public:
	Relation() {}
	~Relation() {}
	
	bool search_data(T &val);
	void insert_data(T &val);
	void remove_data(T &val);
	void insert_index(Binary_tree<T*>* node_ptr);
	void remove_index(Binary_tree<T*>* node_ptr);
};

template <typename T>
bool Relation<T>::search_data(T &val)
{
	for (auto it = indexed_tree.begin(); it != indexed_tree.end(); it++)
		if ((*it)->find_node(&val))
			return true;
		
	return false;
}

template <typename T>
void Relation<T>::insert_data(T &val)
{
	data.push_front(&val);
	for (auto it = indexed_tree.begin(); it != indexed_tree.end(); it++)
		(*it)->add_node(&val);
}

template <typename T>
void Relation<T>::remove_data(T &val)
{
	data.remove(&val);
	for (auto it = indexed_tree.begin(); it != indexed_tree.end(); it++)
		(*it)->delete_node(&val);
}

template <typename T>
void Relation<T>::insert_index(Binary_tree<T*>* node_ptr)
{
	for (auto it = data.begin(); it != data.end(); it++)
		node_ptr->add_node(&**it);
	indexed_tree.push_front(node_ptr);
}

template <typename T>
void Relation<T>::remove_index(Binary_tree<T*>* node_ptr)
{
	indexed_tree.remove(node_ptr);
}
