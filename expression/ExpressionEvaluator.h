#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"
#include "../number/Number.h"

#include "./ExpressionParser.h"
#include "./Types.h"

#include <stack>
#include <map>
#include <stdexcept>
#include <algorithm> 

namespace calc {

    template <typename T>
    class ExpressionEvaluator {
    private:
        OperatorFactory<T> operatorFactory;
        FunctionFactory<T> functionFactory;
        Number<T> number;

        ExpressionParser<T> parser;

    public:
        T evaluate(const std::string& expression, const VariableMap<T>& variables) {
            std::stack<T> values;
            std::stack<char> operators;

            parser.setVariables(variables);
            auto tokens = parser.parse(expression);


            for (size_t i = 0; i < tokens.size(); ++i) {
                std::string token = tokens[i];

                if (token == "(") {
                    operators.push('(');
                }
                else if (token == ")") {
                    while (!operators.empty() && operators.top() != '(') {
                        applyTopOperator(values, operators.top());
                        operators.pop();
                    }
                    operators.pop();
                }
                else if (operatorFactory.isOperator(token[0])) {
                    while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                        applyTopOperator(values, operators.top());
                        operators.pop();
                    }
                    operators.push(token[0]);
                }
                else if (functionFactory.isFunction(token)) {
                    auto arg1Expr = tokens[i + 2];
                    auto arg2Expr = tokens[i + 4];
                    i += 5;

                    T arg1 = evaluate(arg1Expr, variables);
                    T arg2 = evaluate(arg2Expr, variables);

                    values.push(functionFactory.getFunction(token)->apply({arg1, arg2}));
                }
                else if (number.isNumber(token)) {
                    values.push(number.convertToNumber(token));
                }
                else if (variables.find(token) != variables.end()) {
                    values.push(variables.at(token));
                }
                else {
                    throw std::runtime_error("Variable not found: " + token + ".");
                }
            }

            while (!operators.empty()) {
                applyTopOperator(values, operators.top());
                operators.pop();
            }

            return values.top();
        }

    private:
        void applyTopOperator(std::stack<T>& values, char op) {
            T right = values.top(); values.pop();
            T left = values.top(); values.pop();
            values.push(operatorFactory.getOperator(op)->apply(left, right));
        }

        int precedence(char op) const {
            return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
        }
    };
}

#endif // !EXPRESSION_EVALUATOR_H