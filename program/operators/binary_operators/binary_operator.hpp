#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "../operator.hpp"

class BinaryOperator : public Operator {
public:
	virtual int getParams() { return 2; }
};

#endif // BINARY_OPERATOR_H