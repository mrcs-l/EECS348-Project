#ifndef POSITIVE_H
#define POSITIVE_H

#include "unary_operator.hpp"

class Positive : public UnaryOperator {
public:
	double calculate(std::vector<double>& args) {
		return args[0];
	};
};

#endif // POSITIVE_H