#ifndef OPERATOR_H
#define OPERATOR_H

#include <bits/stdc++.h> 
using namespace std; 

class Operator {
	public:
		string symbols;
		int params; // number of parameters?

		Operator(string inputSymbols, int inputParams) {
			symbols = inputSymbols;
			params = inputParams;
		}

		virtual float Calculate() = 0;
};

#endif