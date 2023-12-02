#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../user_interface/user_interface.hpp"
#define OFFSET 3

/**
 * Custom error class for calculator
 * related exceptions. Specifically,
 * those generated in the parser.
 */
class CalculatorException : public std::exception {
public:
	CalculatorException(std::string msg, int pos)
	: message_(msg)
	, position_(pos) {}

	/**
	 * Print error to user. Includes
	 * carats pointing at error pos.
	 */
	virtual void print() {
		std::cout << std::setw(position_ + OFFSET) << "^" << std::endl;
		printError(message_);
	}

protected:
	CalculatorException(std::string msg) : message_(msg) {}
	std::string message_; /** Error message  */
	int position_;        /** Error position */
};

/**
 * Parser exclusive exception class
 * (i.e., all errors not associated
 * with invalid lexer tokens).
 */
class ParserException : public CalculatorException {
	using CalculatorException::CalculatorException;
};

/**
 * Invalid lexer token error class
 * made for unrecognized lexemes.
 */
class LexicalException : public CalculatorException {
public:
	LexicalException(std::string msg, std::vector<int> positions)
	: CalculatorException(msg)
	, positions_(positions) {};

	/**
	 * Print error to user. Includes
	 * a carat for every error found.
	 */
	void print() {
		int prevPos = -OFFSET;
		for (int pos : positions_) {
			std::cout << std::setw(pos - prevPos) << "^";
			prevPos = pos;
		}
		std::cout << "\n";
		printError(message_);
	}

private:
	std::vector<int> positions_; /** Positions of all errors */
};

class EvaluationException : public CalculatorException {
public:
	EvaluationException(std::string msg) : CalculatorException(msg) {}

	/**
	 * Print error to user.
	 */
	void print() {
		printError(message_);
	}
};

#endif // ERROR_HANDLER_H