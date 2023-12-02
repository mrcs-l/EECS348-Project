#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "binary_operator.hpp"

class Subtraction : public BinaryOperator {
public:
	double calculate(std::vector<double>& args) {
		return args[0] - args[1];
	};
};

#endif // SUBTRACTION_H