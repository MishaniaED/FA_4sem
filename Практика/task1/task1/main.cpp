#include"Polynom.h"

int main() {
	setlocale(LC_ALL, "");
	Polynom A, B, C, D;
	uint16_t irred = 285;
	std::cout << "������� ����� ��� �������� � � ���������� [0;255]: ";
	std::cin >> A;
	std::cout << "������� ����� ��� �������� B � ���������� [0;255]: ";
	std::cin >> B;
	std::cout << "��������� ����������:\n";
	std::cout << "A --- " << A << std::endl;
	std::cout << "B --- " << B << std::endl;

	C = plus(A, B);
	std::cout << "��������� ��������: " << C << std::endl;

	D = multiply(A, B);
	std::cout << "��������� ���������: " << D << std::endl;

	C = A.find_back();
	std::cout << "�������� � �: " << C << std::endl;

	D = multiply(C, A);
	std::cout << "�������� ��������� ����������� ���������: (" << A << ") * (" << C << ") = " << D;
	//find_irreducible();

	return 0;
}