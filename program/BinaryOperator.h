#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H

#include "Operator.h"

class BinaryOperator : public Operator {

	public:
		int params = 2;
		
		virtual float Calculate(float lhs, float rhs) = 0;
};

#endif