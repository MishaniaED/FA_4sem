#pragma once

template <typename T>
class	StrategyComparator
{
public:
	virtual ~StrategyComparator() {}
	virtual int compare(const T& obj1, const T& obj2) const = 0;
};

class Comparator_int : public StrategyComparator<int>
{
	int compare(int const& obj1, int const& obj2) const override
	{
		if (obj1 > obj2)
			return (1);
		else if (obj1 < obj2)
			return (-1);
		return (0);
	}
};

class Comparator_ptr_int : public StrategyComparator<int*>
{
	int compare(int* const& obj1, int* const& obj2) const override
	{
		if (*obj1 > *obj2)
			return (1);
		else if (*obj1 < *obj2)
			return (-1);
		return (0);
	}
};

// Шаблон бинарного дерева 

template <typename T>
class	Binary_tree
{
protected:
	StrategyComparator<T>* comparator;

public:
	Binary_tree(StrategyComparator<T>* compare = nullptr) : comparator(compare) {}
	virtual ~Binary_tree() {}

	virtual bool find_node(T&& val) = 0;
	virtual void add_node(T&& val) = 0;
	virtual void delete_node(T&& val) = 0;
};
