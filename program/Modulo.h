#ifndef MODULO_H
#define MODULO_H

#include "BinaryOperator.h"

class Modulo : public BinaryOperator {
    public:
        float Calculate(float lhs, float rhs) {
            return (int)lhs % (int)rhs;
        };
};

#endif
