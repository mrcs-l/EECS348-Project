#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "BinaryOperator.h"

class Multiplication : public BinaryOperator {
    public:
        float Calculate(float lhs, float rhs) const override;
};

#endif