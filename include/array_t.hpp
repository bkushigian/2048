#ifndef ARRAY_T_H
#define ARRAY_T_H
#include <iostream>
struct array_t {
	array_t(int n);
	array_t(array_t& other);
	~array_t();

	int size;
	unsigned int* values;
};

#endif
