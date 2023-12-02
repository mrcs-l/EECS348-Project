#ifndef ADDITION_H
#define ADDITION_H

#include "binary_operator.hpp"

class Addition : public BinaryOperator {
public:
	const int params_ = 1;
	double calculate(std::vector<double>& args) {
		return args[0] + args[1];
	};
};

#endif // ADDITION_H