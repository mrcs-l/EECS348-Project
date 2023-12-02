#ifndef OPERATOR_H
#define OPERATOR_H

#include <vector>

class Operator {
public:
	virtual double calculate(std::vector<double>& args) { return 0; };
	virtual int getParams() {return 0; };
	virtual ~Operator() = default;
};

#endif // OPERATOR_H