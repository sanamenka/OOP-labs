#include <iostream>
#include "Fraction.h"

int main() {
	system("chcp 1251");
	Fraction f1(3, 4);
	Fraction f2(1, 2);
	std::cout << "f1 = " << f1 << ", f2 = " << f2 << std::endl;
	f1.setDenominator(6);
	f2.setNumenator(4);
	std::cout << "f1 = " << f1 << ", f2 = " << f2 << std::endl;
	std::cout << "denominator f1 = " << f1.getDenominator() << std::endl;
	std::cout << "numenator f2 = " << f2.getNumenator() << std::endl;

	//тест
	std::cout << "f1 + f2 = " << (f1 + f2) << std::endl;
	std::cout << "f1 - f2 = " << (f1 - f2) << std::endl;
	std::cout << "f1 * f2 = " << (f1 * f2) << std::endl;
	std::cout << "f1 / f2 = " << (f1 / f2) << std::endl;

	//тест сравнения
	std::cout << "f1 > f2: " << (f1 > f2 ? "true" : "false") << std::endl;
	std::cout << "f1 < f2: " << (f1 < f2 ? "true" : "false") << std::endl;

	//Ввод вывод
	Fraction f3;
	std::cout << "Enter a fraction  (3/4): ";
	std::cin >> f3;
	std::cout << "You entered: " << f3 << std::endl;

	//Доп. методы
	std::cout << "f1 as double: " << f1.toDouble() << std::endl;
	Fraction f4 = Fraction::fromDouble(0.75, 2);
	std::cout << "0.75 as fraction: " << f4 << std::endl;

	return 0;
}