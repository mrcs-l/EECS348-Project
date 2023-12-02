#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "../operator.hpp"

class UnaryOperator : public Operator {
public:
	virtual int getParams() { return 1; }
};

#endif // UNARY_OPERATOR_H
