#include "Addition.h"

Addition::Addition() : Operator("+") {}

float Addition::Calculate(float lhs, float rhs) const {
    return lhs + rhs;
}