#include "Monom.h"
#include "TeX_convertible.h"
#include <list>
#include <string>

class Polynom : public TeX_convertible
{
	friend class Imute_monom;
	private:
		list<Imute_monom> monomes_list;
		void add_polynom_to_list(list<Imute_monom>& poly, list<Imute_monom> polynom_to_add)
		{
			for (auto& it : polynom_to_add) {
				if (it.coef == 0)
					continue;
				auto it_search = find_if(monomes_list.begin(), monomes_list.end(), [&it](const Imute_monom& elem)
					{
						return (elem.var_vect == it.var_vect);
					});

				// если такой элемент нашелс€
				if (it_search != monomes_list.end()) {
					it_search->coef += it.coef;
					if (it_search->coef == 0)
						monomes_list.erase(it_search);
				}
				// если такой элемент Ќ≈ нашелс€, то со спокойной душой добавл€ем
				else monomes_list.push_back(it);
			}
		}

	public:
		Polynom() {};

		Polynom(const char* str) // string = "-12ab-7z"
		{
			Polynom poly_tmp;
			list<Imute_monom> tmp_list;

			string monom_str = "";
			for (int i = 0; i < strlen(str); ) {
				if (str[i] == '+') {
					Imute_monom monome0(monom_str.c_str());
					// через временный список мономов
					tmp_list.push_back(monome0);
					monom_str.clear();
					i++;
				}
				if (str[i] == '-') {
					if (monom_str != "") {
						Imute_monom monome1(monom_str.c_str());
						// через временный список мономов
						tmp_list.push_back(monome1);
						monom_str.clear();
					}
					while (str[i] != '+' || str[i] != '-') { // wtf!?
						monom_str += str[i];
						i++;
						if (i == strlen(str) || str[i] == '+' || str[i] == '-') {
							break;
						}
					}
				}
				else {
					monom_str += str[i];
					i++;
				}
				if (i == strlen(str) && monom_str != "") {
					Imute_monom monome3(monom_str.c_str());
					// через временный список мономов
					tmp_list.push_back(monome3);
					monom_str.clear();
				}
			}
			add_polynom_to_list(monomes_list, tmp_list);
		}

		Polynom(list<Imute_monom> list_poly_to_add)
		{
			add_polynom_to_list(monomes_list, list_poly_to_add);
		}

		Polynom(const Polynom& obj)
		{
			for (auto i : obj.monomes_list)
				this->monomes_list.push_back(i);
			//add_polynom_to_list(monomes_list, tmp_list); - пачему
		}

		~Polynom()
		{
			monomes_list.clear();
		}
		
		Polynom& operator=(const Polynom& obj);
		Polynom& operator=(const char* string);
		Polynom& operator+=(const Polynom& obj);
		Polynom& operator-=(const Polynom& obj);
		Polynom& operator*=(const Polynom& obj);
		Polynom& operator/=(const char var_derivative);
		Polynom& operator/=(const char* vars_derivative);

		bool operator==(const Polynom &obj) const;
		bool operator!=(const Polynom &obj) const;
		Polynom	operator+(const Polynom &obj) const;
		Polynom operator-(const Polynom &obj) const;
		Polynom operator*(const Polynom &obj) const;
		Polynom operator/(const char var_derivative) const;
		Polynom operator/(const char* vars_derivative) const;

		friend bool check_homogeneity(const Polynom &obj);
		friend bool check_harmony(const Polynom &obj);
		friend ostream	&operator<<(ostream &stream, const Polynom &obj);
		
		string convert() const;
};