#include "array_t.h"
array_t::array_t(int n){
	values = new unsigned int[n];
	size = n;
}
array_t::~array_t() {
	delete[] values;
}
