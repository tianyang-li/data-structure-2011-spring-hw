#ifndef PRIOR_QUEUE_H
#define PRIOR_QUEUE_H

#include <new>
#include <cstddef>

// min heap
template <class T>
class PrQue {
public:
	std::size_t size;
	T *data;

	inline PrQue() {
	}

	inline ~PrQue() {
		delete [] data;
	}

	inline void SetSize(std::size_t const new_size) {
		size = new_size;
		data = new (std::nothrow) T[new_size];  // XXX: error detection
	}

	void Insert(T const &new_data) {
		++size;
	}

	std::size_t Pop() { // remove top
		--size;
		return (size + 1);
	}
};

#endif
