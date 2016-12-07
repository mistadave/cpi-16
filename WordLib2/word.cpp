#include "word.h"
#include <string>
#include <algorithm>
#include <istream>
#include <stdexcept>

Word::Word(std::string wordIn) {
	if(isValidWord(wordIn)){
		this -> word = wordIn;
	} else {
		throw std::invalid_argument{"this is not a valid word. only alpha allowed!"};
	}
}

bool myCompare (char c1, char c2)
{
	return std::tolower(c1)<std::tolower(c2);
}

bool Word::operator<(Word const & toCompare) const{
	return std::lexicographical_compare(word.begin(), word.end(), toCompare.word.begin(), toCompare.word.end(), myCompare);
}

bool Word::isValidWord(std::string const & toTest){
	return std::all_of(toTest.begin(), toTest.end(), isalpha)&&!toTest.empty();
}

std::istream& Word::read(std::istream& in){
	std::string input{};
	char c{};
	while(in.get(c) && !isalpha(c)){

	}
	while(isalpha(c)){
		input += c;
		if(!in.get(c)){
			break;
		}
	}

	if(Word::isValidWord(input)){
		this->word = input;
		in.clear();
	} else {
		in.setstate(std::ios::failbit | in.rdstate()); //set failbit
	}
	return in;
}

std::ostream& Word::print(std::ostream& out) const{
	out << this->word;
	return out;
}
