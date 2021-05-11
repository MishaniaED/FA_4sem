#include "Polynom.h"
#include <list>
#include <string>
#include <algorithm>

bool Polynom::operator==(const Polynom &poly) const
{
    auto it1 = monomes_list.begin();
    auto it2 = poly.monomes_list.begin();

	for (it1, it2; it1 != monomes_list.end() && it2 != poly.monomes_list.end(); it1++, it2++)
		if ((Imute_monom)(*it1) != (Imute_monom)(*it2))
			return (false);
	return (true);
}

bool Polynom::operator!=(const Polynom &poly) const
{
	if (!(*this == poly))
		return (true);
	return (false);
}

ostream &operator<<(ostream &stream, const Polynom &obj)
{
    if (obj.monomes_list.empty()) {
		stream << 0;
		return (stream);
	}

	list<Imute_monom>::const_iterator it = obj.monomes_list.begin();
	stream << *it;
	++it;
	for (it; it != obj.monomes_list.end(); ++it)
		stream << " + " << *it;

	return (stream);
}

Polynom& Polynom::operator=(const Polynom &obj)
{
    monomes_list.clear();
    for (auto i: obj.monomes_list)
        monomes_list.push_back(i);

    return (*this);
}

Polynom& Polynom::operator=(const char* string)
{
    Polynom poly(string);
	return (*this);
}

Polynom& Polynom::operator+=(const Polynom &obj)
{
    add_polynom_to_list(monomes_list, obj.monomes_list);
    return (*this);
}

Polynom& Polynom::operator-=(const Polynom &obj)
{
    Polynom obj_copy(obj);
    for (auto &i: obj_copy.monomes_list)
        i.coef *= (-1);

    add_polynom_to_list(monomes_list, obj_copy.monomes_list);
    return (*this);
}

Polynom& Polynom::operator*=(const Polynom &obj)
{
    list<Imute_monom> temp_list;
	
	for (const auto &i : monomes_list)
		for (const auto &j : obj.monomes_list)
			temp_list.push_back(i * j);
	
	monomes_list.clear();
	add_polynom_to_list(monomes_list, temp_list);
	return (*this);
}

Polynom& Polynom::operator/=(const char var_derivative)
{
    list<Imute_monom> temp_list;
	
	for (auto &i : monomes_list) {
		i /= var_derivative;
        temp_list.push_back(i);
    }
	
	monomes_list.clear();
	add_polynom_to_list(monomes_list, temp_list);
	return (*this);
}

Polynom& Polynom::operator/=(const char *vars_derivative)
{
    list<Imute_monom> list_tmp;
    string vars_d = vars_derivative;
    for (auto &i: monomes_list) // для каждого монома:
    {
        auto iter = vars_d.begin();
        for (iter; iter != vars_d.end(); ++iter)
            i /= (*iter);

        list_tmp.push_back(i);
    }
    monomes_list.clear();
    add_polynom_to_list(monomes_list, list_tmp);
    return (*this);
}

Polynom	Polynom::operator+(const Polynom &obj) const
{
    Polynom poly_copy(*this);
    return (poly_copy += obj);
}

Polynom Polynom::operator-(const Polynom &obj) const
{
    Polynom poly_copy(*this);
    return (poly_copy -= obj);
}

Polynom Polynom::operator*(const Polynom &obj) const
{
    Polynom poly_copy(*this);
    return (poly_copy *= obj);
}

Polynom Polynom::operator/(const char var_derivative) const
{
    Polynom poly_copy(*this);
    return (poly_copy /= var_derivative);
}

Polynom Polynom::operator/(const char* vars_derivative) const
{
    Polynom poly_copy(*this);
    return (poly_copy /= vars_derivative);
}

void remove_dublicates_characters(string& str)
{
    sort(str.begin(), str.end());
    str.erase(unique(str.begin(), str.end()), str.end());
}

bool check_homogeneity(const Polynom &obj) // xyz and x^3 - однородный полином
{
    bool flag = false;
    int degree = 0;

    if(obj.monomes_list.empty())
        return true;

    auto i = obj.monomes_list.front();
    degree = i.count_degree_for_monom();
    for (auto j: obj.monomes_list)
        if(j.count_degree_for_monom() != degree)
            return false;

    return true;
}

bool check_harmony(const Polynom& obj)
{
    if (obj.monomes_list.empty())
        return true;

    string	vars;

    for (auto i : obj.monomes_list)
        vars += i.get_vars();
    remove_dublicates_characters(vars);

    Polynom tmp(obj);

    tmp /= vars.c_str();
    tmp /= vars.c_str();
    if (!tmp.monomes_list.empty())
        return false;

    return true;
}

string Polynom::convert() const
{
    string str = "";
	list<Imute_monom>::const_iterator it = monomes_list.begin();
	str += (*it).convert();
	it++;
    for (it; it != monomes_list.end(); it++) {
        str += " $+$ ";
        str += it->convert();
    }
	return (str);
}