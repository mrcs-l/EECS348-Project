#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include <math.h>
#include "BinaryOperator.h"

class Exponentiation : public BinaryOperator {
public:
	double Calculate(double lhs, double rhs) {
		return pow(lhs, rhs);
	};
};

#endif // EXPONENTIATION_H