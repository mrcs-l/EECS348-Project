#include <iostream>
#include "lexer.h"
#include "AST.h"
#include "Calculator.h"

int main() {
	string expression = lexer::lex();
	AST ast = parser::parse(expression);
	return Calculator::evaluate(ast);
}