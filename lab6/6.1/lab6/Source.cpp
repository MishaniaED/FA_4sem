#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "Tex_conv.h"
using namespace std;

float epsilon = 1E-6;
void swap(float* arr1, float* arr2, int size);
int factorial(int n);

class square_matrix : public TeX_Convertible {
private:
	int dimension;
	float** elems;
public:
	square_matrix(int d, float** el) {
		dimension = d;
		elems = new float* [d];
		for (int j = 0; j < d; j++) {
			elems[j] = new float[d];
		}
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++) {
				elems[i][j] = el[i][j];
			}
		}
	}
	square_matrix(int d) {
		dimension = d;
		elems = new float* [d];
		for (int j = 0; j < d; j++) {
			elems[j] = new float[d];
		}
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++) {
				elems[i][j] = 0;
			}
			i++;
		}
	}

	square_matrix(const square_matrix& matrix) {
		//square_matrix matr { determinant };
		dimension = matrix.dimension;
		elems = new float* [dimension];
		for (int i = 0; i < dimension; i++)
			elems[i] = new float[dimension];
		for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++)
				elems[i][j] = matrix.elems[i][j];
	}

	~square_matrix() {
		for (int i = 0; i < dimension; i++) {
			delete[] elems[i];
		}
		delete[] elems;
	}

	string convert() const {
		string output = "\n";
		output += "$\\begin{pmatrix}\n";
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				if (j != dimension - 1)
					output += to_string(elems[i][j]) + " & ";
				else
					output += to_string(elems[i][j]);
			}
			output += "\\";
			output += "\n";
		}
		output += "\\end{pmatrix}$";
		return output; 
	}

	float* operator[](int subscript);					// float& 				// индексирование
	square_matrix operator+=(const square_matrix& matrix);
	square_matrix operator-=(const square_matrix& matrix);
	square_matrix operator*=(const square_matrix& matrix);
	square_matrix operator*=(const float x);
	square_matrix operator+(const square_matrix matrix)const;
	square_matrix operator-(const square_matrix matrix)const;
	square_matrix operator*(const square_matrix matrix)const;
	bool operator!=(const square_matrix& matrix)const;
	bool operator==(const square_matrix& matrix)const;
	square_matrix operator=(const square_matrix& matrix);

	friend float determinant(const square_matrix& matrix);
	friend square_matrix reverse(const square_matrix& matrix);
	friend square_matrix transpointing(const square_matrix& matrix);
	friend float treck(const square_matrix& matrix);
	friend square_matrix exp(const square_matrix& matrix);
	friend ostream& operator << (ostream& out, const square_matrix& matrix);
	friend istream& operator >> (istream& in, const square_matrix& matrix); // не const
};

square_matrix square_matrix::operator+=(const square_matrix& matrix) {
	if (dimension != matrix.dimension) {
		cerr << "matrices of different sizes!\n";
		exit(-4);
	}
	for (int row = 0; row < matrix.dimension; row++)
		for (int col = 0; col < matrix.dimension; col++)
			elems[row][col] += matrix.elems[row][col];

	return *this;
}
square_matrix square_matrix::operator-=(const square_matrix& matrix) {
	if (dimension != matrix.dimension) {
		cerr << "matrices of different sizes!\n";
		exit(-5);
	}
	for (int row = 0; row < matrix.dimension; row++)
		for (int col = 0; col < matrix.dimension; col++)
			elems[row][col] -= matrix.elems[row][col];

	return *this;
}
square_matrix square_matrix::operator*=(const square_matrix& matrix) {
	if (dimension != matrix.dimension && dimension!=1 && matrix.dimension!=1) {
		cerr << "matrices of different sizes!\n";
		exit(-6);
	}
	if (matrix.dimension == 1) {
		for (int row = 0; row < matrix.dimension; row++)
			for (int col = 0; col < matrix.dimension; col++)
				elems[row][col] *= matrix.elems[0][0];
	}
	else if(dimension == 1){
		for (int row = 0; row < matrix.dimension; row++)
			for (int col = 0; col < matrix.dimension; col++)
				matrix.elems[row][col] *= elems[0][0];
		return matrix;
	}
	else{
		for (int row = 0; row < matrix.dimension; row++)
			for (int col = 0; col < matrix.dimension; col++)
				elems[row][col] *= matrix.elems[row][col];
	}
	

	return *this;
}
square_matrix square_matrix::operator*=(const float x) {
	for (int row = 0; row < dimension; row++)
		for (int col = 0; col < dimension; col++)
			elems[row][col] *= x;

	return *this;
}
square_matrix square_matrix::operator+(const square_matrix matrix)const {
	square_matrix copy(*this);
	copy += matrix;
	return (copy);
}
square_matrix square_matrix::operator-(const square_matrix matrix)const {
	square_matrix copy(*this);
	copy -= matrix;
	return (copy);
}
square_matrix square_matrix::operator*(const square_matrix matrix)const {
	square_matrix copy(*this);
	copy *= matrix;
	return (copy);
}
bool square_matrix::operator!=(const square_matrix& matrix)const {
	bool not_equally = true;
	if (dimension != matrix.dimension) {
		return not_equally;
	}
	for (int row = 0; row < dimension; row++)
		for (int col = 0; col < dimension; col++)
			if (elems[row][col] != matrix.elems[row][col]) {
				return not_equally;
			}
	not_equally = false;
	return not_equally;
}
bool square_matrix::operator==(const square_matrix& matrix) const {
	bool equally = false;
	if (dimension != matrix.dimension) {
		return equally;
	}
	for (int row = 0; row < dimension; row++)
		for (int col = 0; col < dimension; col++)
			if (abs(elems[row][col] - matrix.elems[row][col]) > epsilon) {
				return equally;
			}
	equally = true;
	return equally;
}

square_matrix square_matrix::operator=(const square_matrix& matrix) {
	dimension = matrix.dimension;
	for (int row = 0; row < dimension; row++)
		for (int col = 0; col < dimension; col++)
			elems[row][col] = matrix.elems[row][col];
	return *this;
}

static void swap(float* arr1, float* arr2, int size)
{
	double    tmp1;
	for (int i = 0; i < size; i++)
	{
		tmp1 = arr1[i];
		arr1[i] = arr2[i];
		arr2[i] = tmp1;
	}
}

float determinant(const square_matrix& matrix) {
	square_matrix copy(matrix);
	float index;
	int sign;
	float det;

	sign = 1;
	det = 1;
	if (matrix.dimension == 0)
		return (0);
	for (int i = 0; i < matrix.dimension; i++)
		for (int j = i + 1; j < matrix.dimension; j++)
		{
			if (copy[i][i] == 0)
				for (int l = i + 1; l < matrix.dimension; l++)
					if (copy[l][i] != 0)
					{
						swap(copy[l], copy[i], matrix.dimension);
						sign *= -1;
						break;
					}
			if (copy[i][i] == 0)
				return (0);
			index = copy[j][i] / copy[i][i];
			for (int k = 0; k < matrix.dimension; k++)
				copy[j][k] -= index * copy[i][k];
		}
	for (int i = 0; i < matrix.dimension; i++)
		det *= copy[i][i];
	//std::cout << copy;
	return (det * sign);
}


square_matrix reverse(const square_matrix& matrix) {
	square_matrix revmatr(matrix);
	float temp;
	for (int i = 0; i < matrix.dimension; i++)
		for (int j = 0; j < matrix.dimension; j++) {
			revmatr.elems[i][j] = 0.0;
			if (i == j)
				revmatr.elems[i][j] = 1.0;
		}

	for (int k = 0; k < matrix.dimension; k++)
	{
		temp = revmatr[k][k];
		for (int j = 0; j < revmatr.dimension; j++)
		{
			matrix.elems[k][j] /= temp;
			revmatr.elems[k][j] /= temp;
		}

		for (int i = k + 1; i < matrix.dimension; i++)
		{
			temp = matrix.elems[i][k];

			for (int j = 0; j < revmatr.dimension; j++)
			{
				matrix.elems[i][j] -= matrix.elems[k][j] * temp;
				revmatr.elems[i][j] -= revmatr.elems[k][j] * temp;
			}
		}
	}

	for (int k = matrix.dimension - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = matrix.elems[i][k];
			for (int j = 0; j < matrix.dimension; j++)
			{
				matrix.elems[i][j] -= matrix.elems[k][j] * temp;
				revmatr.elems[i][j] -= revmatr.elems[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < matrix.dimension; i++)
		for (int j = 0; j < matrix.dimension; j++)
			matrix.elems[i][j] = revmatr.elems[i][j];
	return matrix;
}

square_matrix transpointing(const square_matrix& matrix) {
	square_matrix tr = matrix;
	for (int i = 0; i < matrix.dimension; i++) {
		for (int j = 0; j < matrix.dimension; j++) {
			tr.elems[i][j] = matrix.elems[j][i];
		}
	}
	return tr;
}

float treck(const square_matrix& matrix) {
	float trace = 0;
	for (int row = 0; row < matrix.dimension; row++)
		for (int col = 0; col < matrix.dimension; col++)
			if (row == col)
				trace += matrix.elems[row][col];
	return trace;
}

int factorial(int n){
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}

square_matrix exp(const square_matrix& matrix) {
	square_matrix identity_matrix(matrix);
	for (int i = 0; i < matrix.dimension;i++) {
		for (int j = 0; j < matrix.dimension; j++) {
			if (i == j) identity_matrix[i][j] = 1;
			else identity_matrix[i][j] = 0;
		}
	}
	
	/*for (int i = 0; i < matrix.dimension; i++){
		identity_matrix.elems[i][i] = 1;
	}*/
	square_matrix exp_matrix(matrix.dimension);
	square_matrix tmp_matrix(matrix);
	for (int i = 0; i < matrix.dimension; i++)
	{
		square_matrix fac(1);
		fac[0][0] = (float(1) / factorial(i));
		exp_matrix +=  tmp_matrix * fac;
		tmp_matrix *= matrix;
	}
	/*for (int i = 0; i < exp_matrix.dimension; i++) {
		for (int j = 0; j < exp_matrix.dimension; j++) {
			if (i == j) exp_matrix[i][j] += 1;
		}
	}*/
	exp_matrix += identity_matrix;
	return (exp_matrix);
}

istream& operator >> (istream& in, const square_matrix& matrix)
{
	int i, j;
	for (i = 0; i < matrix.dimension; i++)
	{
		for (j = 0; j < matrix.dimension; j++)
			in >> matrix.elems[i][j];
	}
	for (; i < matrix.dimension; i++)
	{
		for (; j < matrix.dimension; j++)
			matrix.elems[i][j] = 0;
	}
	//string tmp;
	return in;
}

ostream& operator << (ostream& out, const square_matrix& matrix) {
	int i, j;
	for (i = 0; i < matrix.dimension; i++)
	{
		for (j = 0; j < matrix.dimension; j++)
			out << matrix.elems << ", ";
	}
	out << "\n";
	return out;
}

float* square_matrix:: operator [] (int subscript)
{
	if (subscript < 0 || subscript >= dimension)
	{
		cerr << "\n Invalid index: " << subscript << endl;
		exit(-2);
	}
	return elems[subscript];
}



int main() {
	vector<float> vec;
	string oper;
	int d;
	ofstream fout("tex.TeX");
	ifstream fin("my.txt", ios::in);
	if (fin.fail() || fout.fail()) {
		cerr << "Can not open file";
		return -1;
	}

	while (fin >> d)
	{
		// матрица
		square_matrix matrix{ d };
		fin >> matrix;

		// операция

		fin >> oper;
		square_matrix tmp(matrix);
		//матрица или ее отстутсвие
		if (oper == "+=") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " += " << matrix2.convert() << " = ";
			matrix += matrix2;
			fout << matrix.convert() << "\n";
		}
		else if (oper == "-=") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " -= " << matrix2.convert() << " = ";
			matrix -=matrix2;
			fout << matrix.convert() << "\n";
		}
		else if (oper == "*=") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " *= " << matrix2.convert() << " = ";
			matrix *= matrix2;
			fout << matrix.convert() << "\n";
		}
		else if (oper == "+") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " + " << matrix2.convert() << " = ";
			tmp = (matrix + matrix2);
			//cout << tmp[0][0];
			fout << tmp.convert() << "\n";
		}
		else if (oper == "-") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " - " << matrix2.convert() << " = ";
			tmp = (matrix - matrix2);
			fout << tmp.convert() << "\n";
		}
		else if (oper == "*") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " * " << matrix2.convert() << " = ";
			tmp = (matrix * matrix2);
			fout << tmp.convert() << "\n";
		}
		else if (oper == "!=") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " != " << matrix2.convert() << " = ";
			if (bool not_equal = (matrix == matrix2))
				fout << "false" << "\n";
			else fout << "true" << "\n";  
		}
		else if (oper == "==") {
			fin >> d;
			square_matrix matrix2{ d };
			fin >> matrix2;
			fout << matrix.convert() << " == " << matrix2.convert() << " ";
			if(bool equal = (matrix == matrix2))
				fout << "true" << "\n";
			else fout << "false" << "\n";

		}
		else if (oper == "det") {
			fout << determinant(matrix) << "\n";
		}
		else if (oper == "trace") {
			fout << treck(matrix) << "\n";
		}
		else if (oper == "exp") {
			fout << exp(matrix).convert() << "\n";
		}
	}
	fout.close();
	fin.close();
	return 0;
}