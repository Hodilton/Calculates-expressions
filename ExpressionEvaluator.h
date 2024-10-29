#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include "./operations/Operations.h"
#include "./Types.h"

#include <vector>
#include <stack>
#include <sstream>

namespace calc {

    template <typename T>
    class ExpressionEvaluator {
    public:
        T evaluate(const std::string& expression, const Letters<T>& letters) {
            std::stack<T> values;
            std::stack<char> ops;

            auto tokens = tokenize(expression);

            for (const auto& token : tokens) {
                if (token == "(") {
                    ops.push('(');
                    continue;
                }

                if (token == ")") {
                    while (!ops.empty() && ops.top() != '(') {
                        char op = ops.top();
                        ops.pop();
                        applyTopOperator(values, op);
                    }
                    ops.pop();  // Удаляем '(' из стека
                    continue;
                }

                if (isOperator(token[0])) {
                    while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                        char op = ops.top();
                        ops.pop();
                        applyTopOperator(values, op);
                    }
                    ops.push(token[0]);
                    continue;
                }

                if (letters.find(token) != letters.end()) {
                    values.push(letters.at(token));
                }
                else {
                    throw std::runtime_error("Variable '" + token + "' not found in the provided data.");
                }
            }

            while (!ops.empty()) {
                char op = ops.top();
                ops.pop();
                applyTopOperator(values, op);
            }

            return values.top();
        }

        void addOperator(std::shared_ptr<IOperator<T>> op) {
            operators[op->symbol()] = op;
        }

    private:
        std::map<char, std::shared_ptr<IOperator<T>>> operators;

        std::vector<std::string> tokenize(const std::string& expression) {

            std::vector<std::string> tokens;
            std::string currentToken;

            for (char ch : expression) {
                if (std::isspace(ch)) {
                    continue;
                }
                else if (ch == '(' || ch == ')') {

                    if (!currentToken.empty()) {

                        tokens.push_back(currentToken);

                        currentToken.clear();

                    }

                    tokens.push_back(std::string(1, ch)); // Добавляем скобку как токен

                }

                else if (isOperator(ch)) {

                    if (!currentToken.empty()) {

                        tokens.push_back(currentToken);

                        currentToken.clear();

                    }

                    tokens.push_back(std::string(1, ch)); // Добавляем оператор как токен

                }

                else {

                    currentToken += ch;

                }

            }

            if (!currentToken.empty()) {

                tokens.push_back(currentToken);

            }

            return tokens;

        }

        void applyTopOperator(std::stack<T>& values, char op) {
            if (values.size() < 2) throw std::runtime_error("Invalid expression");

            T right = values.top();
            values.pop();
            T left = values.top();
            values.pop();

            if (operators.find(op) == operators.end()) {
                throw std::runtime_error("Unknown operator: " + std::string(1, op));
            }

            values.push(operators[op]->apply(left, right));
        }

        bool isOperator(char ch) const {
            return operators.find(ch) != operators.end();
        }

        int precedence(char op) const {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            return 0;
        }
    };

}

#endif // !EXPRESSIONEVALUATOR_H