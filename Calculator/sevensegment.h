/*
 * sevensegment.h
 *
 *  Created on: 02.10.2015
 *      Author: Roman Ehrbar
 */

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include <iosfwd>
#include <vector>
void printLargeNumber(int i, std::ostream &out);

void printError(std::ostream &out);

void printVector(std::vector<int> symbols, std::ostream &out);

void printLargeDigit(int i, std::ostream &out);

void printLargeDigitsVertical(int i, std::ostream &out);

#endif /* SEVENSEGMENT_H_ */
