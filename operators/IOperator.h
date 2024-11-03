#ifndef IOPERATOR_H
#define IOPERATOR_H

template <typename T>
class IOperator {
public:
    virtual T apply(const T& left, const T& right) const = 0;
    virtual char symbol() const = 0;

    virtual ~IOperator() = default;
};

#endif // !IOPERATOR_H