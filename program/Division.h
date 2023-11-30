#ifndef DIVISION_H
#define DIVISION_H

#include "BinaryOperator.h"

class Division : public BinaryOperator {
    public:
        float Calculate(float lhs, float rhs) const override;
};

#endif