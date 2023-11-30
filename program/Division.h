#ifndef DIVISION_H
#define DIVISION_H

#include "BinaryOperator.h"

class Division : public BinaryOperator {
public:
	double Calculate(double lhs, double rhs) {

		// @TODO: handle divide by zero errors
		
		return lhs / rhs;
	};
};

#endif // DIVISION_H
