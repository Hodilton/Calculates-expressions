#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"
#include "../number/Number.h"

#include "./Types.h"

#include <string>
#include <vector>
#include <stack>
#include <optional>
#include <cctype>

namespace calc {

    template <typename T>
    class Parser {
    private:
        operators::OperatorFactory<T> operatorFactory;
        functions::FunctionFactory<T> functionFactory;
        numbers::Number<T> number;

        std::optional<VariableMap<T>> variables;

    public:
        Parser() : operatorFactory(), functionFactory(), variables(std::nullopt) {}
        Parser(VariableMap<T>* variables) : operatorFactory(), functionFactory(), variables(variables) {}

        std::vector<std::string> parse(const std::string& expression) const {
            std::vector<std::string> tokens;
            std::string currentToken;

            std::stack<char> brackets;

            for (auto it = expression.begin(); it != expression.end(); ++it) {
                char ch = *it;

                if (isSpace(ch)) {
                    continue;
                }

                if (ch == '(') {
                    addCurrentToken(tokens, currentToken);
                    brackets.push('(');

                    if (!tokens.empty() && functionFactory.isFunction(tokens.back())) {
                        auto [arg1, arg2] = extractFunctionArgs(it, expression.end());

                        tokens.push_back("(");
                        tokens.push_back(arg1);
                        tokens.push_back(",");
                        tokens.push_back(arg2);
                        tokens.push_back(")");

                        brackets.pop();
                        continue;
                    }
                 
                    tokens.push_back("(");                                  
                }
                else if (ch == ')') {
                    addCurrentToken(tokens, currentToken);
                    tokens.push_back(")");

                    if (brackets.empty() || brackets.top() != '(') {
                        throw std::runtime_error("Mismatched brackets in the expression.");
                    }

                    brackets.pop();
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

            if (!brackets.empty()) {
                throw std::runtime_error("Mismatched brackets in the expression.");
            }

            return tokens;
        }

        void setVariables(const VariableMap<T>& variables) {
            this->variables = variables;
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

        std::pair<std::string, std::string> extractFunctionArgs(
            std::string::const_iterator& it,
            std::string::const_iterator end
        ) const {
            if (it == end || *it != '(') {
                throw std::invalid_argument("Function must have brackets and arguments.");
            }

            std::stack<char> brackets;
            std::string beforeComma, afterComma;
            bool foundComma = false;

            for (++it; it != end; ++it) {
                char ch = *it;

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

            if (!foundComma || beforeComma.empty() || afterComma.empty()) {
                throw std::invalid_argument("Function must have two arguments separated by a comma.");
            }

            return { beforeComma, afterComma };
        }
    };
}

#endif // !CALC_PARSER_H