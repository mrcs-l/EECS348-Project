#include "Multiplication.h"

Multiplication::Multiplication() : Operator("*") {}

float Multiplication::Calculate(float lhs, float rhs) const {
    return lhs * rhs;
}