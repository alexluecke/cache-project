#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include "memorycell.h"

class Block {

	public:

		Block(int arg_line_size=0) {
			cells = new MemoryCell[arg_line_size]; // if LS: 8 = 3 bits
			offset_max = arg_line_size;
			line_size = arg_line_size;
		}

		MemoryCell get_cell_from_offset(int offset);
		void set_cell_from_offset(int, MemoryCell);

		void set_id(int);
		int get_id();

		int get_dirty_bit();
		void set_dirty_bit();
		void enable_dirty_bit(); // wrapper for set_dirty_bit
		void clear_dirty_bit();
		bool is_dirty();

	private:

		MemoryCell *cells;
		int dirty_bit; // 0 or 1
		int offset_max;
		int id;
		int line_size;

};

#endif
