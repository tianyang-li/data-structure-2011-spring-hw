#ifndef PRIOR_QUEUE_H
#define PRIOR_QUEUE_H

#include <new>
#include <cstddef>

template <class T>
class PrQue {
public:
	inline PrQue() : size(0) {
	}

	inline ~PrQue() {
	}
private:
	std::size_t size;
};

#endif
