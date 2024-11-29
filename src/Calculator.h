#ifndef CALC_H
#define CALC_H

#include "../core/Evaluator.h"

namespace calc {

    class Calculator {
    public:
        template <typename T>
        std::optional<T> evaluate(const std::string& expression, const types::VariableMap<T>& variables) const {
            calc::Evaluator<T> eval;

            try {
                auto result = eval.evaluate(expression, variables);
                return result;
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return std::nullopt;
            }         
        }
    };
}

#endif // !CALC_H