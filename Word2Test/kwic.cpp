/*
 * kwic.cpp
 *
 *  Created on: 20.11.2016
 *      Author: David
 */

#include "kwic.h"
#include "Word.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <set>

void kwic(std::istream &in, std::ostream &out){
	std::vector<Sentence> sentences{};
	using input = std::istream_iterator<Sentence>;
	std::copy(input{in}, input{}, std::back_inserter(sentences));

	std::set<Sentence> keywordRegister{};
	std::cout << "keywordRegister initialized";

	std::for_each(sentences.begin(), sentences.end(), [&keywordRegister](Sentence s){
		std::cout << "Sentence: " << s;
		for (auto it = s.begin(); it != s.end(); ++it) {
			Sentence rotated{Word{"tEST"}};
//			std::rotate_copy(s.begin(), it, s.end(), rotated.begin());
			keywordRegister.insert(rotated);
		}
	});

	std::copy(keywordRegister.begin(), keywordRegister.end(), std::ostream_iterator<Sentence>(out, "\n"));
}

std::istream & operator>>(std::istream & inStream, Sentence & s){
	using input = std::istream_iterator<Word>;
	std::string line{};
	if(std::getline(inStream, line)){
		std::istringstream is{line};
		std::copy(input{is}, input{}, std::back_inserter(s));
		is.clear();
	}
	return inStream;
}
std::ostream & operator<<(std::ostream & outStream, Sentence const & s){
	std::copy(s.begin(), s.end(), std::ostream_iterator<Word>(outStream, " "));
	return outStream;
}

