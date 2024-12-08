#ifndef CALC_FUNCTIONS_H
#define CALC_FUNCTIONS_H

#include "./IFunction.h"

#include <string>
#include <cmath>

//#include <functional>
//#include <unordered_map>

namespace calc::functions {

    template <typename T>
    class Sqrt2Function : public IFunction<T> {
    public:
        T apply(const std::vector<T>& args) const override {
            if (args.size() != 2) {
                throw std::invalid_argument("Sqrt2 function requires exactly two arguments (base, degree).");
            }
            if (args[0] < T(0) && static_cast<int>(args[1]) % 2 == 0) {
                throw std::invalid_argument("Even-degree root not defined for negative numbers.");
            }

            return std::pow(args[0], T(1) / args[1]);
        }

        virtual const size_t requiredArgCount() const override { return 2; }
    };

    template <typename T>
    class Sqrt1Function : public IFunction<T> {
    public:
        T apply(const std::vector<T>& args) const override {
            if (args.size() != 1) {
                throw std::invalid_argument("Sqrt1 function requires exactly one arguments (base).");
            }
            if (args[0] < T(0)) {
                throw std::invalid_argument("Square root not defined for negative numbers.");
            }

            return std::sqrt(args[0]);
        }

        const size_t requiredArgCount() const override { return 1; }
    };

    template <typename T>
    class Pow2Function : public IFunction<T> {
    public:
        T apply(const std::vector<T>& args) const override {
            if (args.size() != 2) {
                throw std::invalid_argument("Pow2 function requires exactly two arguments (base, degree).");
            }
            return std::pow(args[0], args[1]);
        }

        const size_t requiredArgCount() const override { return 2; }
    };

    template <typename T>
    class Pow1Function : public IFunction<T> {
    public:
        T apply(const std::vector<T>& args) const override {
            if (args.size() != 1) {
                throw std::invalid_argument("Pow1 function requires exactly one arguments (base).");
            }
            return std::pow(args[0], 2);
        }

        const size_t requiredArgCount() const override { return 1; }
    };

    template <typename T>
    class SinFunction : public IFunction<T> {
    public:
        T apply(const std::vector<T>& args) const override {
            if (args.size() != 1) {
                throw std::invalid_argument("Sin function requires exactly one argument.");
            }
            return std::sin(args[0]);
        }

        virtual const size_t requiredArgCount() const override { return 1; }
    };

    template <typename T>
    class CosFunction : public IFunction<T> {
    public:
        T apply(const std::vector<T>& args) const override {
            if (args.size() != 1) {
                throw std::invalid_argument("Cos function requires exactly one argument.");
            }
            return std::cos(args[0]);
        }

        virtual const size_t requiredArgCount() const override { return 1; }
    };

   /* template <typename T>
    class CMathFunction : public IFunction<T> {
    private:
        std::function<T(T)> mathFunction;

    public:
        explicit CMathFunction(std::function<T(T)> func) : mathFunction(std::move(func)) {}

        T apply(const std::vector<T>& args) const override {
            if (args.size() != 1) {
                throw std::invalid_argument("This math function requires exactly one argument.");
            }
            return mathFunction(args[0]);
        }

        const size_t requiredArgCount() const override { return 1; }
    };*/

    //functionFactory.registerFunction("sin", std::make_shared<CMathFunction<T>>(std::sin));
}

#endif // !CALC_FUNCTIONS_H