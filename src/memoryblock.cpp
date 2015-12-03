#include "memoryblock.h"

MemoryCell Block::get_cell_from_offset(int offset) {
	return cells[offset];
}

void Block::set_cell_from_offset(int offset, MemoryCell arg_cell) {
	cells[arg_cell.get_offset()] = arg_cell;
}

void Block::set_id(int arg_id) { id = arg_id; }
int Block::get_id() { return id; }

int Block::get_dirty_bit() { return dirty_bit; }
void Block::set_dirty_bit() { dirty_bit = 1; }
void Block::clear_dirty_bit() { dirty_bit = 0; }
void Block::enable_dirty_bit() { set_dirty_bit(); }

bool Block::is_dirty() {
	if (dirty_bit == 0)
		return false;
	return true;
}
