#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "BinaryOperator.h"

class Subtraction : public BinaryOperator {
    public:
        float Calculate(float lhs, float rhs) const override;
};

#endif