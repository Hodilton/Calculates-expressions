#include "./Calculator.h"
#include "./file_work/file_processor.h"

#include <iostream>

int main() {
	auto expsn = file_work::File<Expression<int>>::read(
		file_work::PathParams("data", "expression", "json"));

    for (const auto& pair : expsn) {
        const auto& expression = pair.first;
        const auto& data = pair.second;

        //std::cout << expression << std::endl;

        Calculator<int> calculator(expression, data);
        const auto result = calculator.solve();

        std::cout << result;
    }

	return 0;
}