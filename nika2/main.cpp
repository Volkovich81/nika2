#include <iostream>
#include <string>
#include <cctype>
#include <clocale>

#include "Array.h"

bool isPositiveInteger(const std::string& s) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!std::isdigit(static_cast<unsigned char>(ch)))
            return false;
    }
    return true;
}

bool isIntegerString(const std::string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '+' || s[0] == '-') {
        if (s.size() == 1) return false;
        start = 1;
    }
    for (int i = start; i < static_cast<int>(s.size()); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    }
    return true;
}

int parseInt(const std::string& s) {
    int sign = 1;
    int i = 0;
    if (s[0] == '+' || s[0] == '-') {
        if (s[0] == '-') sign = -1;
        i = 1;
    }
    int value = 0;
    for (; i < static_cast<int>(s.size()); ++i)
        value = value * 10 + (s[i] - '0');
    return sign * value;
}

void inputArray(Array& arr) {
    std::string line;
    int n = 0;

    while (true) {
        std::cout << "Введите размер массива (>0): ";
        std::getline(std::cin, line);

        if (!isPositiveInteger(line)) {
            std::cout << "Ошибка: введите положительное целое число.\n";
            continue;
        }

        n = 0;
        for (char ch : line) n = n * 10 + (ch - '0');

        if (n <= 0) {
            std::cout << "Ошибка: число должно быть больше 0.\n";
            continue;
        }
        break;
    }

    arr.resize(n);

    for (int i = 0; i < n; ++i) {
        while (true) {
            std::cout << "Элемент [" << i << "] = ";
            std::getline(std::cin, line);
            if (!isIntegerString(line)) {
                std::cout << "Ошибка: введите целое число.\n";
                continue;
            }
            int val = parseInt(line);
            arr.set(i, val);
            break;
        }
    }
}

void printArray(const Array& arr) {
    std::cout << arr << "\n";
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    Array a, b, c;

    while (true) {
        std::cout << "\nМеню:\n"
            << "1. Ввести первый массив\n"
            << "2. Ввести второй массив\n"
            << "3. Найти пересечение массивов\n"
            << "4. Вывести массивы\n"
            << "5. Выход\n"
            << "Ваш выбор: ";

        std::string choiceLine;
        std::getline(std::cin, choiceLine);

        if (choiceLine.empty() || choiceLine.size() > 1 || !std::isdigit(static_cast<unsigned char>(choiceLine[0]))) {
            std::cout << "Ошибка: введите число от 1 до 5.\n";
            continue;
        }

        int choice = choiceLine[0] - '0';

        switch (choice) {
        case 1:
            inputArray(a);
            break;
        case 2:
            inputArray(b);
            break;
        case 3:
            if (a.getSize() == 0 || b.getSize() == 0)
                std::cout << "Массивы не заполнены.\n";
            else {
                c = a & b;
                std::cout << "Пересечение: " << c << "\n";
            }
            break;
        case 4:
            std::cout << "Первый массив: ";
            printArray(a);
            std::cout << "Второй массив: ";
            printArray(b);
            std::cout << "Пересечение: ";
            printArray(c);
            break;
        case 5:
            return 0;
        default:
            std::cout << "Неверный выбор.\n";
        }
    }
}
