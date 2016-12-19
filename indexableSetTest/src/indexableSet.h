#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_
#include <set>
#include <stdexcept>
#include <iostream>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE> {
public:
	using std::set<T, COMPARE>::set;

	T const &at(int index) const {
		int size = this->size();
		if (index < 0) {
			index += size;
		}
		if (index >= size || index < 0) {
			throw std::out_of_range("index is out of range");
		} else {
			return *std::next(this->begin(), index);
		}
	}

	T const &front() const {
		return at(0);
	}

	T const &back() const {
		return at(-1);
	}

	T const &operator[] (const int index) const {
		return at(index);
	}
};


#endif /* SRC_INDEXABLESET_H_ */
