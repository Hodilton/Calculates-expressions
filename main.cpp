#include "./src/Calculator.h"

int main() {
    calc::types::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::Calculator calc;

    //auto result = calc.evaluate<double>("5 + sqrt((x + y) / 3 + 2 * y, 2) + 5 + pi", variables);
    auto result = calc.evaluate<double>("-(-x + 5) + 5 + sqrt2(x + 9, 2)", variables);

    std::cout << "Result: " << (result ? std::to_string(*result) : "no value.") << std::endl;

    return 0;
}