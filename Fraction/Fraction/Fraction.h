#pragma once

#include <iostream>

class Fraction {
private:

	int numerator; // числитель
	int denominator; // знаменатель

	int get_nod(int a, int b); // метод нахождения НОД

	void reduce(); // метод для сокращения дроби

public:

	Fraction(); // конструктор по умолчанию
	Fraction(int num, int den); // конструктор с параметром

	// Методы получения и установки числителя и знаменателя
	void setNumenator(int num);
	void setDenominator(int den);
	int getNumenator() const;
	int getDenominator() const;

	// Перегрузка операций
	Fraction operator+(const Fraction& right) const;
	Fraction operator-(const Fraction& right) const;
	Fraction operator*(const Fraction& right) const;
	Fraction operator/(const Fraction& right) const;

	bool operator>(const Fraction& right) const;
	bool operator<(const Fraction& right) const;
	bool operator==(const Fraction& right) const;
	bool operator!=(const Fraction& right) const;

	// Объявляем дружественные функции для доступа к приватным полям класса Fraction. С целью потокового ввода/вывода
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);

	// Уникальные методы
	double toDouble() const; // конвертация в double
	static Fraction fromDouble(double value, int precision); // из double в дробь
};