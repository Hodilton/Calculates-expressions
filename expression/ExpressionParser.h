#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"

#include <string>
#include <vector>
#include <cctype>

namespace calc {

    template <typename T>
    class ExpressionParser {
    public:
        ExpressionParser(): operatorFactory(), functionFactory() {}

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

    private:
        OperatorFactory<T> operatorFactory;
        FunctionFactory<T> functionFactory;

        bool isSpace(char ch) const {
            return std::isspace(static_cast<unsigned char>(ch));
        }

        void addCurrentToken(std::vector<std::string>& tokens, std::string& currentToken) const {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
    };
}

#endif // !EXPRESSION_PARSER_H