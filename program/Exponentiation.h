#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "BinaryOperator.h"

class Exponentiation : public BinaryOperator {
    public:
        float Calculate(float lhs, float rhs) {
            return pow(lhs, rhs);
        };
};

#endif