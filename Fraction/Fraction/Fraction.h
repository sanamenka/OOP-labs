#pragma once

#include <iostream>

class Fraction {
private:

	int numerator; // ���������
	int denominator; // �����������

	int get_nod(int a, int b); // ����� ���������� ���

	void reduce(); // ����� ��� ���������� �����

public:

	Fraction(); // ����������� �� ���������
	Fraction(int num, int den); // ����������� � ����������

	// ������ ��������� � ��������� ��������� � �����������
	void setNumenator(int num);
	void setDenominator(int den);
	int getNumenator() const;
	int getDenominator() const;

	// ���������� ��������
	Fraction operator+(const Fraction& right) const;
	Fraction operator-(const Fraction& right) const;
	Fraction operator*(const Fraction& right) const;
	Fraction operator/(const Fraction& right) const;

	bool operator>(const Fraction& right) const;
	bool operator<(const Fraction& right) const;
	bool operator==(const Fraction& right) const;
	bool operator!=(const Fraction& right) const;

	// ��������� ������������� ������� ��� ������� � ��������� ����� ������ Fraction. � ����� ���������� �����/������
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);

	// ���������� ������
	double toDouble() const; // ����������� � double
	static Fraction fromDouble(double value, int precision); // �� double � �����
};