#ifndef MODULO_H
#define MODULO_H

#include <cmath>
#include "binary_operator.hpp"

class Modulo : public BinaryOperator {
public:
	double calculate(std::vector<double>& args) {
		return std::fmod(args[0], args[1]);
	};
};

#endif // MODULO_H