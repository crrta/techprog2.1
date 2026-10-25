#include "CustomException.h"
#include <iostream>

CustomException::CustomException(const std::string& msg) : message(msg) {
    std::cout << "Вызван конструктор с параметрами CustomException\n";
}

CustomException::CustomException(const CustomException& other) : message(other.message) {
    std::cout << "Вызван конструктор копирования CustomException\n";
}

CustomException::~CustomException() {
    std::cout << "Вызван деструктор CustomException\n";
}

std::string CustomException::getMessage() const {
    return message;
}