#pragma once

#include <iostream>
#include <list>

template <typename T>
class	List
{
	struct Node
	{
		T		ticket;
		Node*	prev;
		Node*	next;

		Node(T value)
		{
			this->ticket = value;
			this->prev = nullptr;
			this->next = nullptr;
		}

		~Node() {}
	};

private:
	Node*		Head;
	Node*		Tail;
	unsigned int	lst_size;

	Node* create_new_node(const T& value);

public:
	class	iterator
	{
	private:
		Node* node_ptr;

	public:
		iterator()
		{
			node_ptr = nullptr;
		}
		iterator(Node* ptr) 
		{
			node_ptr = ptr;
		}
		~iterator() {}

		bool operator==(const iterator& rhs) const
		{
			return (this->node_ptr == rhs.node_ptr);
		}
		bool operator!=(const iterator& rhs) const
		{
			return (this->node_ptr != rhs.node_ptr);
		}
		T& operator*()
		{
			return (node_ptr->ticket);
		}
		iterator& operator++()
		{
			this->node_ptr = this->node_ptr->next;
			return (*this);
		}
		iterator& operator--()
		{
			this->node_ptr = this->node_ptr->prev;
			return (*this);
		}
		iterator operator++(int)
		{
			iterator copy = *this;
			this->node_ptr = this->node_ptr->next;
			return copy;
		}
		iterator operator--(int)
		{
			iterator copy = *this;
			this->node_ptr = this->node_ptr->prev;
			return copy;
		}
		iterator& operator=(const iterator& rhs)
		{
			this->node_ptr = rhs.node_ptr;
			return (*this);
		}
	};

	List()
	{
		Head = nullptr;
		Tail = nullptr;
		lst_size = 0;
	}
	~List()
	{
		clear();
	}

	unsigned int	size() const;
	bool			empty() const;
	T&				front();
	T&				back();
	iterator		end() const;
	iterator		begin() const;
	iterator		find(const T& value);
	void			clear();
	void			push_back(const T& value);
	void			push_front(const T& value);
	void			pop_back();
	void			pop_front();
};

template <typename T>
typename List<T>::iterator	List<T>::begin() const
{
	return iterator(Head);
}

template <typename T>
typename List<T>::iterator	List<T>::end() const
{
	return iterator(Tail->next);
}

template <typename T>
T& List<T>::front()
{
	return (Head->ticket);
}

template <typename T>
T& List<T>::back()
{
	return (Tail->ticket);
}

template <typename T>
typename List<T>::Node* List<T>::create_new_node(const T& value)
{
	Node* new_node = nullptr;

	new_node = new Node(value);
	if (!new_node)
		return nullptr;
	return new_node;
}

template <typename T>
unsigned int List<T>::size() const
{
	return lst_size;
}

template <typename T>
bool	List<T>::empty() const
{
	return (lst_size == 0);
}

template <typename T>
void	List<T>::clear()
{
	Node* temp_ptr;

		while (Head != nullptr)
		{
			temp_ptr = Head;
			Head = Head->next;
			delete temp_ptr;
		}
		if(Head != nullptr)
		Head = nullptr;
		Tail = nullptr;
		lst_size = 0;
}

template <typename T>
void	List<T>::push_front(const T& value)
{
	Node* new_node;

	new_node = create_new_node(value);
	if (new_node != nullptr)
	{
		if (!Head)
			Tail = new_node;
		else
		{
			new_node->next = Head;
			Head->prev = new_node;
		}
		Head = new_node;
		lst_size++;
	}
}

template <typename T>
void	List<T>::push_back(const T& value)
{
	Node* new_node = nullptr;

	new_node = create_new_node(value);
	if (new_node != nullptr)
	{
		if (!Head)
			Head = new_node;
		else
		{
			new_node->prev = Tail;
			Tail->next = new_node;
		}
		Tail = new_node;
		lst_size++;
	}
}

template <typename T>
void	List<T>::pop_back()
{
	Node* prev_ptr;
	Node* temp_ptr;

	if (!Head)
		return;
	else if (Head && !Head->next)
	{
		lst_size--;
		delete Head;
		Head = nullptr;
		Tail = nullptr;
		return;
	}
	prev_ptr = Tail->prev;
	prev_ptr->next = nullptr;
	temp_ptr = Tail;
	Tail = prev_ptr;
	lst_size--;
	delete temp_ptr;
}

template <typename T>
void	List<T>::pop_front()
{
	Node* next_ptr;
	Node* tmp_ptr;

	if (Head && !Head->next)
	{
		Head = nullptr;
		Tail = nullptr;
		lst_size--;
		delete Head;
		return;
	}

	next_ptr = Head->next;
	next_ptr->prev = nullptr;
	tmp_ptr = Head;
	Head = next_ptr;
	lst_size--;
	delete tmp_ptr;
}

template <typename T>
typename List<T>::iterator	List<T>::find(const T& value)
{
	List<T>::iterator	iter;

	iter = begin();
	while (iter != end())
	{
		if (*iter == value)
			return (iter);
		iter++;
	}
	return end();
}
