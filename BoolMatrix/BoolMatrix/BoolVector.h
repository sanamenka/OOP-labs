#pragma once
#include <iostream>

class BoolVector {
private:
    unsigned char* data;
    int nBits;
    int nBytes;

    static unsigned char mask(int i);

public:
    class BoolRank {
    private:
        unsigned char& byte;
        int bit;
    public:
        BoolRank(unsigned char& b, int bitpos);
        operator bool() const;
        BoolRank& operator=(bool value);
    };

    BoolVector();
    BoolVector(int size, bool value = false);
    BoolVector(const char* str);
    BoolVector(const BoolVector& other);

    ~BoolVector();

    int get_length() const;
    int get_weight() const;

    void swap(BoolVector& other);

    void invert();
    void invert(int i);

    void set(int i, bool value);
    void set(int i, int k, bool value);
    void setAll(bool value);

    BoolRank operator[](int i);
    bool operator[](int i) const;

    BoolVector& operator=(const BoolVector& other);

    BoolVector operator&(const BoolVector& other) const;
    BoolVector& operator&=(const BoolVector& other);
    BoolVector operator|(const BoolVector& other) const;
    BoolVector& operator|=(const BoolVector& other);
    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);
    BoolVector operator~() const;

    BoolVector operator<<(int shift) const;
    BoolVector& operator<<=(int shift);

    BoolVector operator>>(int shift) const;
    BoolVector& operator>>=(int shift);

    friend std::ostream& operator<<(std::ostream& os, const BoolVector& bv);
    friend std::istream& operator>>(std::istream& is, BoolVector& bv);
};