#pragma once

#include<iostream>
#include<list>
#include<string>;

class Polynom_in_GF
{
    std::uint16_t coefs;
public:
    friend Polynom_in_GF plus(const Polynom_in_GF&, const Polynom_in_GF&);        // сложение двух полиномов
    friend Polynom_in_GF multiply(Polynom_in_GF, Polynom_in_GF, uint16_t irred);  // умножение 

    Polynom_in_GF find_back();                                                    // поиск обратного
    Polynom_in_GF galoisPow(Polynom_in_GF, Polynom_in_GF);                        // возведение в степень
    std::list<Polynom_in_GF> find_irreducible();                                  // нахождение простых

    Polynom_in_GF& operator=(const Polynom_in_GF&);                               // оператор присваивания
    friend std::ostream& operator<< (std::ostream& s, const Polynom_in_GF& c);    // перегруженный оператор вывода
    friend std::istream& operator>> (std::istream& s, Polynom_in_GF& c);          // перегруженный оператор ввода
};

bool checkparity(uint16_t poly) {
    int bin = 0, sum = 0;
    while (poly)
    {
        bin = 10 * bin + poly % 2;
        poly /= 2;
        if (bin % 10 == 1)
            ++sum;
    }
    if (sum%2 == 1 && sum != 1) return true;
    else return false;
}

int get_degree(uint16_t poly)
{
    int degree = 0;
    uint16_t bit = 1;
    for (int i = 0; i < 16; i++)
    {
        if (poly & bit)
        {
            degree = i;
        }
        bit <<= 1;
    }
    return degree;
}

uint16_t get_mod(uint16_t poly, uint16_t mod) 
{
    int deg_mod = get_degree(mod), de_poly, difference;
    uint16_t tmp_poly = poly;

    while ((difference = (de_poly = get_degree(tmp_poly)) - deg_mod) >= 0)
    {
        tmp_poly ^= (mod << difference);
    }
    return tmp_poly;
}

bool check_divisibility(uint16_t poly) {
    uint16_t divider;
    int counter = 0;

    for (divider = 2; divider < 32; ++divider) {
        if (get_mod(poly, divider) != 0) {
            ++counter;
        }
        else {
            return false;
        }
    }
    return true;
}

std::list<Polynom_in_GF> Polynom_in_GF::find_irreducible() {
    std::list<Polynom_in_GF> lst;
    Polynom_in_GF poly;
    poly.coefs= 256;
    while (poly.coefs <= 511)
    {
        if ((poly.coefs & 1) && (checkparity(poly.coefs))  && (check_divisibility(poly.coefs)))
        {
            lst.push_back(poly);
        }
        poly.coefs += 1;
    }
    return lst;
}

Polynom_in_GF Polynom_in_GF::galoisPow(Polynom_in_GF a, Polynom_in_GF n) {
    Polynom_in_GF tmp;
    uint16_t irred = 283;
    if (n.coefs == 0) {
        tmp.coefs = 1;
        return tmp;
    }
    else if (n.coefs % 2 == 0) {
        n.coefs /= 2;
        return galoisPow(multiply(a, a, irred), n); // (a*a)^(n/2)
    }
    else {
        tmp = multiply(a, a, irred);
        n.coefs /= 2;
        return multiply(galoisPow(tmp, n),  a, irred); // a * (a*a)^[n/2] 
    }
}

Polynom_in_GF Polynom_in_GF::find_back() {
    Polynom_in_GF tmp;
    tmp.coefs = 254;
    return galoisPow(*this, tmp);
}

Polynom_in_GF multiply(Polynom_in_GF current_poly, Polynom_in_GF polynom, uint16_t irred = 283) {
    Polynom_in_GF tmp;
    tmp.coefs = 0;
    while (current_poly.coefs && polynom.coefs) {
        if (polynom.coefs & 1)                                          // если b нечетное 
            tmp.coefs ^= current_poly.coefs;                            // XOR 

        if (current_poly.coefs & 0x80)                                  // if a >= 128, сдвиг влево и
            current_poly.coefs = (current_poly.coefs << 1) ^ irred;     // XOR с неприводимым полиномом x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) 
        else                                                            // 00100010
            current_poly.coefs <<= 1;                                   // a * 2 
        polynom.coefs >>= 1;                                            // b / 2 
    }
    return tmp;
}

Polynom_in_GF plus(const Polynom_in_GF& current_poly, const Polynom_in_GF& polynom) {
    Polynom_in_GF tmp;
    tmp.coefs = current_poly.coefs ^ polynom.coefs;
    return tmp;
}

Polynom_in_GF& Polynom_in_GF::operator=(const Polynom_in_GF& polynom) {
    this->coefs = polynom.coefs;
    return *this;
};

std::istream& operator>>(std::istream& stream, Polynom_in_GF& polynom) {
    stream >> (polynom.coefs);
    return stream;
};

std::ostream& operator<<(std::ostream& stream, const Polynom_in_GF& polynom) {
    int bin = 0, tmp = polynom.coefs;
    int power_counter = -1;

    while (tmp)
    {
        ++power_counter;
        bin = 10 * bin + tmp % 2;
        tmp /= 2;
    }
    if (power_counter == 0 && (bin & 1) == 1) stream << "1 ";
    else if (power_counter == 1 && (bin & 1) == 1) stream << "x ";
    else if ((bin & 1) == 1) stream << "x^" << power_counter << " ";

    bin /= 10;
    --power_counter;
    while (bin != 0)
    {   
        if (power_counter == 0 && (bin & 1) == 1) stream << "+ 1";
        else if (power_counter == 1 && (bin & 1) == 1) stream << "+ x ";
        else if ((bin & 1) == 1)  stream << "+ x^" << power_counter << " ";
        bin /= 10;
        --power_counter;
    }
    return stream;
};