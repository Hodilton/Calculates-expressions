#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <string>

namespace calc {

	template<typename T>
	using Letters = std::map<std::string, T>;

	template<typename T>
	using Expression = std::map<std::string, Letters<T>>;
}

#endif // !TYPES_H