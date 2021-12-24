#pragma once
#include <stdint.h>
#include <random>

class RNG 
{
public:
	RNG();
	uint64_t get_number(uint64_t from, uint64_t to);

private:
	std::random_device rand_device;
	std::default_random_engine rand_engine;
};