#ifndef OPERATORS_H
#define OPERATORS_H

#include "./IOperator.h"

#include <stdexcept>

template <typename T>
class AdditionOperator : public IOperator<T> {
public:
    T apply(const T& left, const T& right) const override { return left + right; }
    char symbol() const override { return '+'; }
};

template <typename T>
class SubtractionOperator : public IOperator<T> {
public:
    T apply(const T& left, const T& right) const override { return left - right; }
    char symbol() const override { return '-'; }
};

template <typename T>
class MultiplicationOperator : public IOperator<T> {
public:
    T apply(const T& left, const T& right) const override { return left * right; }
    char symbol() const override { return '*'; }
};

template <typename T>
class DivisionOperator : public IOperator<T> {
public:
    T apply(const T& left, const T& right) const override {
        if (right == T(0)) {
            throw std::runtime_error("Division by zero error.");
        }
        return left / right;
    }
    char symbol() const override { return '/'; }
};

#endif // !OPERATORS_H