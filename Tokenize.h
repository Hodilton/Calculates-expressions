//#pragma once
//
//#include <vector>
//#include <string>
//
//class Tokenize {
//	static std::vector<std::string> tokenize(const std::string& expression) {
//
//		std::vector<std::string> tokens;
//		std::string currentToken;
//
//		for (char ch : expression) {
//			if (std::isspace(ch)) {
//				continue;
//			}
//			else if (ch == '(' || ch == ')') {
//
//				if (!currentToken.empty()) {
//
//					tokens.push_back(currentToken);
//
//					currentToken.clear();
//
//				}
//
//				tokens.push_back(std::string(1, ch)); // Добавляем скобку как токен
//
//			}
//
//			else if (isOperator(ch)) {
//
//				if (!currentToken.empty()) {
//
//					tokens.push_back(currentToken);
//
//					currentToken.clear();
//
//				}
//
//				tokens.push_back(std::string(1, ch)); // Добавляем оператор как токен
//
//			}
//
//			else {
//
//				currentToken += ch;
//
//			}
//
//		}
//
//		if (!currentToken.empty()) {
//
//			tokens.push_back(currentToken);
//
//		}
//
//		return tokens;
//
//	}
//};