#ifndef HELPER_H
#define HELPER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace helper {
	void print_data_hex(int);
	void print_binary(int, int);
	void print_binary_from_integer(int, int);
	int int_from_char(char);
	int string_to_decimal(string, int);
	int hex_string_to_decimal(string);
	char char_from_int(int);
	void output_dm_cache(string);
	int get_bits_required(int);
	vector<string> split(const std::string &, char);
};

#endif
