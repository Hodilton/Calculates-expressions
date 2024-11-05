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

            for (const auto& token : tokens) {
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
                    auto remainingExpression = expression.substr(expression.find(token) + token.length());
                    auto [arg1Expr, arg2Expr] = extractFunctionArgs(remainingExpression, token);

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

        std::pair<std::string, std::string> extractFunctionArgs(const std::string& expression,
                                                                   const std::string& function) {
            std::size_t start = expression.find('(');

            if (start == std::string::npos) {
                throw std::invalid_argument("The function "
                    + function
                    + " must have brackets: "
                    + function + "(x, y).");
            }

            start += 1;
            std::stack<char> brackets;
            std::string beforeComma, afterComma;
            bool foundComma = false;

            for (std::size_t i = start; i < expression.size(); ++i) {
                char ch = expression[i];

                if (ch == '(') {
                    brackets.push(ch);
                }
                else if (ch == ')') {
                    if (!brackets.empty()) {
                        brackets.pop();
                    }
                    else {
                        break;
                    }
                }
                else if (ch == ',' && brackets.empty()) {
                    foundComma = true;
                    continue;
                }

                if (foundComma) {
                    afterComma += ch;
                }
                else {
                    beforeComma += ch;
                }
            }

            if (!foundComma) {
                throw std::invalid_argument("The function "
                    + function
                    + " must have arguments: "
                    + function + "(x, y).");
            }

            return { beforeComma, afterComma };
        }
    };
}

#endif // !EXPRESSION_EVALUATOR_H