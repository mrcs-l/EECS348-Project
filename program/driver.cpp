#include <iostream>
#include "user_interface/user_interface.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

void prompt() {
	string expression = getExpressionInput();
	if (isExitString(expression)) return;

	auto lexerTokens  = Lexer(expression).getTokenVector();
	AST abstractSTree = parse(lexerTokens);

	// Check if AST creation failed.
	if (abstractSTree.empty()) {
		printSeparator();
		prompt();
		return;
	}

	// Evaluate AST.
	try {
		double evaluation = abstractSTree.evaluate();
		printOutput(evaluation);
	} catch (EvaluationException e) {
		e.print();
	};

	printSeparator();
	prompt();

}

int main() {
	printIntro();
	prompt();
}