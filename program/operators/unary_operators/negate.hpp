#ifndef NEGATE_H
#define NEGATE_H

#include "unary_operator.hpp"

class Negate : public UnaryOperator {
public:
	double calculate(std::vector<double>& args) {
		return -args[0];
	};
};

#endif // NEGATE_H