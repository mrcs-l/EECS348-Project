#include <stack>
#include <climits>
#include "parser.hpp"

AST parse(const std::vector<Token>& tokenVector) {
	return AST(tokenVector);
}

AST::AST(const std::vector<Token>& tokenVector) {
	try {
		findLexicalExceptions(tokenVector);
		root_ = recursiveDescent(tokenVector);
	} catch (LexicalException e) {
		handleError(&e);
	} catch(CalculatorException e) {
		handleError(&e);
	}
}

void AST::handleError(CalculatorException* error) {
	error->print();
	root_ = nullptr;
}

void AST::findLexicalExceptions(const std::vector<Token>& tokens) {
	std::vector<int> errorPositions;
	for (auto& token : tokens) {
		if (!token.isUnrecognized()) continue;
		errorPositions.push_back(token.position_);
	}

	if (!errorPositions.size()) return;

	throw LexicalException(
		"Unrecognized symbols in expression.",
		errorPositions
	);
}

std::unique_ptr<AST::Node> AST::recursiveDescent(const std::vector<Token>& subVector) {
	std::vector<int> accessibleOperators;
	std::stack<Token> parenStack;
	bool hasStartParen = true;
	bool hasFinalParen = false;

	/*
	 * Find all operators that aren't locked
	 * behind parenthesis in the sub-vector.
	 */

	for (int i = 0; i < subVector.size(); i++) {
		const auto token = subVector[i];

		// Current token is paren
		if (token.isParen()) {

			// Add open paren to stack
			if (token.isOpenedParen())
				parenStack.push(token);

			// Handle paren stack popping
			if (token.isClosedParen()) {

				// Closed paren never opened
				if (parenStack.empty())
					throw ParserException(
						"Closed parenthesis is never opened.",
						token.position_
					);

				if (!token.matches(parenStack.top().kind_)) continue;
				hasFinalParen = i == subVector.size() - 1;
				parenStack.pop();
				continue;
			}
		}

		// Skip, we are inside parenthesis
		if (!parenStack.empty()) continue;

		// We exited all parens
		hasStartParen = false;

		// Operator is accessible, append it
		if (token.isOperator())
			accessibleOperators.push_back(i);
	}

	if (!parenStack.empty())
		throw ParserException(
			"Open parenthesis is not closed.",
			parenStack.top().position_
		);

	/*
	 * Expression was wrapped by extraneous
	 * parenthesis. We remove them both and
	 * recurse downwards.
	 */

	if (hasStartParen && hasFinalParen) {
		if (subVector.size() <= 2)
			throw ParserException(
				"Expression group has no content.",
				subVector[0].position_
			);

		return recursiveDescent({
			subVector.begin() + 1,
			subVector.end() - 1
		});
	}

	/*
	 * Check if we have encountered a
	 * leaf node. If we have, return it
	 * and end this branch's recursion.
	 */

	if (!accessibleOperators.size()) {
		if (subVector.size() > 1)
			throw ParserException(
				"Operands not separated by operator.",
				subVector[0].position_
			);

		return std::make_unique<Node>(subVector[0]);
	}

	/*
	 * Select pivot operator from accessible
	 * operators and split the expression.
	 */

	int lowestPrecedence = INT_MAX;
	int pivotIndex = accessibleOperators[0];
	for (int i : accessibleOperators) {
		int precedence = subVector[i].getPrecedence();
		if (precedence > lowestPrecedence) continue;
		lowestPrecedence = precedence;
		pivotIndex = i;
	}

	auto pivotOperation = subVector[pivotIndex].getOperator();

	std::vector<Token> lExp = {subVector.begin(), subVector.begin() + pivotIndex};
	std::vector<Token> rExp = {subVector.begin() + pivotIndex + 1, subVector.end()};

	if (!rExp.size())
		throw ParserException(
			"Operator right-hand is empty.",
			subVector[pivotIndex].position_
		);

	// Handle unary operator
	if (pivotOperation->getParams() == 1)
		return std::make_unique<Node>(
			subVector[pivotIndex],
			recursiveDescent(rExp)
		);

	if (!lExp.size())
		throw ParserException(
			"Operator left-hand is empty.",
			subVector[pivotIndex].position_
		);

	// Handle binary operator
	return std::make_unique<Node>(
		subVector[pivotIndex],
		recursiveDescent(lExp),
		recursiveDescent(rExp)
	);
}

double AST::evaluate() {
	return root_->evaluate();
}

double AST::Node::evaluate() {
	if (value_.isConstant())
		return stod(value_.lexeme_);

	std::vector<double> params;
	if (lhs_ != nullptr) params.push_back(lhs_->evaluate());
	if (rhs_ != nullptr) params.push_back(rhs_->evaluate());
	return value_.getOperator()->calculate(params);
}