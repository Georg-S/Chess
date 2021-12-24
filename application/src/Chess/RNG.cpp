#include "Chess/RNG.h"

RNG::RNG()
{
	rand_engine = std::default_random_engine(rand_device());
}

uint64_t RNG::get_number(uint64_t from, uint64_t to)
{
	std::uniform_int_distribution<uint64_t> distribution(from, to);

	return distribution(rand_engine);
}
