#include <stdio.h>

#include "AST.h"

class Calculator {
	public:
		static double evaluate(AST ast) {
			return ast.evaluate();
		}
};