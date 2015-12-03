#include "memory.h"

Block Memory::get_block(int arg_entry_id) {
	return blocks[arg_entry_id];
}

void Memory::set_block(int arg_entry_id, Block arg_block) {
	blocks[arg_entry_id] = arg_block;
}

int Memory::sanitize_data(int datum) {
	return (datum & 0xFF); // data is only one byte
}

int Memory::get_offset_from_address(int arg_address) {
	return (arg_address & (line_size-1) ); // 8 = 1000, 8-1 = 0111... want lowest 3 bits
}

int Memory::get_entry_from_address(int arg_address) { // this could be done with mod
	return ((arg_address >> helper::get_bits_required(line_size))%entry_size); // or using mod
}

int Memory::get_tag_from_address(int arg_address) {
	arg_address = (arg_address >> helper::get_bits_required(line_size));
	arg_address = (arg_address >> helper::get_bits_required(entry_size));
	return (arg_address & (tag_size-1)); // lowest 8 bits after shift
}

