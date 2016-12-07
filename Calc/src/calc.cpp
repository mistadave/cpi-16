/*
 * calc.cpp
 *
 *  Created on: 23.10.2016
 *      Author: David
 */

#include "calc.h"
#include <iostream>

int calc(int a, int b, char operatorChar){
	switch (operatorChar) {
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			if(b == 0){
				throw std::logic_error{"null division error"};
			}
			return a/b;
		case '%':
			if(b == 0){
				throw std::logic_error{"null division error"};
			}
			return a%b;
		default:
			throw std::logic_error{"unknown operator"};
	}
}

int calc(std::istream& in){
	int a{}, b{};
	char op{};
	if(in >> a >> op >> b){
		return calc(a,b,op);
	}
	throw std::logic_error{"could not read input"};
}
