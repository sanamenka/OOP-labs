#include "BoolMatrix.h"

BoolMatrix::BoolMatrix() : nRows(0), nCols(0) {}

BoolMatrix::BoolMatrix(int rows, int cols, bool value)
    : nRows(rows), nCols(cols) {
    for (int i = 0; i < rows; ++i) {
        this->rows.emplace_back(cols, value);
    }
}

BoolMatrix::BoolMatrix(const std::vector<std::vector<char>>& charMatrix) {
    nRows = charMatrix.size();
    if (nRows == 0) {
        nCols = 0;
        return;
    }
    nCols = charMatrix[0].size();

    for (const auto& row : charMatrix) {
        if (row.size() != nCols) {
            throw std::invalid_argument("Inconsistent matrix dimensions");
        }
        rows.emplace_back(nCols);
        for (int j = 0; j < nCols; ++j) {
            rows.back().set(j, row[j] != 0);
        }
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix& other)
    : rows(other.rows), nRows(other.nRows), nCols(other.nCols) {}

int BoolMatrix::get_row() const { 
    return nRows; 
}
int BoolMatrix::get_col() const {
    return nCols; 
}

void BoolMatrix::swap(BoolMatrix& other) {
    std::swap(rows, other.rows);
    std::swap(nRows, other.nRows);
    std::swap(nCols, other.nCols);
}

int BoolMatrix::get_weight() const {
    int total = 0;
    for (const auto& row : rows) {
        total += row.get_weight();
    }
    return total;
}

BoolVector BoolMatrix::conjunction() const {
    if (nRows == 0) return BoolVector(0);

    BoolVector result(nCols, true);
    for (const auto& row : rows) {
        result &= row;
    }
    return result;
}

BoolVector BoolMatrix::disjunction() const {
    if (nRows == 0) return BoolVector(0);

    BoolVector result(nCols, false);
    for (const auto& row : rows) {
        result |= row;
    }
    return result;
}

int BoolMatrix::rowWeight(int j) const {
    if (j < 0 || j >= nRows) {
        throw std::out_of_range("Row index out of range");
    }
    return rows[j].get_weight();
}

void BoolMatrix::invert(int i, int j) {
    if (j < 0 || j >= nRows || i < 0 || i >= nCols) {
        throw std::out_of_range("Index out of range");
    }
    rows[j].invert(i);
}

void BoolMatrix::invert(int i, int j, int k) {
    if (j < 0 || j >= nRows || i < 0 || i >= nCols || i + k > nCols) {
        throw std::out_of_range("Index out of range");
    }
    for (int pos = i; pos < i + k; ++pos) {
        rows[j].invert(pos);
    }
}

void BoolMatrix::set(int i, int j, bool value) {
    if (j < 0 || j >= nRows || i < 0 || i >= nCols) {
        throw std::out_of_range("Index out of range");
    }
    rows[j].set(i, value);
}

void BoolMatrix::set(int i, int j, int k, bool value) {
    if (j < 0 || j >= nRows || i < 0 || i >= nCols || i + k > nCols) {
        throw std::out_of_range("Index out of range");
    }
    rows[j].set(i, k, value);
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other) {
    if (this != &other) {
        rows = other.rows;
        nRows = other.nRows;
        nCols = other.nCols;
    }
    return *this;
}

BoolVector& BoolMatrix::operator[](int j) {
    if (j < 0 || j >= nRows) {
        throw std::out_of_range("Row index out of range");
    }
    return rows[j];
}

const BoolVector& BoolMatrix::operator[](int j) const {
    if (j < 0 || j >= nRows) {
        throw std::out_of_range("Row index out of range");
    }
    return rows[j];
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const {
    if (nRows != other.nRows || nCols != other.nCols) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }

    BoolMatrix result(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        result.rows[i] = rows[i] & other.rows[i];
    }
    return result;
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other) {
    *this = *this & other;
    return *this;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const {
    if (nRows != other.nRows || nCols != other.nCols) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }

    BoolMatrix result(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        result.rows[i] = rows[i] | other.rows[i];
    }
    return result;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other) {
    *this = *this | other;
    return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const {
    if (nRows != other.nRows || nCols != other.nCols) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }

    BoolMatrix result(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        result.rows[i] = rows[i] ^ other.rows[i];
    }
    return result;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other) {
    *this = *this ^ other;
    return *this;
}

BoolMatrix BoolMatrix::operator~() const {
    BoolMatrix result(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        result.rows[i] = ~rows[i];
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const BoolMatrix& bm) {
    for (int i = 0; i < bm.nRows; ++i) {
        os << bm.rows[i] << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolMatrix& bm) {
    int rows, cols;
    is >> rows >> cols;

    BoolMatrix temp(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            bool val;
            is >> val;
            temp.rows[i].set(j, val);
        }
    }

    bm.swap(temp);
    return is;
}
