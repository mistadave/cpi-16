#ifndef WORD_H_
#define WORD_H_

#include <string>

class Word {
	std::string word;
public:
	bool operator<(Word const & rhs) const;
	Word(std::string wordValue);
	Word()=default;
	static bool isValidWord(std::string const & toTest);
	std::istream& read(std::istream& in);
	std::ostream& print(std::ostream& in) const;
};

inline bool operator>(Word const & lhs, Word const & rhs) {
return rhs < lhs;
}
inline bool operator>=(Word const & lhs, Word const & rhs) {
return !(lhs < rhs);
}
inline bool operator<=(Word const & lhs, Word const & rhs) {
return !(rhs < lhs);
}
inline bool operator==(Word const & lhs, Word const & rhs) {
return !(lhs < rhs) && !(rhs < lhs);
}
inline bool operator!=(Word const & lhs, Word const & rhs) {
return !(lhs == rhs);
}
inline std::istream& operator>>(std::istream& in, Word& w){
	return w.read(in);
}

inline std::ostream& operator<<(std::ostream& out, Word w){
	return w.print(out);
}

#endif /* WORD_H_ */
