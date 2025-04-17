#include "Fraction.h"
#include <cmath>

// С помощью алгоритма Евклида найдем НОД
int Fraction::get_nod(int a, int b) { 
	a = std::abs(a);
	b = std::abs(b);
	while (b != 0) {
		a %= b;
		std::swap(a, b);
	}

	return a;
}

// Метод сокращение дроби
void Fraction::reduce() {
	if (denominator == 0) {
		std::cerr << "Error: Denominator cannot be zero" << std::endl;
		std::exit(1);
	}
	int nod = get_nod(numerator, denominator);
	numerator /= nod;
	denominator /= nod;
	if (denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}
}

// Конструкторы
Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
	reduce();
}

// Сеттеры и геттеры
void Fraction::setNumenator(int num) {
	numerator = num; 
	reduce();
}

void Fraction::setDenominator(int den) {
	denominator = den;
	reduce();
}

int Fraction::getNumenator() const {
	return numerator;
}

int Fraction::getDenominator() const {
	return denominator;
}

// Перегрузка операторов
Fraction Fraction::operator+(const Fraction& right) const {
	int resNum = this->numerator * right.denominator + right.numerator * this->denominator;
	int resDen = this->denominator * right.denominator;
	return Fraction(resNum, resDen);
}

Fraction Fraction::operator-(const Fraction& right) const {
	int resNum = this->numerator * right.denominator - right.numerator * this->denominator;
	int resDen = this->denominator * right.denominator;
	return Fraction(resNum, resDen);
}

Fraction Fraction::operator*(const Fraction& right) const {
	int resNum = this->numerator * right.numerator;
	int resDen = this->denominator * right.denominator;
	return Fraction(resNum, resDen);
}

Fraction Fraction::operator/(const Fraction& right) const {
	if (right.numerator == 0) {
		std::cerr << "Error: Division by zero" << std::endl;
		std::exit(1);
	}
	int resNum = this->numerator * right.denominator;
	int resDen = this->denominator * right.numerator;
	return Fraction(resNum, resDen);
}

// Операторы сравнения
bool Fraction::operator>(const Fraction& right) const {
	return (this->numerator * right.denominator > right.numerator * this->denominator);
}

bool Fraction::operator<(const Fraction& right) const {
	return (this->numerator * right.denominator < right.numerator * this->denominator);
}

bool Fraction::operator==(const Fraction& right) const {
	return (this->numerator == right.numerator && this->denominator == right.denominator);
}

bool Fraction::operator!=(const Fraction& right) const {
	return !(*this == right);;
}

// Ввод и вывод
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
	os << f.numerator << "/" << f.denominator;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& f) {
	char slash;
	is >> f.numerator >> slash >> f.denominator;
	if (slash != '/') {
		is.setstate(std::ios::failbit);
		std::cerr << "Error: Invalid fraction format: expected '/'" << std::endl;
		std::exit(1);
	}
	f.reduce();
	return is;
}

// Дополнительные методы
double Fraction::toDouble() const {
	return static_cast<double>(numerator) / denominator;
}

Fraction Fraction::fromDouble(double value, int precision) {
	int den = static_cast<int>(pow(10, precision)); // вычисление знаменателя (возводим 10 в степень точности precision)
	int num = static_cast<int>(value * den + (value >= 0 ? 0.5 : -0.5));
	return Fraction(num, den);
}
