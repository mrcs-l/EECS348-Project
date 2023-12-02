#include <iomanip>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include "user_interface.hpp"

using std::string;

void printIntro() {
	std::cout << R"(
━━━━ CALCULATOR ━━━━
 EECS348 Arithmetic
     Calculator
━━━━━━━━━━━━━━━━━━━━
	)" << std::endl;
}

string getExpressionInput() {
	string expression;

	std::cout << ": ";
	std::getline(std::cin, expression);

	return expression;
}

void printOutput(double output) {
	std::cout << "= "   << std::setprecision(15)
			  << output << std::endl;
}

void printSeparator() {
	std::cout << "\n";
}

const std::unordered_set<string> exitLookupTable = {
	"", "x", "e", "esc", "exit", "end", "out",
	"leave", "done", "finish", "finished"
};

bool isExitString(string input) {
	if (!exitLookupTable.count(input))
		return false;

	std::cout << "[Exited Calculator]" << std::endl;
	return true;
}

void printError(string msg) {
	std::cout << "[ERROR]: " << msg << std::endl;
}