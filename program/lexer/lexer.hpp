#ifndef LEXER_H
#define LEXER_H

#include "token.hpp"

/**
 * Handles the conversion of expression
 * strings into token vectors for usage
 * within the parser.
 */
class Lexer {
public:
	Lexer(const string expression) : expression_(expression) { };

	/**
	 * Generate and return all tokens
	 * within the lexer's expression.
	 * @return All tokens from lexer.
	 */
	std::vector<Token> getTokenVector();

	/**
	 * Sequentially generate and return new
	 * tokens from the expression (starting
	 * on the left and moving right). Note,
	 * calls to this method should have the
	 * isEmpty method as a guard.
	 *
	 * @return The next token in expression.
	 */
	Token next();

	/**
	 * Returns if there are any tokens
	 * waiting in the lexer to be read.
	 *
	 * @return Are valid tokens left.
	 */
	bool isEmpty() const;

	/**
	 * Reset the progress of the internal
	 * lexer iterator and the lexer state.
	 */
	void reset();

private:
	string expression_;         /** The expression the lexer is lexing. */
	bool prevOperable_ = false; /** If the previous token is operable.  */
	int index_ = 0;             /** The lexer's current char position.  */

	/**
	 * Return the next character within
	 * the lexer (without mutations).
	 *
	 * @return Current char to be read.
	 */
	char peek() const { return expression_[index_];   }

	/**
	 * Return and then discard the next
	 * char within the lexer (mutates).
	 *
	 * @return Current char to be read.
	 */
	char take() { return expression_[index_++]; }

	/**
	 * Return the next n = count chars in
	 * the lexer (without any mutations).
	 *
	 * @param count Character read count.
	 * @return String of next characters.
	 */
	string peek(int count) const;

	/**
	 * Return and then discard the next
	 * n = count chars within the lexer.
	 *
	 * @param count Character read count.
	 * @return String of next characters.
	*/
	string take(int count);

	/**
	 * Return if the next n = count chars
	 * in lexer are whitespace characters.
	 *
	 * @param count Character read count.
	 * @return If the substring is space.
	 */
	bool isSpace(int count = 1) const;

	/**
	 * Return if the next n = count chars
	 * in lexer are all numerical chars.
	 *
	 * @param count Character read count.
	 * @return If the substr is numerical.
	 */
	bool isNumeric(int count = 1) const;

	/**
	 * Return a numerical constant token
	 * beginning at the lexer's current
	 * position. Consumes as much of the
	 * expression as possible.
	 *
	 * @return Numerical constant token.
	 */
	Token getConstantToken();

	/**
	 * Return a operator token starting
	 * at the lexer's current position.
	 * Gets the longest possible lexeme
	 * (maximal munch). If no operator
	 * is found, returns invalid token.
	 * 
	 * @return Operator kind token. 
	 */
	Token getOperatorToken();
};

#endif // LEXER_H
