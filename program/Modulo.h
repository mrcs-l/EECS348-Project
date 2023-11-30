#ifndef MODULO_H
#define MODULO_H

#include "BinaryOperator.h"

class Modulo : public BinaryOperator {
public:
	double Calculate(double lhs, double rhs) {
		return (int)lhs % (int)rhs;
	};
};

#endif // MODULO_H
