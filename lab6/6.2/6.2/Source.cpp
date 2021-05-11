//#include "Monom.h"
#include <iostream>
#include "Polynom.h"
#include <fstream>
#include <exception>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

void	to_vector(vector<string>& vec, string dlm, const string& src);
bool	get_polynom(string& src, string& dest);
bool	get_diff(string& src, string& dest);

int main()
{ 
    ifstream in("test.txt");
	ofstream out("test.tex", ios::trunc);


	if (in.fail()){
		cerr << "Can't open file" << endl;
		exit(-1);
	}

	vector<string> vec_expr; // вектор в котором выражение разбитое по пробелам
	string buf;
	string poly_str1, poly_str2;

	out << "\\def\\SetClass{article}\n";
	out << "\\documentclass{\\SetClass}\n";
	out << "\\begin{document}\n\n";

	while (getline(in, buf))
	{
		buf.erase(remove(buf.begin(), buf.end(), '\n'), buf.end());
		to_vector(vec_expr, " ", buf); 
		if (vec_expr.size() == 3) {
			if (vec_expr[1] == "/" || vec_expr[1] == "/=") {  
				string	vars_diff;
				if (!get_polynom(vec_expr[0], poly_str1))
					continue;
				if (!get_diff(vec_expr[2], vars_diff))
					continue;

				string	operation = vec_expr[1];
				Polynom	poly(poly_str1.c_str());
				Polynom	result;

				if (operation == "/")
					result = poly / vars_diff.c_str();

				else if (operation == "/=") {
					result = poly;
					result /= vars_diff.c_str();
				}
				out << poly.convert() << " $" << operation << "$" << vars_diff << " $=$ " << result.convert() << "\n\\par\n";
			}
			else
			{
				if (!get_polynom(vec_expr[0], poly_str1))
					continue;
				if (!get_polynom(vec_expr[2], poly_str2))
					continue;

				string	operation = vec_expr[1];
				Polynom	poly1(poly_str1.c_str());
				Polynom	poly2(poly_str2.c_str());
				Polynom	result;
				bool bresult;

				if (operation == "==")
					bresult = (poly1 == poly2);
				else if (operation == "!=")
					bresult = (poly1 != poly2);
				else if (operation == "+")
					result = poly1 + poly2;
				else if (operation == "-")
					result = poly1 - poly2;
				else if (operation == "*")
					result = poly1 * poly2;
				else if (operation == "+=") {
					result = poly1;
					result += poly2;
				}
				else if (operation == "-=") {
					result = poly1;
					result -= poly2;
				}
				else if (operation == "*=") {
					result = poly1;
					result *= poly2;
				}

				if (operation == "==" || operation == "!=")
					out << poly1.convert() << " $" << operation << "$ " << poly2.convert() << " $=$ " << (bresult == true ? "True" : "False") << "$" << "\n\\\n";
				else
					out << poly1.convert() << " $" << operation << "$ " << poly2.convert() << " $=$ " << result.convert() << "\n\\\n";
			}
		}
		else if (vec_expr.size() == 2) {
			string	function = vec_expr[0];

			if (function == "check_homogeneity" || function == "check_harmony") {
				if (!get_polynom(vec_expr[1], poly_str1))
					continue;

				Polynom poly(poly_str1.c_str());
				bool bresult;

				if (function == "check_homogeneity")
					bresult = check_homogeneity(poly);
				else if (function == "check_harmony")
				 	bresult = check_harmony(poly);

				for (int i = 0; i < function.length(); i++)
					if (function[i] == '_')
						function.insert(i++, "\\");

				out << "$" << function << "$ " << poly.convert() << " $=$ "<< "$" << (bresult == true ? "True" : "False") << "$" << "\n\\par\n";
			}
		}
	}
	out << "\\end{document}\n";	
	return 0;
}


void to_vector(vector<string>& vec, string dlm, const string& buf) // заносим строку с выражением в вектор
{
	size_t	p, start = 0, len = buf.length();
	vec.clear();
	start = buf.find_first_not_of(dlm); // ищем символ не содержащийся в строке
	p = buf.find_first_of(dlm, start);  // ищем след. символ содержащийся в строке
	
	while (p != string::npos) { 
		vec.push_back(buf.substr(start, p - start));
		start = buf.find_first_not_of(dlm, p);
		p = buf.find_first_of(dlm, start);
	}
	if (len > start)
		vec.push_back(buf.substr(start, len - start));
}

bool get_polynom(string& src, string& dest)
{
	if (!dest.empty())
		dest.clear();
	dest.assign(src.begin() + 1, src.end() - 1);
	return (true);
}

bool get_diff(string& src, string& dest) // поменять
{
	dest.clear();
	if (*(src.begin()) != '"' || *(src.end() - 1) != '"')
		return (false);

	dest.assign(src.begin() + 1, src.end() - 1);
	return (true);
}