#include <iostream>

using namespace std;

class lexer {
	public:
		static string lex() {
			std::cout << "Enter equation: ";
			string expression;
			cin >> expression;
			return expression;
		}
};