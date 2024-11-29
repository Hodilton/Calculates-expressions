#ifndef CALC_ICONSTANT_H
#define CALC_ICONSTANT_H

#include <string>

namespace calc::constants {

    template <typename T>
    class IConstant {
    public:
        virtual T value() const = 0;
        virtual std::string name() const = 0;
        virtual ~IConstant() = default;
    };
}

#endif // !CALC_ICONSTANT_H