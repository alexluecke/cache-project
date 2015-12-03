#include "memorycell.h"

int MemoryCell::get_offset() { return offset; }
void MemoryCell::set_offset(int arg_offset) { offset = arg_offset; }

int MemoryCell::get_entry() { return entry; }
void MemoryCell::set_entry(int arg_entry) { entry = arg_entry; }

int MemoryCell::get_tag() { return tag; }
void MemoryCell::set_tag(int arg_tag) { tag = arg_tag; }

int MemoryCell::get_address() { return address; }
void MemoryCell::set_address(int arg_address) { address = arg_address; }

int MemoryCell::get_data() { return data; }
void MemoryCell::set_data(int arg_data) { data = arg_data; }

void MemoryCell::make_valid() { valid = true; }
void MemoryCell::make_invalid() { valid = false; }
bool MemoryCell::is_valid() { return valid; }

void MemoryCell::print_cell() {
	cout << "\ndata: " << data << "\n";
	cout << "offset: " << offset << "\n";
	cout << "address: " << address << "\n";
}
