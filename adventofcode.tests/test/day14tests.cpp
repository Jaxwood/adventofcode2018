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

TEST(day14Fixture, Part2a) {
	auto actual = Day14::Part2(vector<int> {5, 1, 5, 8, 9});
	EXPECT_EQ(9, actual);
}

TEST(day14Fixture, Part2b) {
	auto actual = Day14::Part2(vector<int> {0, 1, 2, 4, 5 });
	EXPECT_EQ(5, actual);
}

TEST(day14Fixture, Part2c) {
	auto actual = Day14::Part2(vector<int> { 9, 2, 5, 1, 0});
	EXPECT_EQ(18, actual);
}

TEST(day14Fixture, Part2d) {
	auto actual = Day14::Part2(vector<int> { 5, 9, 4, 1, 4});
	EXPECT_EQ(2018, actual);
}
