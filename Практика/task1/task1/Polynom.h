#pragma once

#include<iostream>
#include<list>
#include<string>;

class Polynom_in_GF
{
    std::uint16_t coefs;
public:
    friend Polynom_in_GF plus(const Polynom_in_GF&, const Polynom_in_GF&);                    // �������� ���� ���������
    friend Polynom_in_GF multiply(const Polynom_in_GF, const Polynom_in_GF, uint16_t irred);  // ��������� 

    Polynom_in_GF operator=(const Polynom_in_GF&);                                      // �������� ������������

    Polynom_in_GF find_back();                                                    // ����� ���������
    Polynom_in_GF galoisPow(Polynom_in_GF, Polynom_in_GF);                                    // ���������� � �������
    std::list<Polynom_in_GF> find_irreducible();                                  // ���������� �������

    friend std::ostream& operator<< (std::ostream& s, const Polynom_in_GF& c);    // ������������� �������� ������
    friend std::istream& operator>> (std::istream& s, Polynom_in_GF& c);          // ������������� �������� �����
};

std::list<Polynom_in_GF> Polynom_in_GF::find_irreducible() {
    std::list<Polynom_in_GF> lst;
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
        if (polynom.coefs & 1)                                          // ���� b �������� 
            tmp.coefs ^= current_poly.coefs;                            // XOR 

        if (current_poly.coefs & 0x80)                                  // if a >= 128, ����� ����� �
            current_poly.coefs = (current_poly.coefs << 1) ^ irred;     // XOR � ������������ ��������� x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) 
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

Polynom_in_GF Polynom_in_GF::operator=(const Polynom_in_GF& polynom) {
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