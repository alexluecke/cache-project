#include "helper.h"

using namespace std;

int helper::int_from_char(char c) {
	if (c >= '0' && c <= '9') return (c-'0');
	if (c >= 'A' && c <= 'F') return (c-'A'+10);
	if (c >= 'a' && c <= 'f') return (c-'a'+10);
	return 0;
}

char helper::char_from_int(int val) {
	if (val <= 9) return char(48+val); // 48 is ascii for '0'.
	if (val > 9) return char(65+(val-10)); // 65 is ascii for 'a'.
	return ' ';
}

int helper::hex_string_to_decimal(string string_to_convert) {
	return string_to_decimal(string_to_convert, 16);
}

int helper::string_to_decimal(string string_to_convert, int base) {
	unsigned int i=0, result=0;
	while ( i < string_to_convert.size() )
		result = base*result + int_from_char(string_to_convert[i++]);
	return result;
}

void helper::output_dm_cache(string filename) {

	int some_ending_spot = 7; // Change this to something meaningful

	ofstream outfile;
	outfile.open(filename.c_str(), ios::trunc); // Note the c_str() function.
	for(int ii = 0; ii <= some_ending_spot; ii++) {
		// Here we need to write the following data to the file on individual lines
		// 0 => Data, 1 => Hit/Miss, 2 => Dirty-bit
		outfile << ii;
	}

	outfile.close();

}

void helper::print_data_hex(int value) {
	printf("%02X", (value & 0xFFFF) );
}

void helper::print_binary(int value, int number_of_bits) {
	for (int i = number_of_bits-1; i >= 0; i--)
		cout << ((value >> i) & 1);
}

int helper::get_bits_required(int arg_number) {
	int bits_required = 0;
	while ((arg_number-1) > 0) {
		arg_number = arg_number >> 1;
		bits_required++;
	}
	return bits_required;
}

vector<string> helper::split(const string &line, char splitter) {
	vector<string> strings;
	stringstream str_stream(line);
	string token;
	while(getline(str_stream, token, splitter))
		strings.push_back(token);
	return strings;
}

