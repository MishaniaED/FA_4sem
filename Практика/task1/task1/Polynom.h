#pragma once

#include<iostream>
#include<list>
#include<string>;

class Polynom
{
    std::uint16_t coefs;
public:
    friend Polynom plus(const Polynom&, const Polynom&);                    // сложение двух полиномов
    friend Polynom multiply(const Polynom, const Polynom, uint16_t irred);// умножение 

    Polynom operator=(const Polynom&);                                      // оператор присваивания

    Polynom find_back();                                                    // поиск обратного
    Polynom galoisPow(Polynom, Polynom);                                    // возведение в степень
    std::list<Polynom> find_irreducible();                                  // нахождение простых

    friend std::ostream& operator<< (std::ostream& s, const Polynom& c);    // перегруженный оператор вывода
    friend std::istream& operator>> (std::istream& s, Polynom& c);          // перегруженный оператор ввода
};

std::list<Polynom> Polynom::find_irreducible() {
    std::list<Polynom> lst;
    return lst;
}

Polynom Polynom::galoisPow(Polynom a, Polynom n) {
    Polynom tmp;
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

Polynom Polynom::find_back() {
    Polynom tmp;
    tmp.coefs = 254;
    return galoisPow(*this, tmp);
}

Polynom multiply(Polynom current_poly, Polynom polynom, uint16_t irred = 283) {
    Polynom tmp;
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

Polynom plus(const Polynom& current_poly, const Polynom& polynom) {
    Polynom tmp;
    tmp.coefs = current_poly.coefs ^ polynom.coefs;
    return tmp;
}

Polynom Polynom::operator=(const Polynom& polynom) {
    this->coefs = polynom.coefs;
    return *this;
};

std::istream& operator>>(std::istream& stream, Polynom& polynom) {
    stream >> (polynom.coefs);
    return stream;
};

std::ostream& operator<<(std::ostream& stream, const Polynom& polynom) {
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