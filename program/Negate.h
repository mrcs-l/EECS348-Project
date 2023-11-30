#ifndef NEGATE_H
#define NEGATE_H

#include "UnaryOperator.h"

class Negate : public UnaryOperator {
public:
	double Calculate(double val) {
		return -val;
	};
};

#endif // NEGATE_H