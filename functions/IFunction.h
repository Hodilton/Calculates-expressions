#ifndef CALC_IFUNCTION_H
#define CALC_IFUNCTION_H

#include <vector>

namespace calc::functions {

    template <typename T>
    class IFunction {
    public:
        virtual T apply(const std::vector<T>& args) const = 0;
        virtual ~IFunction() = default;
    };
}

#endif // !CALC_IFUNCTION_H