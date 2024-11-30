#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include "../operators/OperatorFactory.h"
#include "../functions/FunctionFactory.h"
#include "../constants/ConstantFactory.h"
#include "../number/Number.h"

#include "./Types.h"

#include <string>
#include <vector>
#include <stack>
#include <optional>
#include <cctype>
#include <unordered_set>

namespace calc {

    template <typename T>
    class Parser {
    private:
        operators::OperatorFactory<T> operatorFactory;
        functions::FunctionFactory<T> functionFactory;
        constants::ConstantFactory<T> constantFactory;
        number::Number<T> number;

        std::optional<types::VariableMap<T>> variables;

    public:
        Parser() : operatorFactory(), functionFactory(), constantFactory(), number(), variables(std::nullopt) {}
        Parser(types::VariableMap<T>* variables) : operatorFactory(), functionFactory(), constantFactory(), number(), variables(variables) {}

        std::vector<std::string> parse(const std::string& expression) const {
            std::vector<std::string> tokens;
            std::string currentToken;

            std::stack<char> brackets;
            std::stack<unsigned int> unaryMinusStack;

            for (auto it = expression.begin(); it != expression.end(); ++it) {
                char ch = *it;

                if (isSpace(ch)) {
                    continue;
                }

                if (ch == '(') {
                    brackets.push('(');
                    addCurrentToken(tokens, currentToken, unaryMinusStack, brackets);
                   

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
                    addCurrentToken(tokens, currentToken, unaryMinusStack, brackets);
                    tokens.push_back(")");

                    if (brackets.empty() || brackets.top() != '(') {
                        throw std::runtime_error("Mismatched brackets in the expression.");
                    }

                    brackets.pop();
                }
                else if (operatorFactory.isOperator(ch)) {
                    addCurrentToken(tokens, currentToken, unaryMinusStack, brackets);

                    if (tokens.empty() && ch != '-') {
                        throw std::runtime_error("Expression cannot start with an operator: " + std::string(1, ch));
                    }

                    if (tokens.empty() || operatorFactory.isOperator(tokens.back()[0])) {
                        throw std::runtime_error("Expression cannot end with an operator.");
                    }

                    if (ch == '-' && isUnaryMinusContext(tokens)) {
                        handleUnaryMinus(tokens, currentToken, unaryMinusStack, brackets);
                        continue;
                    }

                    if (!tokens.empty() && operatorFactory.isOperator(tokens.back()[0])) {
                        throw std::runtime_error("Consecutive operators are not allowed: " + tokens.back() + ch);
                    }
         
                    tokens.push_back(std::string(1, ch));
                }
                else {
                    currentToken += ch;
                }
            }

            addCurrentToken(tokens, currentToken, unaryMinusStack, brackets);

            if (!brackets.empty()) {
                throw std::runtime_error("Mismatched brackets in the expression.");
            }

            return tokens;
        }

        void setVariables(const types::VariableMap<T>& variables) {
            this->variables = variables;
        }

    private:
        bool isSpace(char ch) const {
            return std::isspace(static_cast<unsigned char>(ch));
        }

        void addCurrentToken(
            std::vector<std::string>& tokens,
            std::string& currentToken,
            std::stack<unsigned int>& unaryMinusStack,
            const std::stack<char>& brackets
        ) const {
            if (!currentToken.empty()) {
                validateToken(currentToken);
                tokens.push_back(currentToken);
                currentToken.clear();
            }

            while (!unaryMinusStack.empty() && (unaryMinusStack.top() > brackets.size())) {
                tokens.push_back(")");
                unaryMinusStack.pop();
            }
        }


        void validateToken(const std::string& token) const {
            if (token == "(" || token == ")" || token == ",") {
                return;
            }
            else if (functionFactory.isFunction(token)) {
                return;
            }        
            else if (operatorFactory.isOperator(token[0])) {
                return;
            }
            else if (constantFactory.isConstant(token)) {
                return;
            }              
            else if (variables && variables->count(token) > 0) {
                return;
            }
            else if (number.isNumber(token)) {
                return;
            }
            else {
                throw std::runtime_error("Invalid function or token found: " + token + ".");
            }
        }

        bool isUnaryMinusContext(const std::vector<std::string>& tokens) const {
            if (tokens.empty()) {
                return true;
            }

            const std::string& lastToken = tokens.back();
            static const std::unordered_set<std::string> operators = { "(", "," };

            return operators.find(lastToken) != operators.end() || operatorFactory.isOperator(lastToken[0]);
        }

        void handleUnaryMinus(
            std::vector<std::string>& tokens,
            std::string& currentToken,
            std::stack<unsigned int>& unaryMinusStack,
            const std::stack<char>& brackets
        ) const {
            addCurrentToken(tokens, currentToken, unaryMinusStack, brackets);

            tokens.push_back("(");
            tokens.push_back("0");
            tokens.push_back("-");

            unaryMinusStack.push(brackets.size() + 1);
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
                    if (foundComma) {
                        throw std::invalid_argument("Too many commas in function arguments.");
                    }

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