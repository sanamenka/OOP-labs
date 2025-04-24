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


};

