#include <iostream>
#include <string>
#include <cctype>
#include <locale>
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

void inputArray(Array& arr) {
    std::string line;
    size_t n = 0;

    while (true) {
        std::cout << "Введите размер массива (>0): ";
        std::getline(std::cin, line);

        if (!isPositiveInteger(line)) {
            std::cout << "Ошибка: введите положительное целое число.\n";
            continue;
        }

        n = 0;
        for (char ch : line) {
            n = n * 10 + (ch - '0');
            if (n == 0) {
                break;
            }
        }

        if (n == 0) {
            std::cout << "Ошибка: число должно быть больше 0.\n";
            continue;
        }
        break;
    }

    arr.resize(n);

    for (size_t i = 0; i < n; ++i) {
        while (true) {
            std::cout << "Элемент [" << i << "] = ";
            std::getline(std::cin, line);

            bool negative = false;
            size_t pos = 0;
            if (!line.empty() && line[0] == '-') {
                negative = true;
                pos = 1;
            }
            bool isNumber = true;
            for (; pos < line.size(); ++pos) {
                if (!std::isdigit(static_cast<unsigned char>(line[pos]))) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber || line.empty() || line == "-" || line == "+") {
                std::cout << "Ошибка: введите целое число.\n";
                continue;
            }

            int val = 0;
            pos = (negative) ? 1 : 0;
            for (; pos < line.size(); ++pos) {
                val = val * 10 + (line[pos] - '0');
            }
            val = negative ? -val : val;

            arr.set(i, val);
            break;
        }
    }
}

void printArray(const Array& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr.get(i);
        if (i + 1 < arr.getSize())
            std::cout << ", ";
    }
    std::cout << "]";
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

        if (!isPositiveInteger(choiceLine) || choiceLine.length() > 1) {
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
                c = a.intersect(b);
                std::cout << "Пересечение: ";
                printArray(c);
                std::cout << "\n";
            }
            break;
        case 4:
            std::cout << "Первый массив: ";
            printArray(a);
            std::cout << "\nВторой массив: ";
            printArray(b);
            std::cout << "\nПересечение: ";
            printArray(c);
            std::cout << "\n";
            break;
        case 5:
            return 0;
        default:
            std::cout << "Неверный выбор.\n";
        }
    }
}