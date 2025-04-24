#include "BoolVector.h"
#include <cstring>
#include <algorithm>

unsigned char BoolVector::mask(int i) {
    return 1 << (i % 8);
}

BoolVector::BoolRank::BoolRank(unsigned char& b, int bitpos) : byte(b), bit(bitpos) {}

BoolVector::BoolRank::operator bool() const { 
    return (byte >> bit) & 1; 
}

BoolVector::BoolRank& BoolVector::BoolRank::operator=(bool value) {
    if (value) byte |= (1 << bit);
    else byte &= ~(1 << bit);
    return *this;
}