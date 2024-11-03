#include "./expression/ExpressionEvaluator.h"

#include <iostream>

int main() {
    calc::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::ExpressionEvaluator<double> evaluator;

    try {
        double result = evaluator.evaluate("(x + y) / 3 + sqrt(27, 3)", variables);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    /*auto expsn = file_work::File<Expression<int>>::read(
    file_work::PathParams("data", "expression", "json"));

    for (const auto& pair : expsn) {
    const auto& expression = pair.first;
    const auto& data = pair.second;

    std::cout << expression << std::endl;

    Calculator<int> calculator(expression, data);
    const auto result = calculator.solve();

    std::cout << result;
    }*/

    return 0;
}