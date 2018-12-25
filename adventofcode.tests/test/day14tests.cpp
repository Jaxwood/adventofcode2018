#include "pch.h"
#include "Day14.h"

using namespace std;

TEST(day14Fixture, Part1a) {
	auto actual = Day14::Part1(9);
	EXPECT_EQ("5158916779", actual);
}

TEST(day14Fixture, Part1b) {
	auto actual = Day14::Part1(5);
	EXPECT_EQ("0124515891", actual);
}

TEST(day14Fixture, Part1c) {
	auto actual = Day14::Part1(18);
	EXPECT_EQ("9251071085", actual);
}

TEST(day14Fixture, Part1d) {
	auto actual = Day14::Part1(2018);
	EXPECT_EQ("5941429882", actual);
}
