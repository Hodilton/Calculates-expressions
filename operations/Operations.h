#ifndef OPERATIONS_H
#define OPERATIONS_H

template <typename T>
class IOperator {
public:
    virtual T apply(T& left, const T& right) const = 0;
    virtual char symbol() const = 0;
    virtual ~IOperator() = default;
};

template <typename T>
class PlusOperator : public IOperator<T> {
public:
    T apply(T& left, const T& right) const override {
        return left + right;
    }
    char symbol() const override {
        return '+';
    }
};

template <typename T>
class MinusOperator : public IOperator<T> {
public:
    T apply(T& left, const T& right) const override {
        return left - right;
    }
    char symbol() const override {
        return '-';
    }
};

template <typename T>
class MultiplyOperator : public IOperator<T> {
public:
    T apply(T& left, const T& right) const override {
        return left * right;
    }
    char symbol() const override {
        return '*';
    }
};

template <typename T>
class DivideOperator : public IOperator<T> {
public:
    T apply(T& left, const T& right) const override {
        return left / right;
    }
    char symbol() const override {
        return '/';
    }
};

#endif // !OPERATIONS_H