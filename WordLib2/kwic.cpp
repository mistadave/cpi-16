#include "kwic.h"
#include "word.h"
#include <iterator>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>


using wordIt = std::istream_iterator<Word>;

void kwic(std::istream& is, std::ostream& os){
	std::set<std::vector<Word>> dictionary{};
	std::string str{};
	while(std::getline(is, str)){
		if(str.empty()){
			break;
		}
		std::istringstream iss{str};

		std::vector<Word> sentence{wordIt{iss}, wordIt{}};

		for(auto it = sentence.begin();it != sentence.end();it++){
			std::vector<Word> destination{};
			std::rotate_copy(sentence.begin(), it, sentence.end(), std::back_inserter(destination));
			dictionary.insert(destination);
		}
	}

	for(auto & sent : dictionary){
		for (auto & element : sent) {
			os << element << " ";
		}
		os << "\n";
	}
}
