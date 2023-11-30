#ifndef UNARYOPERATOR_H
#define UNARYOPERATOR_H

#include "Operator.h"

class UnaryOperator : public Operator {
public:
	int params = 1;
	virtual float Calculate(float exp) = 0;
};

#endif // UNARYOPERATOR_H
