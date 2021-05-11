#include "Monom.h"
#include <iostream>
#include <algorithm>

Imute_monom& Imute_monom::operator+=(const Imute_monom& obj)
{
    if (var_vect != obj.var_vect)
		cerr<<"Error in \"+=\": the monomes are not equal!";
	
	coef += obj.coef;
	return (*this);
}

Imute_monom& Imute_monom::operator-=(const Imute_monom& obj)
{
    if (var_vect == obj.var_vect) {
        coef -= obj.coef;
    }
    else 
        cerr<<"Error in \"-=\": the monomes are not equal!";
    return (*this);
}

Imute_monom& Imute_monom::operator*=(const Imute_monom& obj)
{
    if (obj.coef == 0) {
        (*this).clear_mem();
    }
    else {
        coef *= obj.coef;
        for (auto &i: obj.var_vect) {
            bool find_var = false;
            for (auto &j: var_vect) {
                if (j.first == i.first) {
                    j.second += i.second;
                    find_var = true;
                    break;
                }
            }
            if (find_var == false)
                var_vect.push_back(make_pair(i.first, i.second));
        }
    }
    return (*this);
}

Imute_monom& Imute_monom::operator*=(int x)
{
    if (x == 0)
        (*this).clear_mem();
    else
        coef *= x; 

    return (*this);
}

Imute_monom& Imute_monom::operator=(const Imute_monom& obj)
{
    (*this).clear_mem();
    coef = obj.coef;
    for (auto i: obj.var_vect) {
        var_vect.push_back(i);
    }
    return (*this);
}

Imute_monom& Imute_monom::operator=(const char *string)
{
    Imute_monom monom(string);
    return ((*this) = monom);
}

Imute_monom& Imute_monom::operator/=(const char variable_derivative)
{
    auto i = find_if(var_vect.begin(), var_vect.end(), [variable_derivative](pair<int, char> pair)
    {
        return (pair.first == variable_derivative);
    });

    // если производная по переменной, кот нет в мономе
    if (i == var_vect.end()) {
        (*this).clear_mem();
        coef = 0;
    }    
    else {
        coef *= i->second; 
        if (!(--(i->second))) 
            var_vect.erase(i);
    }
    return (*this);
}

bool Imute_monom::operator==(const Imute_monom &obj) const
{
    if (obj.coef != coef || obj.var_vect != var_vect)
        return false;
    else
        return true;
}

bool Imute_monom::operator!=(const Imute_monom &obj) const
{
    return !((*this) == obj);
}

// Тип ostream. Библиотечный тип, обеспечивающий потоковый вывод
ostream& operator<<(ostream &stream, const Imute_monom& obj1)
{
    if (obj1.coef == 1)
        stream << "";
    else if (obj1.coef == -1)
        stream << "-";
    else 
        stream << obj1.coef;
    for(auto i: obj1.var_vect) {
        if (i.second == 1) 
            stream << i.first;
        else 
            stream << i.first << "^" << i.second;
    }
    return stream;
}

// Тип istream. Библиотечный тип, обеспечивающий потоковый ввод
istream& operator>>(istream &stream, Imute_monom& obj1)
{
    string str;
    stream >> str;
    obj1 = Imute_monom(str.c_str());
    return stream;
}

Imute_monom Imute_monom::operator+(const Imute_monom& obj) const
{
    Imute_monom copy_monom(*this);
    copy_monom += obj;
    return copy_monom;
}

Imute_monom Imute_monom::operator-(const Imute_monom& obj) const
{
    Imute_monom copy_monom(*this);
    copy_monom -= obj;
    return copy_monom;
}

Imute_monom Imute_monom::operator*(const Imute_monom& obj) const
{
    Imute_monom copy_monom(*this);
    copy_monom *= obj;
    return copy_monom;
}

Imute_monom Imute_monom::operator/(const char var_derivative) const
{
    Imute_monom copy_monom(*this);
    copy_monom /= var_derivative;
    return copy_monom;
}

void Imute_monom::clear_mem()
{
    var_vect.clear();
    coef = 0;
}

int Imute_monom::count_degree_for_monom()
{
    int sum_degree = 0;
    for (auto& i: var_vect) {
        sum_degree += i.second;
    }
    return sum_degree;
}

string Imute_monom::get_vars()
{
    string	vars;
    for (auto i : var_vect)
        vars += i.first;
    return vars;
}

string Imute_monom::convert() const
{
    string str;
    str += "$";
    if (coef == 1);
    else if (coef == -1)
        str += "-";
    else 
        str += to_string(coef);

    for(auto& i: var_vect) {
        if (i.second == 1) {
            str += i.first;
        }
        else {
            str += i.first;
            str += "^";
            str += to_string(i.second);
        }
    }
    str += "$";
    return str;
}
