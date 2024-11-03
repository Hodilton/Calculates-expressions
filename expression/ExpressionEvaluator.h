#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"

#include "./ExpressionParser.h"
#include "./Types.h"

#include <stack>
#include <map>

#include <stdexcept>
#include <sstream>
#include <algorithm> 

namespace calc {

    template <typename T>
    class ExpressionEvaluator {
    public:
        T evaluate(const std::string& expression, const VariableMap<T>& variables) {
            std::stack<T> values;
            std::stack<char> ops;
            auto tokens = parser.parse(expression);

            for (const auto& token : tokens) {
                 if (token == "(") {
                    ops.push('(');
                }
                else if (token == ")") {
                    while (!ops.empty() && ops.top() != '(') {
                        applyTopOperator(values, ops.top());
                        ops.pop();
                    }
                    ops.pop();
                }
                else if (operatorFactory.isOperator(token[0])) {
                    while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                        applyTopOperator(values, ops.top());
                        ops.pop();
                    }
                    ops.push(token[0]);
                }
                else if (functionFactory.isFunction(token)) {

                    //values.push(functionFactory.getFunction(token)->apply(args));
                }
                else if (isNumber(token)) {
                    values.push(convertToNumber(token));
                }
                else if (variables.find(token) != variables.end()) {
                    values.push(variables.at(token));
                }
                else {
                    throw std::runtime_error("Variable '" + token + "' not found.");
                }
            }

            while (!ops.empty()) {
                applyTopOperator(values, ops.top());
                ops.pop();
            }

            return values.top();
        }

    private:
        OperatorFactory<T> operatorFactory;
        FunctionFactory<T> functionFactory;
        ExpressionParser<T> parser;

        void applyTopOperator(std::stack<T>& values, char op) {
            T right = values.top(); values.pop();
            T left = values.top(); values.pop();
            values.push(operatorFactory.getOperator(op)->apply(left, right));
        }

        int precedence(char op) const {
            return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
        }

        bool isNumber(const std::string& token) const {
            std::istringstream iss(token);
            double dummy;
            char extra;
            return (iss >> dummy) && !(iss >> extra);
        }

        T convertToNumber(const std::string& token) const {
            T value;
            std::istringstream(token) >> value;
            return value;
        }
    };
}

#endif // !EXPRESSION_EVALUATOR_H