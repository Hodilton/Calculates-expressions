#ifndef CALC_TYPES_H
#define CALC_TYPES_H

#include <map>
#include <string>

namespace calc::types {
    template<typename T>
    using FunctionMap = std::map<std::string, std::string>;

    template<typename T>
    using VariableMap = std::map<std::string, T>;

    template<typename T>
    using ExpressionMap = std::map<std::string, VariableMap<T>>;
}

#endif // !CALC_TYPES_H