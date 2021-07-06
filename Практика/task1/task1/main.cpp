#include"Polynom.h"

int main() {
	setlocale(LC_ALL, "");
	Polynom A, B, C, D;
	uint16_t irred = 285;
	std::cout << "Введите число для полинома А в промежутке [0;255]: ";
	std::cin >> A;
	std::cout << "Введите число для полинома B в промежутке [0;255]: ";
	std::cin >> B;
	std::cout << "Введенные многочлены:\n";
	std::cout << "A --- " << A << std::endl;
	std::cout << "B --- " << B << std::endl;

	C = plus(A, B);
	std::cout << "Результат сложения: " << C << std::endl;

	D = multiply(A, B);
	std::cout << "Результат умножения: " << D << std::endl;

	C = A.find_back();
	std::cout << "Обратный к А: " << C << std::endl;

	D = multiply(C, A);
	std::cout << "Проверка обратного посредстовм умножения: (" << A << ") * (" << C << ") = " << D;
	//find_irreducible();

	return 0;
}