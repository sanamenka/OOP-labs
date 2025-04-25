#pragma once

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(const T& value);
};

