#ifndef CALC_FUNCTION_FACTORY_H
#define CALC_FUNCTION_FACTORY_H

#include "./Functions.h"

#include <map>
#include <string>
#include <stdexcept>
#include <memory>

namespace calc::functions {

    template <typename T>
    class FunctionFactory {
    public:
        FunctionFactory() {
            functions["sqrt1"] = std::make_unique<Sqrt1Function<T>>();
            functions["sqrt2"] = std::make_unique<Sqrt2Function<T>>();
            functions["pow1"] = std::make_unique<Pow1Function<T>>();
            functions["pow2"] = std::make_unique<Pow2Function<T>>();
            functions["sin"] = std::make_unique<SinFunction<T>>();
            functions["cos"] = std::make_unique<CosFunction<T>>();
        }

        const IFunction<T>* getFunction(const std::string& name) const {
            auto it = functions.find(name);

            if (it != functions.end()) {
                return it->second.get();
            }

            throw std::runtime_error("Unknown function: " + name);
        }

        bool isFunction(const std::string& name) const {
            return functions.find(name) != functions.end();
        }

    private:
        std::map<std::string, std::unique_ptr<IFunction<T>>> functions;
    };

}

#endif // !CALC_FUNCTION_FACTORY_H