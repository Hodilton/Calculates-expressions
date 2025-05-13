#include "./src/Calculator.h"

int main() {
    calc::types::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::Calculator<double> calc;

    auto result = calc.evaluate("-(-x + 5) + 5 + sqrt2(x + 9, 2)", variables);

    std::cout << "Result: " << (result ? std::to_string(*result) : "no value.") << std::endl;

    return 0;
}