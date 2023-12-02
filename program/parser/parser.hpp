#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"
#include "../error_handler/error_handler.hpp"

class AST {
public:
	AST(const std::vector<Token>&);

	/**
	 * Evaluate the AST recursively
	 * starting from the root node.
	 *
	 * @return Value of the AST.
	 */
	double evaluate();

	/**
	 * Check if the AST is empty.
	 * Usually empty because it
	 * encountered an error when
	 * parsing.
	 *
	 * @return If AST is empty.
	 */
	bool empty() { return root_ == nullptr; }

private:
	class Node {
	public:
		Node(Token value) : value_(value) {};

		Node(Token value, std::unique_ptr<Node> rhs)
		: value_(value)
		, rhs_(std::move(rhs)) {};

		Node(Token value, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
		: value_(value)
		, lhs_(std::move(lhs))
		, rhs_(std::move(rhs)) {};

		Token value_;
		std::unique_ptr<Node> lhs_;
		std::unique_ptr<Node> rhs_;

		/**
		 * Evaluate this node's operation
		 * on its lhs and rhs subtrees do
		 * with recursion.
		 *
		 * @return Value of evaluation.
		 */
		double evaluate();
	};

	std::unique_ptr<Node> root_;

	/**
	 * Recursively construct subtrees using
	 * the provided sub-vector. Returns node
	 * that is root to the new subtree.
	 *
	 * @param subVector Token vector to use.
	 * @return Root to new AST subtree.
	 */
	std::unique_ptr<Node> recursiveDescent(const std::vector<Token>& subVector);

	/**
	 *
	 */
	void findLexicalExceptions(const std::vector<Token>& tokens);

	/**
	 * Helper function that handles
	 * exceptions using polymorphism.
	 *
	 * @param error Exception handle.
	 */
	void handleError(CalculatorException* error);
};

/**
 * Generate an AST from a vector
 * of lexer tokens. Is basically
 * a wrapper for the default AST
 * constructor.
 *
 * @param tokenVector Lexer tokens.
 * @return AST of token vector.
 */
AST parse(const std::vector<Token>& tokenVector);

#endif // PARSER_H