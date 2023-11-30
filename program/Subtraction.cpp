#include "Subtraction.h"

Subtraction::Subtraction() : Operator("-") {}

float Subtraction::Calculate(float lhs, float rhs) const {
    return lhs - rhs;
}
