#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "binary_operator.hpp"

class Multiplication : public BinaryOperator {
public:
	double calculate(std::vector<double>& args) {
		return args[0] * args[1];
	};
};

#endif // MULTIPLICATION_H