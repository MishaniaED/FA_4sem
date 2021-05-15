#pragma once

template <typename T>
class	StratagyComparator
{
public:
	virtual ~StratagyComparator() {}
	virtual int compare(const T &obj1, const T &obj2) const = 0;
};

/* datetime */

class Comparator_datetime : public StratagyComparator<message_info*>
{
	int compare(message_info* const &obj1, message_info* const &obj2) const override
	{
		int	obj1_date = (*obj1).date.year * 1000 + (*obj1).date.month * 100 + (*obj1).date.day;
		int	obj2_date = (*obj2).date.year * 1000 + (*obj2).date.month * 100 + (*obj2).date.day;
		int	obj1_time = (*obj1).date.hour * 3600 + (*obj1).date.month * 60 + (*obj1).date.sec;
		int	obj2_time = (*obj2).date.hour * 3600 + (*obj2).date.month * 60 + (*obj2).date.sec;

		if (obj1_date + obj1_time > obj2_date + obj2_time)
			return 1;
		if (obj1_date + obj1_time < obj2_date + obj2_time)
			return -1;
		return 0;
	}
};

/* username */

class Comparator_username : public StratagyComparator<message_info*>
{
	int compare(message_info* const &obj1, message_info* const &obj2) const override
	{
		if ((*obj1).username > (*obj2).username)
			return 1;
		else if ((*obj1).username < (*obj2).username)
			return -1;
		return 0;
	}
};

/* message */

class Comparator_message : public StratagyComparator<message_info*>
{
	int compare(message_info* const& obj1, message_info* const& obj2) const override 
	{
		string	obj1_message_copy = (*obj1).message;
		string	obj2_message_copy = (*obj2).message;

		transform(obj1_message_copy.begin(), obj1_message_copy.end(),
			obj1_message_copy.begin(), ::toupper);
		transform(obj2_message_copy.begin(), obj2_message_copy.end(),
			obj2_message_copy.begin(), ::toupper);

		if (obj1_message_copy > obj2_message_copy)
			return 1;
		else if (obj1_message_copy < obj2_message_copy)
			return -1;
		return 0;
	}
};

/* first - datetime, second - username */

class Comparator_datetime_username : public StratagyComparator<message_info*>
{
	int compare(message_info* const& obj1, message_info* const& obj2) const override {
		int	obj1_date = (*obj1).date.year * 1000 + (*obj1).date.month * 100 + (*obj1).date.day;
		int	obj1_time = (*obj1).date.hour * 3600 + (*obj1).date.month * 60 + (*obj1).date.sec;
		int	obj2_date = (*obj2).date.year * 1000 + (*obj2).date.month * 100 + (*obj2).date.day;
		int	obj2_time = (*obj2).date.hour * 3600 + (*obj2).date.month * 60 + (*obj2).date.sec;

		if (obj1_date + obj1_time > obj2_date + obj2_time)
			return 1;
		if (obj1_date + obj1_time < obj2_date + obj2_time)
			return -1;
		else {
			string	obj1_username_copy = (*obj1).username;
			string	obj2_username_copy = (*obj2).username;

			transform(obj1_username_copy.begin(), obj1_username_copy.end(),
				obj1_username_copy.begin(), ::toupper);
			transform(obj2_username_copy.begin(), obj2_username_copy.end(),
				obj2_username_copy.begin(), ::toupper);

			if (obj1_username_copy > obj2_username_copy)
				return 1;
			else if (obj1_username_copy < obj2_username_copy)
				return -1;
		}
		return 0;
	}
};

template <typename T>
class	Binary_tree
{
protected:
	StratagyComparator<T>* comparator;

public:
	Binary_tree(StratagyComparator<T> *compare = nullptr) : comparator(compare) {}
	virtual ~Binary_tree() {}

	virtual bool find_node(T &&val) = 0;
	virtual void add_node(T &&val) = 0;
	virtual void delete_node(T &&val) = 0;
};
