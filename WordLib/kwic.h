/*
 * kwic.h
 *
 *  Created on: 20.11.2016
 *      Author: David
 */

#ifndef KWIC_H_
#define KWIC_H_

#include "Word.h"
#include <iosfwd>
#include <vector>

using Sentence = std::vector<Word>;

void kwic(std::istream &in, std::ostream &out);

std::istream & operator>>(std::istream & inStream, Sentence & s);
std::ostream & operator<<(std::ostream & outStream, Sentence const & s);
#endif /* KWIC_H_ */
