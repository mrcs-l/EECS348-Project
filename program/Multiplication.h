#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "BinaryOperator.h"

class Multiplication : public BinaryOperator {
    public:
        Multiplication();
        float Calculate(float lhs, float rhs) const override;
};

#endif