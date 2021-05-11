#include "TeX_convertible.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Imute_monom: public TeX_convertible
{
    friend class Polynom;
    private:
        int coef;
        vector<pair<char, int>> var_vect;

        Imute_monom& operator+=(const Imute_monom& obj);
        Imute_monom& operator-=(const Imute_monom& obj);
        Imute_monom& operator*=(const Imute_monom& obj);
        Imute_monom& operator*=(int x);
        Imute_monom& operator=(const Imute_monom& obj);
        Imute_monom& operator=(const char *string);
        Imute_monom& operator/=(const char var_derivative);
        void clear_mem();

    public:
        /* Constructors */
        Imute_monom() {};
        Imute_monom(const char* str) 
        {
            int tmp_coef = 0;
            int i;
            bool negativity = false;

            if (str[0] == '-') {
                negativity = true;
                coef = -1;
            }
            else coef = 1;

            if (negativity) {
                for (i = 1; isdigit(str[i]); i++)
                    tmp_coef = tmp_coef * 10 + str[i] - '0';
            }
            else {
                for (i = 0; isdigit(str[i]); i++)
                    tmp_coef = tmp_coef * 10 + str[i] - '0';
            }

            if (tmp_coef)
                coef *= tmp_coef;

            // добавление в вектор <переменная, степень>
            for (i; i < strlen(str);) {
                char var;
                int power = 0;
                // если переменная
                if (isalpha(str[i])) {
                    var = str[i];
                    // проверяем наличие степени у переменной
                    if ((i + 1 < strlen(str)) && (str[i + 1] == '^')) {
                        i = i + 2;
                        // нашли степень переменной
                        for (i; isdigit(str[i]); i++) {
                            power = power * 10 + str[i] - '0';
                        }
                    }
                    // иначе степень = 1
                    else {
                        power = 1;
                        i++;
                    }
                }
                else i++;
                // добавляем полученную пару в вектор пар
                var_vect.push_back(make_pair(var, power));
            }

        }
        Imute_monom(const Imute_monom& obj)
        {
            coef = obj.coef;
            var_vect = obj.var_vect;
        }

        ~Imute_monom()
        {
            var_vect.clear();
            coef = 0;
        };

        Imute_monom operator+(const Imute_monom& obj) const; 
        Imute_monom operator-(const Imute_monom& obj) const;
        Imute_monom operator*(const Imute_monom& obj) const;
        Imute_monom operator/(const char var_derivative) const;
        bool operator==(const Imute_monom &obj) const;
        bool operator!=(const Imute_monom &obj) const;

        friend ostream& operator<<(ostream &stream, const Imute_monom& obj1);
        friend istream& operator>>(istream &stream, Imute_monom& obj1);

        
        int count_degree_for_monom();
        string get_vars();

        string convert() const;

};