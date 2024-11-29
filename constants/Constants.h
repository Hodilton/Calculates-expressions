#ifndef CALC_CONSTANTS_H
#define CALC_CONSTANTS_H

#include "./IConstant.h"

#include <numbers>

namespace calc::constants {

    template <typename T>
    class PiConstant : public IConstant<T> {
    public:
        T value() const override { return static_cast<T>(std::numbers::pi); }
        std::string name() const override { return "pi"; }
    };

    template <typename T>
    class EConstant : public IConstant<T> {
    public:
        T value() const override { return static_cast<T>(std::numbers::e); }
        std::string name() const override { return "e"; }
    };
}

#endif // !CALC_CONSTANTS_H