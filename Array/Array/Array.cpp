#include "Array.h"
#include <utility>
#include <cassert>

void Array::resize(int new_capacity) {
    int* new_data = new int[new_capacity];
    int new_size = size < new_capacity ? size : new_capacity;
    for (int i = 0; i < new_size; ++i)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    size = new_size;
}

Array::Array(int initial_size) {
    if (initial_size < 0)
        initial_size = -initial_size;
    size = initial_size;
    capacity = initial_size > 0 ? initial_size * 2 : 10;
    data = new int[capacity];
    for (int i = 0; i < size; ++i)
        data[i] = 0;
}

Array::Array(const Array& other) : size(other.size), capacity(other.capacity) {
    data = new int[capacity];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

Array::Array(Array&& move) noexcept : size(move.size), capacity(move.capacity), data(move.data) {
    move.data = nullptr;
    move.size = 0;
    move.capacity = 0;
}

Array::~Array() {
    delete[] data;
}

int Array::getSize() const noexcept {
    return size;
}

void Array::swap(Array& other) noexcept {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

int Array::find(int value) const noexcept {
    for (int i = 0; i < size; ++i) {
        if (data[i] == value)
            return i;
    }
    return -1;
}

bool Array::insert(const int index, const int& value) {
    if (index < 0 || index > size)
        return false;
    if (size == capacity)
        resize(capacity == 0 ? 1 : capacity * 2);
    for (int i = size; i > index; --i)
        data[i] = data[i - 1];
    data[index] = value;
    ++size;
    return true;
}

bool Array::removeAtIndex(int index) {
    if (index < 0 || index >= size)
        return false;
    for (int i = index; i < size - 1; ++i)
        data[i] = data[i + 1];
    --size;
    if (size < capacity / 4 && capacity > 1)
        resize(capacity / 2);
    return true;
}

bool Array::remove(int value) {
    int index = find(value);
    if (index == -1)
        return false;
    return removeAtIndex(index);
}

int& Array::operator[](int index) noexcept {
    assert(index >= 0 && index < size);
    return data[index];
}

const int& Array::operator[](int index) const noexcept {
    assert(index >= 0 && index < size);
    return data[index];
}

Array& Array::operator=(const Array& other) {
    Array copy(other);
    swap(copy);
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    swap(other);
    return *this;
}

Array Array::operator+(const Array& other) const {
    Array result(size + other.size);
    for (int i = 0; i < size; ++i)
        result[i] = data[i];
    for (int i = 0; i < other.size; ++i)
        result[i + size] = other.data[i];
    return result;
}

Array& Array::operator+=(const Array& other) {
    *this = *this + other;
    return *this;
}

Array& Array::operator+=(int value) {
    insert(size, value);
    return *this;
}

std::istream& operator>>(std::istream& in, Array& arr) {
    int n;
    in >> n;
    Array temp(n);
    for (int i = 0; i < n; ++i)
        in >> temp.data[i];
    arr = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Array& arr) {
    for (int i = 0; i < arr.size; ++i)
        out << arr.data[i] << " ";
    return out;
}