#pragma once
#include "BoolVector.h"
#include <vector>
#include <stdexcept>

class BoolMatrix {
private:
    std::vector<BoolVector> rows;
    int nRows;
    int nCols;

public:
    BoolMatrix();
    BoolMatrix(int rows, int cols, bool value = false);
    BoolMatrix(const std::vector<std::vector<char>>& charMatrix);
    BoolMatrix(const BoolMatrix& other);

    ~BoolMatrix() = default;

    int get_row() const;
    int get_col() const;

    void swap(BoolMatrix& other);
    int get_weight() const;
    BoolVector conjunction() const;
    BoolVector disjunction() const;
    int rowWeight(int j) const;

    void invert(int i, int j);
    void invert(int i, int j, int k);
    void set(int i, int j, bool value);
    void set(int i, int j, int k, bool value);

    BoolMatrix& operator=(const BoolMatrix& other);
    BoolVector& operator[](int j);
    const BoolVector& operator[](int j) const;

    BoolMatrix operator&(const BoolMatrix& other) const;
    BoolMatrix& operator&=(const BoolMatrix& other);
    BoolMatrix operator|(const BoolMatrix& other) const;
    BoolMatrix& operator|=(const BoolMatrix& other);
    BoolMatrix operator^(const BoolMatrix& other) const;
    BoolMatrix& operator^=(const BoolMatrix& other);
    BoolMatrix operator~() const;

    friend std::ostream& operator<<(std::ostream& os, const BoolMatrix& bm);
    friend std::istream& operator>>(std::istream& is, BoolMatrix& bm);
};
