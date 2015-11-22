#include "array_t.hpp"
array_t::array_t(int n){
	values = new unsigned int[n];
	size = n;
}
array_t::array_t(array_t& other) {
	size = other.size;
	values = new unsigned int[size];
	for (int pos = 0; pos < 16; ++pos)
		values[pos] = other.values[pos];
}
array_t::~array_t() {
	delete[] values;
}
