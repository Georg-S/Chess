#include "Utility.h"

bool ceg::is_number(char c)
{
	return (c >= '0') && (c <= '9');
}

void ceg::set_bit(uint64_t& num, int bit_index)
{
	constexpr uint64_t buf = 1;
	num |= (buf << bit_index);
}

std::vector<std::string> ceg::string_split(std::string str, const std::string& delimiter)
{
	std::vector<std::string> result;
	size_t pos = 0;
	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		result.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	}
	result.push_back(str);

	return result;
}

bool ceg::is_bit_set(uint64_t num, int bit_index)
{
	constexpr uint64_t buf = 1;
	return num & (buf << bit_index);
}

int ceg::to_linear_idx(int x, int y)
{
	return x + y * 8;
}

void ceg::print_bit_board(uint64_t num)
{
	for (int y = 0; y < 8; y++) 
	{
		for (int x = 0; x < 8; x++) 
		{
			char c = is_bit_set(num, to_linear_idx(x, y)) ? '1' : '-';
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
}
