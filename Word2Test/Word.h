/*
 * Word.h
 *
 *  Created on: 20.11.2016
 *      Author: David
 */

#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <iosfwd>

class Word {
	std::string word;
public:
	Word() = default;
	Word(std::string word);

	std::ostream & print(std::ostream & os) const;

	std::istream & read(std::istream & is);

	bool operator<(Word const& rhs) const;
};
inline std::istream & operator>>(std::istream & is, Word & w) {
	return w.read(is);
}
inline std::ostream & operator<<(std::ostream & os, Word const & w) {
	return w.print(os);
}
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
#endif /* WORD_H_ */
