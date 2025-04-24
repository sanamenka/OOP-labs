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

BoolVector::BoolVector() : nBits(8), nBytes(1) {
    data = new unsigned char[nBytes];
    std::memset(data, 0, nBytes);
}

BoolVector::BoolVector(int size, bool value) : nBits(size), nBytes((size + 7) / 8) {
    data = new unsigned char[nBytes];
    std::memset(data, value ? 0xFF : 0x00, nBytes);
    if (value && nBits % 8)
        data[nBytes - 1] &= (1 << (nBits % 8)) - 1;
}

BoolVector::BoolVector(const char* str) {
    nBits = std::strlen(str);
    nBytes = (nBits + 7) / 8;
    data = new unsigned char[nBytes];
    std::memset(data, 0, nBytes);
    for (int i = 0; i < nBits; ++i)
        if (str[i] == '1') set(i, 1);
}

BoolVector::BoolVector(const BoolVector& other) : nBits(other.nBits), nBytes(other.nBytes) {
    data = new unsigned char[nBytes];
    std::memcpy(data, other.data, nBytes);
}

BoolVector::~BoolVector() {
    delete[] data;
}