#ifndef IFUNCTION_H
#define IFUNCTION_H

#include <vector>

template <typename T>
class IFunction {
public:
    virtual T apply(const std::vector<T>& args) const = 0;

    virtual ~IFunction() = default;
};

#endif // !IFUNCTION_H