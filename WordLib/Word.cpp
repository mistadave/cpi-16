/*
 * Word.cpp
 *
 *  Created on: 20.11.2016
 *      Author: David
 */

#include "Word.h"
#include <iostream>
#include <string>
#include <algorithm>

Word::Word(std::string word) {
	if(word == "" || !all_of(word.begin(), word.end(), isalpha)){
		throw std::invalid_argument {"only alpha is allowed as input!"};
	}
	this->word = word;
}

std::ostream & Word::print(std::ostream & os) const {
	os << word;
	return os;
}

std::istream & Word::read(std::istream & is) {
	std::string tempWord { };
	char c { };
	while (is.good() && !isalpha(is.peek())) {
		is.get();
	}
	while ((bool) is.get(c) && isalpha(c)) {
		tempWord.push_back(c);
	}
	try {
		Word input { tempWord };
		(*this) = input; // overwrite content of this object
		is.clear();
	} catch (std::invalid_argument &e) {
		// Set the failbit
		is.setstate(std::ios::failbit | is.rdstate());
	}
	return is;
}

bool Word::operator<(Word const& rhs) const {
	return std::lexicographical_compare(word.begin(), word.end(), rhs.word.begin(), rhs.word.end(), [](char l, char r) {
		return std::tolower(l) < std::tolower(r);
	});
}
