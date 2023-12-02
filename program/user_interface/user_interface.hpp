#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

/**
 * Print the calculator intro
 * onto the user's terminal.
 */
void printIntro();

/**
 * Request arithmetic expression
 * from the user through the CLI.
 *
 * @return String input by user.
 */
std::string getExpressionInput();

/**
 * Print the provided output double
 * to the user as an program answer.
 *
 * @param output Output to display.
 */
void printOutput(double output);

/**
 * Print separation to terminal for
 * usage between entry & evaluation
 * cycles (cleans up output).
 */
void printSeparator();

/**
 * Determine if input string is an
 * exit string. If so, print a msg
 * that tells user.
 *
 * @param input String to check.
 * @return Input is an escape str.
 */
bool isExitString(std::string input);

/**
 * Print an error's message onto
 * the terminal for the user.
 *
 * @param msg error msg to print.
 */
void printError(std::string msg);

#endif // USER_INTERFACE_H