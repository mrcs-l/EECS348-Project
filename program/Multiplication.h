#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "BinaryOperator.h"

class Multiplication : public BinaryOperator {
public:
	double Calculate(double lhs, double rhs) {
		return lhs * rhs;
	};
};

#endif // MULTIPLICATION_H