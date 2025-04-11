#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:

	int numerator;
	int detorminator;

public:
	Fraction();
	Fraction(int num, int den);

	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

	// Методы получения и установки числ. знам.
	void setNumenator(int num);
	void setDenominator();
	int getNumenator() const;
	int getNumenator() const;

	// Перегрузка операций
	Fraction operator+(const Fraction& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator*(const Fraction& other) const;
	Fraction operator/(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<(const Fraction& other) const;
	bool operator==(const Fraction& other) const;
	bool operator!=(const Fraction& other) const;
};

#endif