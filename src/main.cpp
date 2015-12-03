using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

#include "helper.h"
#include "memory.h"
#include "directmapped.h"

using std::string;

// GLOBALS
//const int LINE_SIZE=4;
//const int MEMORY_SIZE_IN_BYTES = 256;
const int N_FIELDS = 3;

typedef unsigned int uint;

int main(void) {

	vector<string> lines;
	string line;

	// tag = 0, 2^(16-3) = 2^13 = 0x2000 = entry, 8 line_size
	Memory *m = new Memory(0, 0x2000, 8);

	// tag: 256 = 8 bits, entry_size: 32 = 5 bits = how many blocks, line_size: 8 = 3 bits
	DirectMapped cache = DirectMapped(256, 32, 8);

	// Memory deleted in destructor
	cache.set_memory(m);

	// Get the input
	while (std::getline(std::cin, line))
		lines.push_back(line);

	for (auto itl = lines.begin(); itl != lines.end(); itl++) {
		vector<int> fields;

		// split into parts
		vector<string> parts = helper::split(*itl, ' ');

		// turn parts into decimal values
		for (auto itp = parts.begin(); itp != parts.end(); itp++)
			fields.push_back(helper::hex_string_to_decimal(*itp));

		if (fields.size() < 3) {
			cout << "Wrong number of fields.\n";
			exit(1);
		}

	 	Request request = Request(
	 		fields.at(0), // address: 2 bytes
	 		fields.at(1), // type: 0x00 = read, 0xFF = write
	 		fields.at(2)  // data: 1 byte
	 	);

		cache.process_request(request);

	}

	return 0;

}
