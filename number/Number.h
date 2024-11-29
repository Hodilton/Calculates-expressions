#ifndef CALC_NUMBER_H
#define CALC_NUMBER_H

#include "./INumber.h"

#include <sstream>

namespace calc::number {

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
}

#endif // !CALC_NUMBER_H