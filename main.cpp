#include "./src/Calculator.h"

int main() {
    calc::types::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::Calculator calc;

    auto result = calc.evaluate<double>("5 + sqrt((x + y) / 3 + 2 * y, 2) + 5", variables);

    std::cout << "Result: " << (result ? std::to_string(*result) : "no value.") << std::endl;

    return 0;
}