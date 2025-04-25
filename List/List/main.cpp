#include "List.h"
#include <iostream>

int main() {
    List<int> list1;
    list1.insertHead(3);
    list1.insertTail(1);
    list1.insertAt(1, 2);
    std::cout << "List1: " << list1 << std::endl;

    int arr[] = { 4, 5, 6 };
    List<int> list2(arr, 3);
    std::cout << "List2: " << list2 << std::endl;

    List<int> list3 = list1 + list2;
    std::cout << "List3 (list1 + list2): " << list3 << std::endl;

    list3.sort();
    std::cout << "Sorted List3: " << list3 << std::endl;

    const Node<int>* max = list3.maxElement();
    const Node<int>* min = list3.minElement();
    if (max) std::cout << "Max element: " << max->data << std::endl;
    if (min) std::cout << "Min element: " << min->data << std::endl;

    return 0;
}