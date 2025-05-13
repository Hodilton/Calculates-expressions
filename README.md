# Expression Calculator

The algorythm for evaluating mathematical expressions with variables, functions, and operators.

## Features

- Evaluates complex mathematical expressions
- Supports constants (e.g., `e`, `pi`)
- Supports variables (e.g., `x`, `y`)
- Built-in functions (e.g., `pow`, `sin`)
- Handles operator precedence and parentheses
- Unary minus support
- Type-safe templated design (works with `double`, `float`, etc.)
## Examples
1. Basic arithmetic
```cpp
calc.evaluate("2 + 2 * 2", {});  // Returns 6
```
2. With variables
```cpp
calc.evaluate("pow(x, 2)", {{"x", 4}});  // Returns 16
```
3. Complex expressions
```cpp
calc.evaluate("sqrt(pow(x, 2), 2)", {{"x", 4}});  // Returns 4
```
4. Unary minus
```cpp
calc.evaluate("-(3 + 5) + pow(-2, 2)", {});  // Returns -4
```
## How to Work
```cpp
#include "Calculator.h"

int main() {
    calc::types::VariableMap<double> variables = {{"x", 27}, {"y", 3}};
    calc::Calculator<double> calc;

    auto result = calc.evaluate("-(-x + 5) + 5 + sqrt(x + 9, 2)", variables);
    
    if (result) {
        std::cout << "Result: " << *result << std::endl;
    }
    
    return 0;
}
```
Output
```cpp
Result: 33.000000
```