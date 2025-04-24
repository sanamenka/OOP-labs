#include <iostream>
#include "BoolVector.h"
#include "BoolMatrix.h"

int main() {
    BoolMatrix mat1(3, 3, true);
    BoolMatrix mat2(3, 3, false);

    mat1.set(0, 0, false);
    mat1.set(1, 1, true);
    mat1.set(2, 2, false);

    std::cout << "Matrix 1:\n" << mat1 << std::endl;
    std::cout << "Matrix 1 weight: " << mat1.get_weight() << std::endl;
    std::cout << "Conjunction of all rows in matrix 1: " << mat1.conjunction() << std::endl;

    BoolMatrix mat3 = mat1 & mat2;
    std::cout << "Bitwise AND result (matrix 1 & matrix 2):\n" << mat3 << std::endl;

    return 0;
}