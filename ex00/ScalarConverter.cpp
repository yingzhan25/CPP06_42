#include "ScalarConverter.hpp"
#include <sstream>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isChar(const std::string& str) {
	if (str.length() != 3)
		return false;
	if (str[0] != '\'' || str[2] != '\'')
		return false;
	// Check is printable or not
	if (str[1] < 32 || str[1] > 126)
		return false;
	return true;
}

bool ScalarConverter::isInt(const std::string& str) {
	if (str.empty())
		return false;
	std::stringstream ss(str);
	// Convert to long long first to avoid undefined behavior
	long long num;
	ss >> num;
	// string not pure digital, e.g.123abc, 1.0f
	// 0 before digit is skipped
	if (ss.fail() || !ss.eof())
		return false;
	if (num < std::numeric_limits<int>::min() ||
		num > std::numeric_limits<int>::max())
		return false;
	return true;
}

bool ScalarConverter::isFloat(const std::string& str) {
	if (str.empty())
		return false;
	
}