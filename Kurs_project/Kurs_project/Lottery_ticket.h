#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

class Lottery_ticket
{
private:
	unsigned int				size;
	std::vector<unsigned int>	numbers;
	unsigned int				id;
	unsigned int				gain = 0;

public:
	Lottery_ticket(unsigned int&& n = 0)
	{
		size = n;
	}

	~Lottery_ticket()
	{}

	unsigned int	get_gain() const;
	unsigned int	get_id() const;
	unsigned int	get_size() const;
	void			set_size(const unsigned int& value);
	void			set_gain(const unsigned int& value);
	void			set_id(const unsigned int& value);
	void			set_numbers(const unsigned int& value);
	std::ostream&	print_ticket(std::ostream& stream);
	std::vector<unsigned int> get_numbers() const;
};


unsigned int Lottery_ticket::get_gain() const
{
	return gain;
}

unsigned int Lottery_ticket::get_id() const
{
	return id;
}

unsigned int Lottery_ticket::get_size() const
{
	return size;
}

std::vector<unsigned int> Lottery_ticket::get_numbers() const
{
	return numbers;
}

void Lottery_ticket::set_size(const unsigned int& value)
{
	this->size = value;
}


void Lottery_ticket::set_gain(const unsigned int& value)
{
	this->gain = value;
}

void Lottery_ticket::set_id(const unsigned int& value)
{
	this->id = value;
}

void Lottery_ticket::set_numbers(const unsigned int& value)
{
	if (this->numbers.size() == this->size)
		return;
	this->numbers.push_back(value);
}

std::ostream& Lottery_ticket::print_ticket(std::ostream& stream)
{
	stream << "No." << id << " = ";
	for (int i = 0; i < size; i++) {
		stream << " " << numbers[i];
	}
	stream << " gain = " << gain << std::endl;
	return stream;
}
