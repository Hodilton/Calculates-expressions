#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <string>

namespace calc {

    template<typename T>
    using VariableMap = std::map<std::string, T>;

    template<typename T>
    using ExpressionMap = std::map<std::string, VariableMap<T>>;
}

#endif // !TYPES_H