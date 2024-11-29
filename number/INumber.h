#ifndef CALC_INUMBER_H
#define CALC_INUMBER_H

#include <string>

namespace calc::number {

    template <typename T>
    class INumber {
    public:
        virtual bool isNumber(const std::string& token) const = 0;
        virtual T convertToNumber(const std::string& token) const = 0;
        virtual ~INumber() = default;
    };
}

#endif // !CALC_INUMBER_H