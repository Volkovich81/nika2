#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
private:
    int* data = nullptr;
    int size = 0;

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

   private:
    friend std::istream& operator>>(std::istream& is, Array& arr) {
        int n;
        if (!(is >> n)) return is;
        arr.resize(n);
        for (int i = 0; i < n; ++i)
            is >> arr.data[i];
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << "[";
        for (int i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i + 1 < arr.size) os << ", ";
        }
        os << "]";
        return os;
    }

    void swap(Array& other) noexcept;
};

#endif
