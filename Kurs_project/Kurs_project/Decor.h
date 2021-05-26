#pragma once
#include "dс_list.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#define max_gain 50000000

template <template <typename T, class allocator = std::allocator<T>>
class Container, typename T>
	class Interface
{
private:
	Container<T>* decor_container;
public:
	Interface(Container<T>* container) 
	{
		decor_container = container;
	}
	~Interface() {}

	unsigned int	size() const
	{
		return (this->decor_container->size());
	}

	bool	empty() const
	{
		return (this->decor_container->empty());
	}

	void	insert_back(const T& value)
	{
		this->decor_container->insert_back(value);
	}

	void	remove_back()
	{
		this->decor_container->remove_back();
	}

	void	clear_memory()
	{
		this->decor_container->clear_memory();
	}

	void	clear()
	{
		this->decor_container->clear();
	}

	void	print(ostream& stream) const
	{
		this->decor_container->print(stream);
	}

	void	find_winners() const
	{
		return (this->decor_container->find_winners());
	}

	void	search_by_id(const unsigned int& id) const
	{
		this->decor_container->search_by_id(id);
	}

	void	search_by_gain(const unsigned int& g) const
	{
		this->decor_container->search_by_gain(g);
	}
};

template <typename T, class allocator = std::allocator<T>>
class	Vector_interface
{
private:
	vector<T>	vec;
public:


	unsigned int	size() const
	{
		return vec.size();
	}

	bool	empty() const
	{
		return vec.empty();
	}

	void	insert_back(const T& value)
	{
		vec.push_back(value);
	}

	void	remove_back()
	{
		vec.pop_back();
	}

	void	clear_memory()
	{
		typename vector<T>::iterator	iter;

		iter = vec.begin();
		while (iter != vec.end())
		{
			delete(*iter);
			++iter;
		}
	}

	void	clear()
	{
		if (vec.empty())
			return;
		this->vec.clear();
	}

	void	print(ostream& stream) const
	{
		typename vector<T>::const_iterator	iter;

		iter = vec.begin();
		while (iter != vec.end())
		{
			(*iter)->print_ticket(stream);
			++iter;
		}
	}

	void	search_by_id(const unsigned int& id) const // додумать
	{
		typename vector<T>::const_iterator	iter;
		bool	flag = false;

		iter = vec.begin();
		++iter;
		while (iter != vec.end())
		{
			if ((*iter)->get_id() == id)
			{
				(*iter)->print_ticket(std::cout);
				flag = true;
				break;
			}
			++iter;
		}
		if (!flag)
			cout << "\nNo tickets found for the specified \"No.\"\n";
	}

	void	search_by_gain(const unsigned int& g) const // додумать
	{
		typename vector<T>::const_iterator	iter;
		bool		flag = false;

		iter = vec.begin();
		++iter;
		while (iter != vec.end())
		{
			if ((*iter)->get_gain() == g)
			{
				(*iter)->print_ticket(std::cout);
				flag = true;
			}
			++iter;
		}
		if (!flag)
			cout << "\nNo tickets found for the specified prize\n";
	}

	void	find_winners() const
	{
		typename vector<T>::const_iterator	iter;
		bool	flag = false;

		iter = vec.begin();
		++iter;
		while (iter != vec.end())
		{
			if ((*iter)->get_gain() == max_gain)
			{
				cout << "\n";
				(*iter)->print_ticket(std::cout);
				cout << "\n";
				flag = true;
			}
			++iter;
		}
		if (!flag)
			cout << "\nNo winners\n";
	}
};


template <typename T, class allocator = std::allocator<T>>
class	List_interface
{
private:
	List<T>	lst;

public:

	unsigned int	size() const
	{
		return lst.size();
	}

	bool	empty() const
	{
		return (lst.empty());
	}

	void	insert_back(const T& value)
	{
		lst.push_back(value);
	}

	void	remove_back()
	{
		lst.pop_back();
	}

	void	clear_memory()
	{
		typename List<T>::iterator	iter;

		if (lst.empty())
			return;
		iter = lst.begin();
		while (iter != lst.end())
		{
			delete(*iter);
			++iter;
		}
	}

	void	clear()
	{
		if (lst.empty())
			return;
		this->lst.clear();
	}

	void	print(ostream& stream) const
	{
		typename List<T>::iterator	iter;

		iter = lst.begin();
		while (iter != lst.end())
		{
			(*iter)->print_ticket(stream);
			++iter;
		}
	}

	void	search_by_id(const unsigned int& id) const // додумать
	{
		typename List<T>::iterator	iter;
		bool	flag = false;

		iter = lst.begin();
		++iter;
		while (iter != lst.end())
		{
			if ((*iter)->get_id() == id)
			{
				(*iter)->print_ticket(std::cout);
				flag = true;
				break;
			}
			++iter;
		}
		if (!flag)
			cout << "\nNo tickets found for the specified \"No.\"\n";
	}

	void	search_by_gain(const unsigned int& g) const // додумать
	{
		typename List<T>::iterator	iter;
		bool	flag = false;

		iter = lst.begin();
		++iter;
		while (iter != lst.end())
		{
			if ((*iter)->get_gain() == g)
			{
				(*iter)->print_ticket(std::cout);
				flag = true;
			}
			++iter;
		}
		if (!flag)
			cout << "\nNo tickets found for the specified gain\n";
	}

	void	find_winners() const
	{
		typename List<T>::iterator	iter;
		bool	flag = false;

		iter = lst.begin();
		++iter;
		while (iter != lst.end())
		{
			if ((*iter)->get_gain() == max_gain)
			{
				cout << "\n";
				(*iter)->print_ticket(std::cout);
				cout << "\n";
				flag = true;
			}
			++iter;
		}
		if (!flag)
			cout << "\nNo winners\n";
	}
};