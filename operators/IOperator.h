#ifndef CALC_IOPERATOR_H
#define CALC_IOPERATOR_H

namespace calc::operators {

    template <typename T>
    class IOperator {
    public:
        virtual T apply(const T& left, const T& right) const = 0;
        virtual char symbol() const = 0;
        virtual ~IOperator() = default;
    };
}

#endif // !CALC_IOPERATOR_H