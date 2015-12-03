#ifndef DIRECTMAPPED_H
#define DIRECTMAPPED_H

#include <iostream>
#include "request.h"
#include "memory.h"

using std::cout;

class DirectMapped {

public:

	DirectMapped(int arg_tag_size, int arg_entry_size, int arg_line_size) {
		cache = new Memory(arg_tag_size, arg_entry_size, arg_line_size);
	}

	~DirectMapped() {
		delete [] cache;
		delete memory;
	}

	MemoryCell create_cell_from_request(Request);
	bool is_read(Request); // !is_read = write
	bool read(Request);    // read from location
	bool write(Request);   // write to cache
	bool process_request(Request); // should return a response?
	void set_memory(Memory *);

private:

	Memory *memory; // instantiated from main and connect via set_memory
	Memory *cache;
	Request request;
	RequestType request_type;

};

#endif
