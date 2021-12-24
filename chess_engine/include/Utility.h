#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


namespace ceg 
{
	bool is_number(char c);
	void set_bit(uint64_t& num, int bit_index);
	std::vector<std::string> string_split(std::string str, const std::string& delimiter);
	bool is_bit_set(uint64_t num, int bit_index);
	int to_linear_idx(int x, int y);
	void print_bit_board(uint64_t num);
}