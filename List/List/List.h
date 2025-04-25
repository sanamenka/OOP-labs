#pragma once

#include "Node.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    List();
    List(const T* arr, int n);
    List(const List<T>& other);

    ~List();

    int getSize() const;
    void swap(List<T>& other);
    bool isEmpty() const;
    void clear();

    const Node<T>* find(const T& key) const;
    void insertHead(const T& value);
    void insertTail(const T& value);
    void insertAt(int pos, const T& value);
    void insertAfter(const T& key, const T& value);
    void removeHead();
    void removeTail();
    void removeAt(int pos);
    void remove(const T& key);
    const Node<T>* maxElement() const;
    const Node<T>* minElement() const;
    void sort();

    List<T>& operator=(const List<T>& other);
    T& operator[](int index);
    const T& operator[](int index) const;
    bool operator==(const List<T>& other) const;
    bool operator!=(const List<T>& other) const;
    List<T> operator+(const List<T>& other) const;
    List<T>& operator+=(const List<T>& other);

    friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
        Node<T>* current = list.head;
        while (current) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, List<T>& list) {
        list.clear();
        int n;
        is >> n;
        if (n < 0) throw std::invalid_argument("Input size cannot be negative");
        for (int i = 0; i < n; ++i) {
            T value;
            is >> value;
            list.insertTail(value);
        }
        return is;
    }
};


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
int List<T>::getSize() const {
    return size;
}

template <typename T>
void List<T>::swap(List<T>& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void List<T>::clear() {
    while (!isEmpty()) {
        removeHead();
    }
}

template <typename T>
const Node<T>* List<T>::find(const T& key) const {
    Node<T>* current = head;
    while (current) {
        if (current->data == key) return current;
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void List<T>::insertHead(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
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

template <typename T>
void List<T>::insertAt(int pos, const T& value) {
    if (pos < 0 || pos > size) throw std::out_of_range("Position out of range");
    if (pos == 0) {
        insertHead(value);
    }
    else if (pos == size) {
        insertTail(value);
    }
    else {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        size++;
    }
}

template <typename T>
void List<T>::insertAfter(const T& key, const T& value) {
    const Node<T>* node = find(key);
    if (node) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = const_cast<Node<T>*>(node)->next;
        newNode->prev = const_cast<Node<T>*>(node);
        if (node->next) {
            node->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
        const_cast<Node<T>*>(node)->next = newNode;
        size++;
    }
}

template <typename T>
void List<T>::removeHead() {
    if (isEmpty()) return;
    Node<T>* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
    size--;
}

template <typename T>
void List<T>::removeTail() {
    if (isEmpty()) return;
    Node<T>* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete temp;
    size--;
}

template <typename T>
void List<T>::removeAt(int pos) {
    if (pos < 0 || pos >= size) throw std::out_of_range("Position out of range");
    if (pos == 0) {
        removeHead();
    }
    else if (pos == size - 1) {
        removeTail();
    }
    else {
        Node<T>* current = head;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }
}

template <typename T>
void List<T>::remove(const T& key) {
    const Node<T>* node = find(key);
    if (node) {
        if (node == head) {
            removeHead();
        }
        else if (node == tail) {
            removeTail();
        }
        else {
            Node<T>* toDelete = const_cast<Node<T>*>(node);
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            delete toDelete;
            size--;
        }
    }
}

template <typename T>
const Node<T>* List<T>::maxElement() const {
    if (isEmpty()) return nullptr;
    Node<T>* maxNode = head;
    Node<T>* current = head->next;
    while (current) {
        if (current->data > maxNode->data) maxNode = current;
        current = current->next;
    }
    return maxNode;
}

template <typename T>
const Node<T>* List<T>::minElement() const {
    if (isEmpty()) return nullptr;
    Node<T>* minNode = head;
    Node<T>* current = head->next;
    while (current) {
        if (current->data < minNode->data) minNode = current;
        current = current->next;
    }
    return minNode;
}

template <typename T>
void List<T>::sort() {
    std::vector<T> vec;
    Node<T>* current = head;
    while (current) {
        vec.push_back(current->data);
        current = current->next;
    }
    std::sort(vec.begin(), vec.end());
    clear();
    for (const auto& val : vec) {
        insertTail(val);
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* current = other.head;
        while (current) {
            insertTail(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
T& List<T>::operator[](int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T& List<T>::operator[](int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
bool List<T>::operator==(const List<T>& other) const {
    if (size != other.size) return false;
    Node<T>* curr1 = head;
    Node<T>* curr2 = other.head;
    while (curr1) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return true;
}

template <typename T>
bool List<T>::operator!=(const List<T>& other) const {
    return !(*this == other);
}

template <typename T>
List<T> List<T>::operator+(const List<T>& other) const {
    List<T> result(*this);
    Node<T>* current = other.head;
    while (current) {
        result.insertTail(current->data);
        current = current->next;
    }
    return result;
}

template <typename T>
List<T>& List<T>::operator+=(const List<T>& other) {
    Node<T>* current = other.head;
    while (current) {
        insertTail(current->data);
        current = current->next;
    }
    return *this;
}