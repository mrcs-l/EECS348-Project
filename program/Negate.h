#ifndef NEGATE_H
#define NEGATE_H

#include "UnaryOperator.h"

class Negate : public UnaryOperator {
    public:
        float Calculate(float val) {
            return -val;
        
        }
};

#endif