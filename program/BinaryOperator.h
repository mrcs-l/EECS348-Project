#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H

#include "Operator.h"

class BinaryOperator : public Operator {
public:
	const int params = 2;
	virtual double Calculate(double lhs, double rhs) = 0;
};

#endif // BINARYOPERATOR_H