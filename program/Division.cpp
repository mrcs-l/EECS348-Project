#include "Division.h"

Division::Division() : Operator("/") {}

float Division::Calculate(float lhs, float rhs) const {
    return lhs / rhs;
}