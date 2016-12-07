/*
 * pocketcalculator.cpp
 *
 *  Created on: 23.10.2016
 *      Author: David
 */

#include "pocketcalculator.h"
#include "sevensegment.h"
#include "calc.h"

#include <iostream>
#include <iterator>
#include <sstream>

void startCalc(std::istream &in, std::ostream &out){
	using input=std::istream_iterator<std::string>;
	std::string line;
	while(std::getline(in, line)){

		std::istringstream stringStream{line};
		try{
			int result = calc(stringStream);
			printLargeNumber(result, out);
		} catch (std::logic_error const &e){
			printError(out);
		}
	}
}

