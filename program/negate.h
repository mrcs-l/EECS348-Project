#ifndef NEGATE_H
#define NEGATE_H

#include "UnaryOperator.h"

class NegationOperator : public UnaryOperator {
    public:
        NegationOperator(){}
        float Calculate(float val) {
            return -val;
        
        }
};

#endif