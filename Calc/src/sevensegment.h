/*
 * sevensegment.h
 *
 *  Created on: 23.10.2016
 *      Author: David
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
