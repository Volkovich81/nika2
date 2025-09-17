#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

class Array {
private:
    int* data = nullptr;
    size_t size = 0;

public:
    Array();
    explicit Array(size_t n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    size_t getSize() const;
    int get(size_t index) const;
    void set(size_t index, int value);
    void resize(size_t newSize);

    Array intersect(const Array& other) const;
};

#endif