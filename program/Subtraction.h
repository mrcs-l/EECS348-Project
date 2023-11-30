#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "BinaryOperator.h"

class Subtraction : public BinaryOperator {
public:
	double Calculate(double lhs, double rhs) {
		return lhs - rhs;
	};
};

#endif // SUBTRACTION_H