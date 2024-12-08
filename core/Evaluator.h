#ifndef CALC_EVALUATOR_H
#define CALC_EVALUATOR_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"
#include "../constants/ConstantFactory.h"
#include "../number/Number.h"

#include "./Parser.h"
#include "./Types.h"

#include <map>
#include <stack>
#include <optional>
#include <algorithm> 
#include <stdexcept>
#include <iostream>

namespace calc {

    template <typename T>
    class Evaluator {
    private:
        operators::OperatorFactory<T> operatorFactory;
        functions::FunctionFactory<T> functionFactory;
        constants::ConstantFactory<T> constantFactory;
        number::Number<T> number;

        Parser<T> parser;

    public:
        std::optional<T> evaluate(const std::string& expression, const types::VariableMap<T>& variables) {
            std::stack<T> values;
            std::stack<char> operators;
            std::vector<std::string> tokens;

            parser.setVariables(variables);

            tokens = parser.parse(expression);

            for (auto it = tokens.begin(); it != tokens.end(); ++it) {
                const std::string& token = *it;

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
                    while (!operators.empty() &&
                            precedence(operators.top()) >= precedence(token[0])) {
                        applyTopOperator(values, operators.top());
                        operators.pop();
                    }
                    operators.push(token[0]);
                }
                else if (functionFactory.isFunction(token)) {
                    std::vector<T> args;

                    for (it += 2; it != tokens.end() && *it != ")"; ++it) {
                        auto argValue = evaluate(*it, variables);

                        if (!argValue) {
                            return std::nullopt;
                        }

                        args.push_back(*argValue);
                    }

                    //auto arg1Expr = *(std::next(it, 2));
                    //auto arg2Expr = *(std::next(it, 4));
                    //it = std::next(it, 5);

                    //auto arg1 = evaluate(arg1Expr, variables);
                    //auto arg2 = evaluate(arg2Expr, variables);

                    //if (!arg1 || !arg2) {
                    //    return std::nullopt;
                    //}

                    values.push(functionFactory.getFunction(token)->apply(args));
                }
                else if (constantFactory.isConstant(token)) {
                    values.push(constantFactory.getConstant(token)->value());
                }
                else if (variables.find(token) != variables.end()) {
                    values.push(variables.at(token));
                }
                else if (number.isNumber(token)) {
                    values.push(number.convertToNumber(token));
                }             
                //else {
                //    throw std::runtime_error("Variable not found: " + token + ".");
                //}
            }

            while (!operators.empty()) {
                applyTopOperator(values, operators.top());
                operators.pop();
            }

            if (!values.empty()) {
                return values.top();
            }
            else {
                return std::nullopt;
            }
        }

    private:
        void applyTopOperator(std::stack<T>& values, char op) {
            T right = values.top(); values.pop();
            T left = values.top(); values.pop();
            values.push(operatorFactory.getOperator(op)->apply(left, right));
        }

        int precedence(char op) const {
            return (op == '+' || op == '-')
                ? 1
                : (op == '*' || op == '/')? 2 : 0;
        }
    };
}

#endif // !CALC_EVALUATOR_H