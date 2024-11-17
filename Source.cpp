#include "./core/Evaluator.h"

int main() {
    calc::VariableMap<double> variables = { {"x", 27}, {"y", 3} };
    calc::Evaluator<double> eval;

    auto result = eval.evaluate("5 + sqrt((x + y) / 3 + 2 * y, 2) + 5", variables);

    std::cout << "Result: " << (result
        ? std::to_string(*result)
        : "no value.") << std::endl;



    return 0;
}