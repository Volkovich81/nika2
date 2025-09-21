#include "Array.h"

Array::Array() : size(0) {}

Array::Array(int n) : size(n) {
    if (n > 0)
        data = new int[n](); 
}

Array::Array(const Array& other) : size(other.size) {
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
}

void Array::swap(Array& other) noexcept {
    int* tmpData = data;
    data = other.data;
    other.data = tmpData;

    int tmpSize = size;
    size = other.size;
    other.size = tmpSize;
}

Array& Array::operator=(const Array& other) {
    if (this == &other) return *this;
    Array tmp(other);   
    swap(tmp);          
    return *this;
}

Array::~Array() {
    delete[] data;
}

int Array::getSize() const {
    return size;
}

int Array::get(int index) const {
    if (index >= size || data == nullptr)
        return 0; 
    return data[index];
}

void Array::set(int index, int value) {
    if (index < size && data != nullptr)
        data[index] = value;
}

void Array::resize(int newSize) {
    if (newSize == size) return;

    int* newData = nullptr;
    if (newSize > 0) {
        newData = new int[newSize]();
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; ++i)
            newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    size = newSize;
}


Array Array::intersect(const Array& other) const {
    Array result;
    if (size == 0 || other.size == 0)
        return result;

    int maxSize = (size < other.size) ? size : other.size;
    result.resize(maxSize);

    int idx = 0;
    for (int i = 0; i < size; ++i) {
        int elem = data[i];
        bool foundInOther = false;

        for (int j = 0; j < other.size; ++j) {
            if (other.data[j] == elem) {
                foundInOther = true;
                break;
            }
        }

        if (!foundInOther) continue;

        bool alreadyInResult = false;
        for (int k = 0; k < idx; ++k) {
            if (result.data[k] == elem) {
                alreadyInResult = true;
                break;
            }
        }

        if (!alreadyInResult) {
            result.data[idx++] = elem;
        }
    }

    result.resize(idx);
    return result;
}

Array Array::operator&(const Array& other) const {
    return intersect(other);
}


std::istream& operator>>(std::istream& is, Array& arr) {
    int n;
    if (!(is >> n)) return is;
    arr.resize(n);
    for (int i = 0; i < n; ++i)
        is >> arr.data[i];
    return is;
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    os << "[";
    for (int i = 0; i < arr.size; ++i) {
        os << arr.data[i];
        if (i + 1 < arr.size) os << ", ";
    }
    os << "]";
    return os;
}
