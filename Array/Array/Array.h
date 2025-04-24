#pragma once

#include <iostream>

class Array {
private:
    int *data {nullptr};
    int size {0};
    int capacity {0};

    void resize(int new_capacity);

public:
    Array(int initial_size = 10);
    Array(const Array& other);
    Array(Array&& move) noexcept;

    ~Array();

    int getSize() const noexcept;
    void swap(Array& other) noexcept;
    int find(int value) const noexcept;

    bool insert(const int index, const int& value);
    bool removeAtIndex(int index);
    bool remove(int value);

    int& operator[](int index) noexcept;
    const int& operator[](int index) const noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    Array& operator+=(int value);

    friend std::istream& operator>>(std::istream& in, Array& arr);
    friend std::ostream& operator<<(std::ostream& out, const Array& arr);
};