#include <iostream>
#include "lexer.h"
#include "AST.h"
#include "Calculator.h"
#include "Parser.h"

int main() {
	string expression = lexer::lex();
	AST ast = Parser::parse(expression);
	return Calculator::evaluate(ast);
}