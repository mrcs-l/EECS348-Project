#ifndef OPERATOR_H
#define OPERATOR_H

class Operator {
public:
	int params; /** Number of parameters */
	virtual double Calculate() = 0;
};

#endif // OPERATOR_H