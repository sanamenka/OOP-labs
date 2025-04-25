#include "List.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
List<T>::List(const T* arr, int n) : head(nullptr), tail(nullptr), size(0) {
    if (n < 0) throw std::invalid_argument("Array size cannot be negative");
    for (int i = 0; i < n; ++i) {
        insertTail(arr[i]);
    }
}

template <typename T>
List<T>::List(const List<T>& other) : head(nullptr), tail(nullptr), size(0) {
    Node<T>* current = other.head;
    while (current) {
        insertTail(current->data);
        current = current->next;
    }
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::insertTail(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}