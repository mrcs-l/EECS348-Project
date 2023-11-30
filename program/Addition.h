#ifndef ADDITION_H
#define ADDITION_H

#include "BinaryOperator.h"

class Addition : public BinaryOperator {
    public:
        float Calculate(float lhs, float rhs) {
			return lhs + rhs;
		};
};

#endif