#include "Unittest/catch_amalgamated.hpp"
#include "Utility.h"

TEST_CASE("Test_get_bit_index", "Utility") 
{
	REQUIRE(ceg::get_bit_index_lsb(1) == 0);
	REQUIRE(ceg::get_bit_index_lsb(2) == 1);
	REQUIRE(ceg::get_bit_index_lsb(3) == 0);
	REQUIRE(ceg::get_bit_index_lsb(4) == 2);
	REQUIRE(ceg::get_bit_index_lsb(8) == 3);
	REQUIRE(ceg::get_bit_index_lsb(12) == 2);
	REQUIRE(ceg::get_bit_index_lsb(16) == 4);
	REQUIRE(ceg::get_bit_index_lsb(32) == 5);
	REQUIRE(ceg::get_bit_index_lsb(64) == 6);
	REQUIRE(ceg::get_bit_index_lsb(128) == 7);
	REQUIRE(ceg::get_bit_index_lsb(256) == 8);
	REQUIRE(ceg::get_bit_index_lsb(453) == 0);
}

TEST_CASE("Test_get_lsb", "Utility")
{
	REQUIRE(ceg::get_lsb(1) == 1);
	REQUIRE(ceg::get_lsb(7) == 1);
	REQUIRE(ceg::get_lsb(14) == 2);
}

TEST_CASE("Test_reset_lsb", "Utility")
{
	uint64_t num = 7;
	ceg::reset_lsb(num);
	REQUIRE(num == 6);
	ceg::reset_lsb(num);
	REQUIRE(num == 4);
	ceg::reset_lsb(num);
	REQUIRE(num == 0);

	uint64_t num2 = 1;
	ceg::reset_lsb(num);
	REQUIRE(num == 0);
}

TEST_CASE("Test_get_bit_indices_1", "Utility")
{
	auto indices = ceg::get_bit_indices(0b11);

	REQUIRE(indices.size() == 2);
}

TEST_CASE("Test_get_bit_indices_2", "Utility")
{
	auto indices = ceg::get_bit_indices(0b100001);

	REQUIRE(indices.size() == 2);
}

TEST_CASE("Test_get_every_bit_combination_2_bit", "Utility")
{
	auto indices = ceg::get_bit_indices(0b11);
	auto bit_comb = ceg::get_every_bit_combination(indices);

	REQUIRE(bit_comb.size() == 4);
}

TEST_CASE("Test_get_every_bit_combination_4_bit", "Utility")
{
	auto indices = ceg::get_bit_indices(0b11011);
	auto bit_comb = ceg::get_every_bit_combination(indices);

	REQUIRE(bit_comb.size() == 16);
}

TEST_CASE("Test_get_every_bit_combination_14_bit", "Utility")
{
	auto indices = ceg::get_bit_indices(0b11111111111111);
	auto bit_comb = ceg::get_every_bit_combination(indices);

	REQUIRE(bit_comb.size() == 16384);
}