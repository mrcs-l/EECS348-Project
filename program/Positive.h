#ifndef POSITIVE_H
#define POSITIVE_H

#include "UnaryOperator.h"

class Positive : public UnaryOperator {
    public:
        float Calculate(float val) {
            return val;
        
        }
};

#endif