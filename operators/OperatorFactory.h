#ifndef OPERATOR_FACTORY_H
#define OPERATOR_FACTORY_H

#include "./Operators.h"

#include <string>
#include <map>

#include <stdexcept>
#include <memory>

namespace calc {

    template <typename T>
    class OperatorFactory {
    public:
        OperatorFactory() {
            operators['+'] = std::make_unique<AdditionOperator<T>>();
            operators['-'] = std::make_unique<SubtractionOperator<T>>();
            operators['*'] = std::make_unique<MultiplicationOperator<T>>();
            operators['/'] = std::make_unique<DivisionOperator<T>>();
        }

        IOperator<T>* getOperator(char symbol) const {
            auto it = operators.find(symbol);
            if (it != operators.end()) {
                return it->second.get();
            }
            throw std::runtime_error("Unknown operator: " + std::string(1, symbol));
        }

        bool isOperator(char symbol) const {
            return operators.find(symbol) != operators.end();
        }

    private:
        std::map<char, std::unique_ptr<IOperator<T>>> operators;
    };
}

#endif // !OPERATOR_FACTORY_H