#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include <cmath>
#include "binary_operator.hpp"

class Exponentiation : public BinaryOperator {
public:
	double calculate(std::vector<double>& args) {
		return pow(args[0], args[1]);
	};
};

#endif // EXPONENTIATION_H