#ifndef CALC_CONSTANT_FACTORY_H
#define CALC_CONSTANT_FACTORY_H

#include "./Constants.h"

#include <map>
#include <memory>
#include <stdexcept>

namespace calc::constants {

    template <typename T>
    class ConstantFactory {
    public:
        ConstantFactory() {
            constants["pi"] = std::make_unique<PiConstant<T>>();
            constants["e"] = std::make_unique<EConstant<T>>();
        }

        const IConstant<T>* getConstant(const std::string& name) const {
            auto it = constants.find(name);
            if (it != constants.end()) {
                return it->second.get();
            }
            throw std::runtime_error("Unknown constant: " + name);
        }

        bool isConstant(const std::string& name) const {
            return constants.find(name) != constants.end();
        }

    private:
        std::map<std::string, std::unique_ptr<IConstant<T>>> constants;
    };
}

#endif // !CALC_CONSTANT_FACTORY_H