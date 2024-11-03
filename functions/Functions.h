#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./IFunction.h"

#include <cmath>
#include <iostream>

template <typename T>
class SqrtFunction : public IFunction<T> {
public:
    T apply(const std::vector<T>& args) const override {
        
        std::cout << "Sqrt function called with arguments: ";
        for (const auto& ch : args) {
            std::cout << ch;
        } std::cout << std::endl;

        if (args.empty()) {
            throw std::runtime_error("Sqrt function requires at least one argument.");
        }
        if (args[0] < 0) {
            throw std::runtime_error("Cannot compute the square root of a negative number.");
        }

        return std::sqrt(args[0]);
    }
};

#endif // !FUNCTIONS_H