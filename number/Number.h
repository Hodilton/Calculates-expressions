#ifndef NUMBER_H
#define NUMBER_H

#include "./INumber.h"

#include <sstream>

template <typename T>
class Number : public INumber<T> {
public:
    bool isNumber(const std::string& token) const override {
        std::istringstream iss(token);
        double dummy;
        char extra;
        return (iss >> dummy) && !(iss >> extra);
    }

    T convertToNumber(const std::string& token) const override {
        T value;
        std::istringstream(token) >> value;
        return value;
    }
};

#endif // !NUMBER_H