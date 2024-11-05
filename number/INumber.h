#ifndef INUMBER_H
#define INUMBER_H

#include <string>

template <typename T>
class INumber {
public:
    virtual bool isNumber(const std::string& token) const = 0;
    virtual T convertToNumber(const std::string& token) const = 0;

    virtual ~INumber() = default;
};

#endif // !INUMBER_H