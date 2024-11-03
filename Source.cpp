#include "./expression/ExpressionEvaluator.h"

#include <iostream>

int main() {
    calc::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::ExpressionEvaluator<double> evaluator;

    try {
        double result = evaluator.evaluate("(x + y) / 3 + 2 * y", variables);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}