#include "array_t.hpp"
array_t::array_t(int n){
	values = new unsigned int[n];
	size = n;
}
array_t::~array_t() {
	delete[] values;
}
