#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./IFunction.h"

#include <cmath>
#include <iostream>

template <typename T>
class SqrtFunction : public IFunction<T> {
public:
    T apply(const std::vector<T>& args) const override {
        if (args.size() < 2) {
            throw std::invalid_argument("Sqrt function requires exactly one argument.");
        }
        if (args[0] < T(0)) {
            throw std::domain_error("Square root is not defined for negative numbers.");
        }
        return std::sqrt(args[0]);
    }
};

#endif // !FUNCTIONS_H