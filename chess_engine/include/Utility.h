#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


namespace ceg 
{
	// lsb = least significant bit
	int get_bit_index_lsb(uint64_t num);
	uint64_t get_lsb(uint64_t num);
	void reset_lsb(uint64_t& num);
	bool is_number(char c);
	void set_bit(uint64_t& num, int bit_index);
	void set_bit_board_format(uint64_t& num, int x, int y);
	std::vector<std::string> string_split(std::string str, const std::string& delimiter);
	bool is_bit_set(uint64_t num, int bit_index);
	int to_linear_idx(int x, int y);
	void print_bit_board(uint64_t num);
	uint64_t set_all_bits_in_direction(int pos_x, int pos_y, int dir_x, int dir_y, bool set_pos = false);
}