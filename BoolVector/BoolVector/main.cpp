#include "BoolVector.h"
#include <iostream>

int main() {
    BoolVector bv(16, 1);
    std::cout << bv << std::endl;
    bv.set(3, 0);
    std::cout << bv << std::endl;
    bv.invert(2);
    std::cout << bv << std::endl;
    bv.setAll(0);
    std::cout << bv << std::endl;
    bv.set(0, 5, 1);
    std::cout << bv << std::endl;
    std::cout << "weight: " << bv.get_weight() << std::endl;

    BoolVector bv2("1010101010101010");
    std::cout << bv2 << std::endl;

    BoolVector bv3 = bv & bv2;
    std::cout << bv3 << std::endl;

    bv3 |= bv2;
    std::cout << bv3 << std::endl;

    bv3 ^= bv;
    std::cout << bv3 << std::endl;

    bv3 <<= 2;
    std::cout << bv3 << std::endl;

    bv3 >>= 3;
    std::cout << bv3 << std::endl;

    ~bv3;
    std::cout << bv3 << std::endl;

    bv3[0] = 1;
    std::cout << "bv3[0] = " << bv3[0] << std::endl;
    BoolVector bv4;
    std::cin >> bv4;
    std::cout << bv4 << std::endl;
    return 0;
}