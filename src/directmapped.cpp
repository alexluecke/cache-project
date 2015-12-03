#include "directmapped.h"

void DirectMapped::set_memory(Memory *arg_memory) {
	memory = arg_memory;
}

bool DirectMapped::process_request(Request arg_request) {

	// Set the request so object can determine
	this->request = arg_request; // cache only handles one request at a time

	if (is_read(arg_request))
		read(arg_request);
	else
		write(arg_request);

	return false;

}

bool DirectMapped::is_read(Request arg_request) {
	if (this->request.type == 0)
		return true;
	return false;
}

MemoryCell DirectMapped::create_cell_from_request(Request arg_request) {

	// the offset, entry, and tag depend whether the item is in cache memory or
	// main memory. This will return the cache memory properties.

	MemoryCell new_cell = MemoryCell();
	new_cell.set_address( arg_request.address );
	new_cell.set_data( arg_request.data );
	new_cell.set_offset( cache->get_offset_from_address(arg_request.address) ); // offset never changes
//	new_cell.set_entry( cache->get_offset_from_address(arg_request.address) );
//	new_cell.set_tag( cache->get_tag_from_address(arg_request.address) );

	return new_cell;

}


bool DirectMapped::read(Request arg_request) {

	// Read
	// Memory Miss
	// - Need to bring data from memory, write to cache, update, and clear dirty bit
	// - cache memory valid, but different tags -- evict data, fetch data from memory, clear dirty, put in cache
	// - cache memory invalid, fetch from memory, clear dirty, put in cache
	// Memory Hit
	// - return the cache data, all is good

	Block cache_block = cache->get_block(
		cache->get_entry_from_address(arg_request.address)
	);

	MemoryCell old_cache_cell = cache_block.get_cell_from_offset(
		cache->get_offset_from_address(arg_request.address)
	);

	if (cache->get_tag_from_address(arg_request.address)
			== cache->get_tag_from_address(old_cache_cell.get_address()) ) { // read hit

		// cout << "R: " << cache->get_entry_from_address(old_cache_cell.get_address()) << ": ";
		helper::print_data_hex(old_cache_cell.get_data());
		cout << " " << 1;
		cout << " " << cache_block.get_dirty_bit() << "\n";

	} else { // read miss

		// EVICTION:

		// Just boot the old fucking cache memory out for now
		Block evicted_block = cache_block;

		int dirty_bit = evicted_block.get_dirty_bit(); // he wants the previous dirty bit

		// If evicting a block, clear the dirty bit
		evicted_block.clear_dirty_bit();

		// set block id to the new memory block id
		evicted_block.set_id(
			memory->get_entry_from_address(old_cache_cell.get_address())
		);

		// evict
		memory->set_block(
			memory->get_entry_from_address(old_cache_cell.get_address())
			, evicted_block
		);

		// FETCH FROM MEMORY:

		// Get the new block from memory
		Block new_block = memory->get_block(
			memory->get_entry_from_address(arg_request.address)
		);

		// Update to cache block id
		new_block.set_id(
			cache->get_entry_from_address(arg_request.address)
		);

		cache->set_block(
			cache->get_entry_from_address(arg_request.address)
			, new_block
		);

		MemoryCell new_cell = new_block.get_cell_from_offset(
			cache->get_offset_from_address(arg_request.address)
		);

		// cout << "R: " << cache->get_entry_from_address(new_cell.get_address()) << ": ";
		helper::print_data_hex(new_cell.get_data());
		cout << " " << 0;
		cout << " " << dirty_bit << "\n";

	}

	return true;

}

// write()

// memory miss = tags are different. Go to memory and get the value.
// memory hit = valid and tags are the same

// Miss
// - Evict block, fetch new block from memory, write data, make block dirty

// Hit
// - write data to block and set dirty bit

// A cache write always sets the dirty bit

// Write-back (or write-behind): initially, writing is done only to the cache.
// The value is marked as dirty, then, only in the event that the item
// beomes evicted does the data get sent off to main memory

// Write allocate (also called fetch on write): datum at the missed-write
// location is loaded to cache, followed by a write-hit operation. In this
// approach, write misses are similar to read misses.

bool DirectMapped::write(Request arg_request) {

	Block cache_block = cache->get_block(
		cache->get_entry_from_address(arg_request.address)
	);

	MemoryCell old_cache_cell = cache_block.get_cell_from_offset(
		cache->get_offset_from_address(arg_request.address)
	);

	MemoryCell new_cache_cell = create_cell_from_request(arg_request);

//	cout << arg_request.address << " W: " << cache->get_entry_from_address(new_cache_cell.get_address()) << ": ";
//	helper::print_data_hex(new_cache_cell.get_data());
//	cout << " " << 1;
//	cout << " " << cache_block.get_dirty_bit() << "\n";

	if ( cache->get_tag_from_address(arg_request.address)
			== cache->get_tag_from_address(old_cache_cell.get_address()) ) { // write hit

		cache_block.set_dirty_bit(); // writes make block dirty

		cache_block.set_cell_from_offset(
			new_cache_cell.get_offset()
			, new_cache_cell
		);

		cache->set_block(
			cache->get_entry_from_address(new_cache_cell.get_offset())
			, cache_block
		);


	} else { // Write miss

		// EVICTION:

		// Just boot the old cache memory out
		Block evicted_block = cache_block;

		// update the block id to the memory block id
		evicted_block.set_id(
			memory->get_entry_from_address(old_cache_cell.get_address()
		));

		evicted_block.clear_dirty_bit();

		// gtfo
		memory->set_block(
			memory->get_entry_from_address(old_cache_cell.get_address())
			, evicted_block
		);

		// FETCH FROM MEMORY:

		// get the new block from memory
		Block new_block = memory->get_block(
			memory->get_entry_from_address(arg_request.address)
		);

		// make sure block has new cache block id
		new_block.set_id(
			cache->get_entry_from_address(arg_request.address)
		);

		// write the request the new block 
		new_block.set_cell_from_offset(
			cache->get_offset_from_address(arg_request.address)
			, new_cache_cell
		);

		// writing makes dirty
		new_block.set_dirty_bit();

		cache->set_block(
			cache->get_entry_from_address(arg_request.address)
			, new_block
		);

	}

	return true;

}
