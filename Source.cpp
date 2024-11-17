#include "./core/Evaluator.h"

#include <iostream>

int main() {
    calc::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::Evaluator<double> eval;

    try {
        auto result = eval.evaluate("5 + sqrt((x + y) / 3 + 2 * y, 2) + 5", variables);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}