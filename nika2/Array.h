#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
private:
    int* data;
    int size;

public:
    Array();
    explicit Array(int n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    int getSize() const;
    int get(int index) const;     
    void set(int index, int value);
    void resize(int newSize);

    Array intersect(const Array& other) const;
    Array operator&(const Array& other) const;

    friend std::istream& operator>>(std::istream& is, Array& arr);
    friend std::ostream& operator<<(std::ostream& os, const Array& arr);

    void swap(Array& other) noexcept;
};

#endif 
