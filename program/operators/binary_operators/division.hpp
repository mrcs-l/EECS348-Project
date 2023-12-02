#ifndef DIVISION_H
#define DIVISION_H

#include "binary_operator.hpp"
#include "../../error_handler/error_handler.hpp"

class Division : public BinaryOperator {
public:
	double calculate(std::vector<double>& args) {

		if (!args[1]) throw EvaluationException("Divide by zero.");

		return args[0] / args[1];
	};
};

#endif // DIVISION_H
