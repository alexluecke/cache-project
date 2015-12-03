#ifndef MEMORY_H
#define MEMORY_H

#include "memoryblock.h"
#include "request.h"
#include "helper.h"

class Memory {

public:

	Memory(int arg_tag_size=0, int arg_entry_size=0, int arg_line_size=0) {
		tag_size    = arg_tag_size;
		entry_size  = arg_entry_size;
		line_size   = arg_line_size;
		memory_size = entry_size*line_size;
		blocks      = new Block[entry_size];

//		cout << "CREATING MEMORY OF ENTRY SIZE: " << entry_size << endl;
		for (int ii=0; ii < entry_size; ii++) {
			blocks[ii] = Block(line_size);
			blocks[ii].set_id(ii);
		}

	}

	void set_block(int, Block);
	Block get_block(int);
	void set_memory_for_address(int, int, MemoryCell);
	MemoryCell get_memory_for_address(int, int);
	int get_offset_from_address(int);
	int get_entry_from_address(int);
	int get_tag_from_address(int);

private:

	Block *blocks; // each block has line_size number of cells
	int sanitize_data(int); // make sure data is 8 bits
	int memory_size; // = 2^(line_size + entry_size + tag_size)... or that many bits
	int tag_size;
	int line_size;
	int entry_size; // # of blocks

};

#endif
