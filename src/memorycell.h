#ifndef MEMORYCELL_H
#define MEMORYCELL_H

#include <iostream>
#include "request.h"

using std::cout;

class MemoryCell {

public:

	MemoryCell() {
		tag       = 0;
		entry     = 0;
		offset    = 0;
		data      = 0;
		address   = 0;
		valid     = false;
	}

	void set_cell(Request);

	int get_offset();
	void set_offset(int);

	int get_entry();
	void set_entry(int);

	int get_tag();
	void set_tag(int);

	int get_address();
	void set_address(int);

	int get_data();
	void set_data(int);

	bool is_valid();
	void make_valid();
	void make_invalid();

	void print_cell();

private:

	int data; // maybe datatype should be string?
	int offset;
	int entry;
	int tag;
	int address;
	bool valid;

};

#endif
