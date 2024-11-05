#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"
#include "../number/Number.h"

#include "./Types.h"

#include <string>
#include <vector>
#include <optional>

#include <cctype>   

namespace calc {

    template <typename T>
    class ExpressionParser {
    private:
        OperatorFactory<T> operatorFactory;
        FunctionFactory<T> functionFactory;
        Number<T> number;

        std::optional<VariableMap<T>> variables;

    public:
        ExpressionParser(): operatorFactory(), functionFactory(), variables(std::nullopt) {}
        ExpressionParser(VariableMap<T>* varMap) : operatorFactory(), functionFactory(), variables(varMap) {}

        std::vector<std::string> parse(const std::string& expression) const {
            std::vector<std::string> tokens;
            std::string currentToken;

            int parenthesesCount = 0;

            for (char ch : expression) {
                if (isSpace(ch)) {
                    continue;
                }
                else if (ch == '(') {
                    addCurrentToken(tokens, currentToken);
                    tokens.push_back(std::string(1, ch));
                    parenthesesCount++;
                }
                else if (ch == ')') {
                    addCurrentToken(tokens, currentToken);
                    tokens.push_back(std::string(1, ch));
                    parenthesesCount--;
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

            if (parenthesesCount != 0) {
                throw std::runtime_error("The brackets are incorrectly placed in the expression.");
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
                throw std::runtime_error("Invalid function found: " + token + ".");
            }
        }
    };
}

#endif // !EXPRESSION_PARSER_H