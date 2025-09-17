#include "Array.h"

Array::Array() : data(nullptr), size(0) {}

Array::Array(size_t n) : size(n) {
    if (n > 0)
        data = new int[n](); 
    else
        data = nullptr;
}

Array::Array(const Array& other) : size(other.size) {
    if (size > 0) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    else {
        data = nullptr;
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        if (size > 0) {
            data = new int[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        else {
            data = nullptr;
        }
    }
    return *this;
}

Array::~Array() {
    delete[] data;
}

size_t Array::getSize() const {
    return size;
}

int Array::get(size_t index) const {
    if (index >= size)
        return 0; 
    return data[index];
}

void Array::set(size_t index, int value) {
    if (index < size)
        data[index] = value;
}

void Array::resize(size_t newSize) {
    if (newSize == size)
        return;

    int* newData = nullptr;
    if (newSize > 0) {
        newData = new int[newSize]();
        size_t minSize = (newSize < size) ? newSize : size;

        for (size_t i = 0; i < minSize; ++i)
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

    size_t maxSize = (size < other.size) ? size : other.size;
    result.resize(maxSize);

    size_t idx = 0;
    for (size_t i = 0; i < size; ++i) {
        int elem = data[i];
        bool foundInOther = false;

        for (size_t j = 0; j < other.size; ++j) {
            if (other.data[j] == elem) {
                foundInOther = true;
                break;
            }
        }

        if (foundInOther) {
            bool alreadyInResult = false;
            for (size_t k = 0; k < idx; ++k) {
                if (result.data[k] == elem) {
                    alreadyInResult = true;
                    break;
                }
            }

            if (!alreadyInResult) {
                result.data[idx++] = elem;
            }
        }
    }

    result.resize(idx);
    return result;
}