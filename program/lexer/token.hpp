#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../operators/operator_barrel.hpp"

using std::string;

/**
 * All the token kinds/types recognized by
 * the lexer (and thus the calculator as a
 * whole). New operators, etc. must all be
 * appended here in order to be handled.
 */
enum class Kind {
	CONSTANT,
	PAREN_OPENED,
	PAREN_CLOSED,
	BRACKET_OPENED,
	BRACKET_CLOSED,
	POSITIVE,
	NEGATE,
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	MODULO,
	EXPONENTIATION,
	UNRECOGNIZED
};

/*
 * We can't use switch statements because
 * lexemes are strings not chars (because
 * some lexemes are 2 or more characters)
 * Instead, we use lookup tables with the
 * same O(1) complexity as a perfect jump
 * table (albeit, with less clarity).
 */

/**
 * Token kind lookup table for kinds that
 * don't care what token kind they follow.
 */
const std::unordered_map<string, Kind> kindLookupAlways {
	{"(" , Kind::PAREN_OPENED  },
	{")" , Kind::PAREN_CLOSED  },
	{"[" , Kind::BRACKET_OPENED},
	{"]" , Kind::BRACKET_CLOSED},
	{"+" , Kind::POSITIVE      },
	{"-" , Kind::NEGATE        },
};

/**
 * Token kind lookup table for kinds must
 * always come after an "operable" token.
 * That is, one which could theoretically
 * be an operand in an operation.
 */
const std::unordered_map<string, Kind> kindLookupBinary {
	{"+" , Kind::ADDITION      },
	{"-" , Kind::SUBTRACTION   },
	{"*" , Kind::MULTIPLICATION},
	{"/" , Kind::DIVISION      },
	{"%" , Kind::MODULO        },
	{"**", Kind::EXPONENTIATION},
	{"^" , Kind::EXPONENTIATION}
};

/**
 * Tokens are extracted from an expression
 * primarily based on syntactic rules. The
 * process of extracting is handled by the
 * lexer. Tokens are the fundamental break
 * -down unit of an expression, consisting
 * of a lexeme that can be as short as one
 * character.
 */
class Token {
public:
	Token(Kind kind, int position, string lexeme)
	: kind_(kind)
	, position_(position)
	, lexeme_(lexeme) {}

	const Kind kind_;
	const int position_;
	const string lexeme_;

	/**
	 * Return if this token is one of the
	 * token kinds listed within the vec.
	 *
	 * @param kinds Token kinds to check.
	 * @return If token is of given kind.
	 */
	bool isOfKind(std::vector<Kind> kinds) const {
		return std::find(
			kinds.begin(),
			kinds.end(),
			kind_
		) != kinds.end();
	}

	/**
	 * Get an operator object instance
	 * of the operator associated with
	 * the token's kind. A classic GoF
	 * factory method.
	 *
	 * @return Pointer to operator obj.
	 */
	std::unique_ptr<Operator> getOperator() const {
		switch(kind_) {
		case Kind::POSITIVE      : return std::make_unique<Positive>();
		case Kind::NEGATE        : return std::make_unique<Negate>();
		case Kind::ADDITION      : return std::make_unique<Addition>();
		case Kind::SUBTRACTION   : return std::make_unique<Subtraction>();
		case Kind::MULTIPLICATION: return std::make_unique<Multiplication>();
		case Kind::DIVISION      : return std::make_unique<Division>();
		case Kind::MODULO        : return std::make_unique<Modulo>();
		case Kind::EXPONENTIATION: return std::make_unique<Exponentiation>();
		default: return std::make_unique<Positive>();
		}
	}

	/**
	 * Get the precedence of an operator
	 * kind. Returns 0 for any kind that
	 * is not an operator.
	 *
	 * @return Precedence of the token.
	 */
	int getPrecedence() const {
		switch(kind_) {
		case Kind::NEGATE:
		case Kind::POSITIVE:
			return 4;
		case Kind::ADDITION:
		case Kind::SUBTRACTION:
			return 1;
		case Kind::MODULO:
		case Kind::DIVISION:
		case Kind::MULTIPLICATION:
			return 2;
		case Kind::EXPONENTIATION:
			return 3;
		default: return 0;
		}
	}

	/**
	 * Return true if this token is a
	 * numerical constant, else false.
	 *
	 * @return If token is a constant.
	 */
	bool isConstant() const { return kind_ == Kind::CONSTANT; }

	/**
	 * Return if this token is an
	 * operator token (i.e. not a
	 * constant, error, or paren).
	 *
	 * @return Token is a operator.
	 */
	bool isOperator() const {
		return !(isUnrecognized() || isConstant() || isParen());
	}

	/**
	 * Return true if this token is an
	 * unrecognized token (i.e a token
	 * that must be error handled).
	 *
	 * @return Token is unrecognizable.
	 */
	bool isUnrecognized() const { return kind_ == Kind::UNRECOGNIZED; }

	/**
	 * Return true if this token is an
	 * grouping operator (parenthesis,
	 * or brackets) else, return false.
	 *
	 * @return If token is a grouping.
	 */
	bool isParen() const {
		return isOfKind({
			Kind::PAREN_OPENED,
			Kind::PAREN_CLOSED,
			Kind::BRACKET_OPENED,
			Kind::BRACKET_CLOSED
		});
	}

	/**
	 * Return wether this token is
	 * an opened grouping operator.
	 *
	 * @return Token is opened paren.
	 */
	bool isOpenedParen() const {
		return isOfKind({
			Kind::PAREN_OPENED,
			Kind::BRACKET_OPENED
		});
	}

	/**
	 * Return wether this token is
	 * an closed grouping operator.
	 *
	 * @return Token is closed paren.
	 */
	bool isClosedParen() const {
		return isOfKind({
			Kind::PAREN_CLOSED,
			Kind::BRACKET_CLOSED
		});
	}

	/**
	 * Return if this token is grouping
	 * match with other. That is, if it
	 * successfully closes/opens other.
	 *
	 * @param other Kind to match with.
	 * @return Token matches other kind.
	 */
	bool matches(Kind other) const {
		switch (other) {
		case Kind::PAREN_OPENED:
			return kind_ == Kind::PAREN_CLOSED;
		case Kind::PAREN_CLOSED:
			return kind_ == Kind::PAREN_OPENED;
		case Kind::BRACKET_OPENED:
			return kind_ == Kind::BRACKET_CLOSED;
		case Kind::BRACKET_CLOSED:
			return kind_ == Kind::BRACKET_OPENED;
		default: return false;
		}
	}

	string getName() const {
		switch (kind_) {
		case Kind::CONSTANT      : return "CONSTANT";
		case Kind::PAREN_OPENED  : return "PAREN_OPENED";
		case Kind::PAREN_CLOSED  : return "PAREN_CLOSED";
		case Kind::BRACKET_OPENED: return "BRACKET_OPENED";
		case Kind::BRACKET_CLOSED: return "BRACKET_CLOSED";
		case Kind::POSITIVE      : return "POSITIVE";
		case Kind::NEGATE        : return "NEGATE";
		case Kind::ADDITION      : return "ADDITION";
		case Kind::SUBTRACTION   : return "SUBTRACTION";
		case Kind::MULTIPLICATION: return "MULTIPLICATION";
		case Kind::DIVISION      : return "DIVISION";
		case Kind::MODULO        : return "MODULO";
		case Kind::EXPONENTIATION: return "EXPONENTIATION";
		case Kind::UNRECOGNIZED  : return "UNRECOGNIZED";
		};
	}
};

#endif // TOKEN_H