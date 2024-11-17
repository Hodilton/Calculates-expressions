#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"
#include "../number/Number.h"

#include "./Types.h"

#include <string>
#include <vector>
#include <optional>
#include <stack>
#include <cctype>

namespace calc {

    template <typename T>
    class ExpressionParser {
    private:
        operators::OperatorFactory<T> operatorFactory;
        functions::FunctionFactory<T> functionFactory;
        numbers::Number<T> number;

        std::optional<VariableMap<T>> variables;

    public:
        ExpressionParser() : operatorFactory(), functionFactory(), variables(std::nullopt) {}
        ExpressionParser(VariableMap<T>* varMap) : operatorFactory(), functionFactory(), variables(varMap) {}

        std::vector<std::string> parse(const std::string& expression) const {
            std::vector<std::string> tokens;
            std::string currentToken;
            std::stack<char> parenthesesStack;

            for (size_t i = 0; i < expression.length(); ++i) {
                char ch = expression[i];

                if (isSpace(ch)) {
                    continue;
                }

                if (ch == '(') {
                    addCurrentToken(tokens, currentToken);
                    parenthesesStack.push('(');

                    if (!tokens.empty() && functionFactory.isFunction(tokens.back())) {
                        auto [arg1, arg2] = extractFunctionArgs(expression, i);

                        tokens.push_back("(");
                        tokens.push_back(arg1);
                        tokens.push_back(",");
                        tokens.push_back(arg2);
                        tokens.push_back(")");
                        i += arg1.length() + arg2.length() + 2; // Пропускаем обработанные символы (запятая и закрывающая скобка).
                        parenthesesStack.pop(); // Закрывающая скобка уже обработана.

                        continue;
                    }
                 
                    tokens.push_back("(");                                  
                }
                else if (ch == ')') {
                    addCurrentToken(tokens, currentToken);
                    tokens.push_back(")");
                    if (parenthesesStack.empty() || parenthesesStack.top() != '(') {
                        throw std::runtime_error("Mismatched parentheses in the expression.");
                    }
                    parenthesesStack.pop();
                }
                else if (ch == ',') {
                    addCurrentToken(tokens, currentToken);
                    tokens.push_back(",");
                }
                else if (operatorFactory.isOperator(ch)) {
                    addCurrentToken(tokens, currentToken);
                    tokens.push_back(std::string(1, ch));
                }
                else {
                    currentToken += ch;
                }
            }

            addCurrentToken(tokens, currentToken);

            if (!parenthesesStack.empty()) {
                throw std::runtime_error("Mismatched parentheses in the expression.");
            }

            return tokens;
        }

        void setVariables(const VariableMap<T>& varMap) {
            variables = varMap;
        }

    private:
        bool isSpace(char ch) const {
            return std::isspace(static_cast<unsigned char>(ch));
        }

        void addCurrentToken(std::vector<std::string>& tokens, std::string& currentToken) const {
            if (!currentToken.empty()) {
                validateToken(currentToken);
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }

        void validateToken(const std::string& token) const {
            if (token == "(" || token == ")" || token == ",") {
                return;
            }
            else if (operatorFactory.isOperator(token[0])) {
                return;
            }
            else if (number.isNumber(token)) {
                return;
            }
            else if (functionFactory.isFunction(token)) {
                return;
            }
            else if (variables && variables->count(token) > 0) {
                return;
            }
            else {
                throw std::runtime_error("Invalid function or token found: " + token + ".");
            }
        }

        std::pair<std::string, std::string> extractFunctionArgs(const std::string& expression, size_t startIdx) const {
            size_t start = expression.find('(', startIdx);

            if (start == std::string::npos) {
                throw std::invalid_argument("Function must have brackets and arguments.");
            }

            start += 1; // Переходим за открывающую скобку.
            std::stack<char> brackets;
            std::string beforeComma, afterComma;
            bool foundComma = false;

            for (size_t i = start; i < expression.size(); ++i) {
                char ch = expression[i];

                if (ch == '(') {
                    brackets.push(ch);
                }
                else if (ch == ')') {
                    if (!brackets.empty()) {
                        brackets.pop();
                    }
                    else {
                        if (!foundComma) {
                            throw std::invalid_argument("Function must have arguments separated by a comma.");
                        }
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
                throw std::invalid_argument("Function must have two arguments separated by a comma.");
            }

            return { beforeComma, afterComma };
        }
    };
}

#endif // !EXPRESSION_PARSER_H
