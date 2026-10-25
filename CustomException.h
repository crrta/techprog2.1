#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <string>

class CustomException {
private:
    std::string message;
public:
    CustomException(const std::string& msg);
    CustomException(const CustomException& other);
    ~CustomException();
    std::string getMessage() const;
};

#endif#pragma once
