/*
 * sevensegment.cpp
 *
 *  Created on: 02.10.2015
 *      Author: Roman Ehrbar
 */

#include "sevensegment.h"

#include <vector>
#include <algorithm>
#include <string>
#include <ostream>

const int MAX_SYMBOLS = 8;

const std::vector<std::vector<std::string>> SYMBOLS{
	{
		" - ",
		"| |",
		"   ",
		"| |",
		" - "
	}, {
		"   ",
		"  |",
		"   ",
		"  |",
		"   "
	},{
		" - ",
		"  |",
		" - ",
		"|  ",
		" - "
	},{
		" - ",
		"  |",
		" - ",
		"  |",
		" - "
	},{
		"   ",
		"| |",
		" - ",
		"  |",
		"   "
	},{
		" - ",
		"|  ",
		" - ",
		"  |",
		" - "
	},{
		" - ",
		"|  ",
		" - ",
		"| |",
		" - "
	},{
		" - ",
		"  |",
		"   ",
		"  |",
		"   "
	},{
		" - ",
		"| |",
		" - ",
		"| |",
		" - "
	},{
		" - ",
		"| |",
		" - ",
		"  |",
		" - "
	},{
		"   ",
		"   ",
		"-- ",
		"   ",
		"   "
	},{
		" - ",
		"|  ",
		" - ",
		"|  ",
		" - "
	},{
		"   ",
		"   ",
		" - ",
		"|  ",
		"   "
	},{
		"   ",
		"   ",
		" - ",
		"| |",
		" - "
	}
};

void printLargeNumber(int i, std::ostream &out){
	std::vector<int> number{};
	int rest = abs(i);
	do{
		number.insert(number.begin(), rest % 10);
		rest /= 10;
	} while (rest > 0);

	if(i<0){
		number.insert(number.begin(), 10);
	}

	if(number.size() > MAX_SYMBOLS){
		throw std::length_error{"Cannot output number, length is restricted by MAX_SYMBOLS"};
	}

	printVector(number, out);
}

void printError(std::ostream &out){
	printVector({11, 12, 12, 13, 12}, out);
}

void printVector(std::vector<int> symbols, std::ostream &out){
	// TODO loop through lines and add a \n
	for(auto it = cbegin(SYMBOLS.at(0)); it!= cend(SYMBOLS.at(0));++it){
		int dist = std::distance(cbegin(SYMBOLS.at(0)), it);
		std::for_each(symbols.begin(), symbols.end(), [&out, &dist](int x){
			out << SYMBOLS.at(x).at(dist) << " ";
		});
		out << "\n";
	};
}


void printLargeDigit(int i, std::ostream &out){
	std::for_each(SYMBOLS.at(i).begin(), SYMBOLS.at(i).end(), [&out](std::string x){
		out << x << "\n";
	});
}

