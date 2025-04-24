#include "Array.h"
#include <iostream>

int main() {
    Array arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    std::cout << "Initial array: " << arr << std::endl;

    arr.insert(1, 4);
    std::cout << "After inserting 4 at index 1: " << arr << std::endl;

    arr.remove(2);
    std::cout << "After removing 2: " << arr << std::endl;

    Array arr2(2);
    arr2[0] = 5;
    arr2[1] = 6;
    Array concat = arr + arr2;
    std::cout << "Concatenation of arr and arr2: " << concat << std::endl;

    std::cout << "Enter array size and elements (e.g., 3 7 8 9): ";
    Array arr3;
    std::cin >> arr3;
    std::cout << "Input array: " << arr3 << std::endl;

    int value = 4;
    int index = arr.find(value);
    std::cout << "Index of " << value << ": " << index << std::endl;

    return 0;
}