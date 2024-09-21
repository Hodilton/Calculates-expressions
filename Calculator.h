#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "./ExpressionEvaluator.h"

#include<map>
#include<string>

template<typename T>
class Calculator {
public:
    Calculator(const std::string& expression, const Letters<T>& letters)
        : expression(expression), letters(letters) {}

    T solve() {
        ExpressionEvaluator<T> evaluator;

        evaluator.addOperator(std::make_shared<PlusOperator<T>>());
        evaluator.addOperator(std::make_shared<MinusOperator<T>>());
        evaluator.addOperator(std::make_shared<MultiplyOperator<T>>());
        evaluator.addOperator(std::make_shared<DivideOperator<T>>());

        return evaluator.evaluate(expression, letters);
    }

private:
    std::string expression;
    std::map<std::string, T> letters;
};

#endif // !TASK_1_CALCULATOR_H