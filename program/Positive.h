#ifndef POSITIVE_H
#define POSITIVE_H

#include "UnaryOperator.h"

class Positive : public UnaryOperator {
public:
	double Calculate(double val) {
		return val;
	};
};

#endif // POSITIVE_H