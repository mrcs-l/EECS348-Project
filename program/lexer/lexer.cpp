#include "lexer.hpp"
#define MAX_OPERATOR_LEN 2

string Lexer::peek(int count) const {
	return expression_.substr(index_, count);
}

string Lexer::take(int count) {
	string takenStr = expression_.substr(index_, count);
	index_ += count;
	return takenStr;
}

bool Lexer::isEmpty() const {
	return index_ == expression_.size() ||
		   isSpace(expression_.size() - index_ + 1);
}

void Lexer::reset() {
	prevOperable_ = false;
	index_ = 0;
}

Token Lexer::next() {
	// Remove all whitespace
	while (isSpace()) take();

	// Check and return a constant token
	if (isNumeric()) return getConstantToken();

	// Return operator instead
	auto opToken  = getOperatorToken();
	prevOperable_ = opToken.isClosedParen();
	return opToken;
}

std::vector<Token> Lexer::getTokenVector() {
	reset();
	std::vector<Token> tokenVector;
	while(!isEmpty())
		tokenVector.push_back(next());
	return tokenVector;
}

bool Lexer::isSpace(int count) const {
	return peek(count).find_last_not_of(" \t\n\r\f\v") == string::npos;
}

bool Lexer::isNumeric(int count) const {
	return peek(count).find_first_not_of("0123456789.") == string::npos;
}

Token Lexer::getConstantToken() {
	string lexeme;
	int curIndex   = index_;
	int decimalCnt = 0;
	prevOperable_  = true;

	while (!isEmpty() && isNumeric()) {
		decimalCnt += peek() == '.';
		if (decimalCnt > 1) break;
		lexeme += take();
	}

	return {Kind::CONSTANT, curIndex, lexeme};
}

Token Lexer::getOperatorToken() {
	for (int len = MAX_OPERATOR_LEN; len > 0; len--) {
		string lexeme = peek(len);
		bool isBinary = kindLookupBinary.count(lexeme);
		bool isAlways = kindLookupAlways.count(lexeme);

		/*
		 * Return a binary kind operator if lexeme is
		 * in the binary operator lookup table AND it
		 * it follows an operable token (the intended
		 * case) or it is not in the other table (the
		 * inevitable error created by this case will
		 * be handled in the parser).
		 */

		if (isBinary && (prevOperable_ || !isAlways))
			return {kindLookupBinary.at(lexeme), index_, take(lexeme.size())};

		/*
		 * If the lexeme is not a binary operator or
		 * its context makes it better suited as its
		 * unary form, return it as that token.
		 */

		if (isAlways) return
			{kindLookupAlways.at(lexeme), index_, take(lexeme.size())};
	}

	/*
	 * The current postion does not encode
	 * a recognized operator lexeme, so we
	 * return unrecognized token instead.
	 */

	return {Kind::UNRECOGNIZED, index_, take(1)};
}