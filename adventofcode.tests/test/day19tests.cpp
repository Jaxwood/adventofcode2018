#include "pch.h"

#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <regex>

#include "Day19.h"

using namespace std;
using namespace Day19;

class day19Fixture : public ::testing::Test {

private:
	std::vector<std::string> _tokens;

public:
	void SetUp(std::string path) {
		std::vector<std::string> tokens;
		std::string line;
		std::ifstream stream;
		stream.open(path, std::iostream::in);
		while (std::getline(stream, line))
		{
			tokens.push_back(line);
		}

		if (stream.is_open())
		{
			stream.close();
		}

		_tokens = tokens;
	}

	vector<Instruction> getTokens() {
		auto result = vector<Instruction>();
		auto reg = regex("(\\w+)\\s(\\d+)\\s(\\d+)\\s(\\d+)", regex_constants::ECMAScript);
		for (auto &token : _tokens) {
			smatch match;
			if (regex_match(token, match, reg)) {
				result.push_back(Instruction(match[1], vector<int> { stoi(match[2]), stoi(match[3]), stoi(match[4]) }));
			}
		}
		return result;
	}
	InstructionPointer getPointer() {
		auto reg = regex("#ip\\s(\\d+)", regex_constants::ECMAScript);
		smatch match;
		if (regex_match(_tokens[0], match, reg)) {
			return InstructionPointer(stoi(match[1]));
		}
		throw exception("could not parse instruction pointer");
	}
};

TEST_F(day19Fixture, Part1) {
	SetUp("day19_fixture.txt");
	auto actual = Day19::Part1(getPointer(), getTokens());
	EXPECT_EQ(6, actual);
}

TEST_F(day19Fixture, Part2) {
	auto actual = Day19::Part2();
	EXPECT_EQ(24117312, actual);
}
