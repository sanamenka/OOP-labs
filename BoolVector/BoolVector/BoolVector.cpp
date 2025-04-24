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

int BoolVector::get_length() const {
    return nBits;
}

int BoolVector::get_weight() const {
    int w = 0;
    for (int i = 0; i < nBits; ++i)
        w += (*this)[i];
    return w;
}

void BoolVector::swap(BoolVector& other) {
    std::swap(data, other.data);
    std::swap(nBits, other.nBits);
    std::swap(nBytes, other.nBytes);
}

void BoolVector::invert() {
    for (int i = 0; i < nBytes; ++i)
        data[i] = ~data[i];
    if (nBits % 8)
        data[nBytes - 1] &= (1 << (nBits % 8)) - 1;
}

void BoolVector::invert(int i) {
    if (i < 0 || i >= nBits)
        return;
    data[i / 8] ^= mask(i);
}

void BoolVector::set(int i, bool value) {
    if (i < 0 || i >= nBits)
        return;
    if (value)
        data[i / 8] |= mask(i);
    else
        data[i / 8] &= ~mask(i);
}

void BoolVector::set(int i, int k, bool value) {
    for (int j = i; j < i + k && j < nBits; ++j)
        set(j, value);
}

void BoolVector::setAll(bool value) {
    std::memset(data, value ? 0xFF : 0x00, nBytes);
    if (value && nBits % 8)
        data[nBytes - 1] &= (1 << (nBits % 8)) - 1;
}

BoolVector::BoolRank BoolVector::operator[](int i) {
    return BoolRank(data[i / 8], i % 8);
}

bool BoolVector::operator[](int i) const {
    return (data[i / 8] >> (i % 8)) & 1;
}

BoolVector& BoolVector::operator=(const BoolVector& other) {
    if (this == &other) return *this;
    delete[] data;
    nBits = other.nBits;
    nBytes = other.nBytes;
    data = new unsigned char[nBytes];
    std::memcpy(data, other.data, nBytes);
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const {
    BoolVector res(nBits < other.nBits ? nBits : other.nBits);
    for (int i = 0; i < res.nBytes; ++i)
        res.data[i] = data[i] & other.data[i];
    return res;
}

BoolVector& BoolVector::operator&=(const BoolVector& other) {
    int minBytes = nBytes < other.nBytes ? nBytes : other.nBytes;
    for (int i = 0; i < minBytes; ++i)
        data[i] &= other.data[i];
    return *this;
}
BoolVector BoolVector::operator|(const BoolVector& other) const {
    BoolVector res(nBits < other.nBits ? nBits : other.nBits);
    for (int i = 0; i < res.nBytes; ++i)
        res.data[i] = data[i] | other.data[i];
    return res;
}
BoolVector& BoolVector::operator|=(const BoolVector& other) {
    int minBytes = nBytes < other.nBytes ? nBytes : other.nBytes;
    for (int i = 0; i < minBytes; ++i)
        data[i] |= other.data[i];
    return *this;
}
BoolVector BoolVector::operator^(const BoolVector& other) const {
    BoolVector res(nBits < other.nBits ? nBits : other.nBits);
    for (int i = 0; i < res.nBytes; ++i)
        res.data[i] = data[i] ^ other.data[i];
    return res;
}
BoolVector& BoolVector::operator^=(const BoolVector& other) {
    int minBytes = nBytes < other.nBytes ? nBytes : other.nBytes;
    for (int i = 0; i < minBytes; ++i)
        data[i] ^= other.data[i];
    return *this;
}
BoolVector BoolVector::operator~() const {
    BoolVector res(*this);
    res.invert();
    return res;
}

BoolVector BoolVector::operator<<(int shift) const {
    BoolVector res(*this);
    res <<= shift;
    return res;
}
BoolVector& BoolVector::operator<<=(int shift) {
    if (shift <= 0) return *this;
    for (int i = nBits - 1; i >= shift; --i)
        set(i, (*this)[i - shift]);
    for (int i = 0; i < shift; ++i)
        set(i, 0);
    return *this;
}
BoolVector BoolVector::operator>>(int shift) const {
    BoolVector res(*this);
    res >>= shift;
    return res;
}
BoolVector& BoolVector::operator>>=(int shift) {
    if (shift <= 0) return *this;
    for (int i = 0; i < nBits - shift; ++i)
        set(i, (*this)[i + shift]);
    for (int i = nBits - shift; i < nBits; ++i)
        set(i, 0);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BoolVector& bv) {
    for (int i = 0; i < bv.get_length(); ++i)
        os << (bv[i] ? '1' : '0');
    return os;
}

std::istream& operator>>(std::istream& is, BoolVector& bv) {
    std::string input;
    is >> input;
    int len = input.length();
    bv = BoolVector(len);
    for (int i = 0; i < len; ++i)
        bv.set(i, (input[i] == '1'));
    return is;
}