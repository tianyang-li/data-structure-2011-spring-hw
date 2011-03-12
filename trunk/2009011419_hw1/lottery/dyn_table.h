/*
 * template for
 * dynamic tables (similar to vector in STL)
 */

#ifndef DYN_TABLE_H
#define DYN_TABLE_H

#include <cstddef>

template <class T>
class DynTable {
public:
	DynTable();
	~DynTable();

protected:
	std::size_t num_;  // # of elements in table
	std::size_t size_;  // size of allcoated memory
	T *table_;
};

template <class T>
DynTable<T>::~DynTable() {
	if (this->size_ != 0) {
		delete [] this->table_;
	}
}

template <class T>
DynTable<T>::DynTable() : num_(0), size_(0), table_(0) {
}

#endif  // DYN_TABLE_H
