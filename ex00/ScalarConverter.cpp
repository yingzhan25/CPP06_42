#include "ScalarConverter.hpp"
#include <sstream>
#include <limits>
#include <cmath>

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
	// String not pure digital, e.g.123abc, 1.0f
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
	if (str[str.length() - 1] != 'f' && str[str.length() - 1] != 'F')
		return false;
	std::string withoutF = str.substr(0, str.length() - 1);
	std::stringstream ss(withoutF);
	float num;
	ss >> num;
	return (!ss.fail() && ss.eof() && withoutF.find('.') != std::string::npos);
}

bool ScalarConverter::isDouble(const std::string& str) {
	if (str.empty())
		return false;
	if (str[str.length() - 1] == 'f' && str[str.length() - 1] == 'F')
		return false;
	std::stringstream ss(str);
	double num;
	ss >> num;
	return (!ss.fail() && ss.eof() && str.find('.') != std::string::npos);
}

bool ScalarConverter::isPsudoLiteral(const std::string& str) {
	// Check pseudo-literals in float
	if (str == "nanf" || str == "+inff" || str == "-inff" || str == "inff")
		return true;
	// Check pseudo-literals in double
	if (str == "nan" || str == "+inf" || str == "-inf" || str == "inf")
		return true;
	return false;
}

void ScalarConverter::toChar(double value) {
	std::cout << "char: ";

	// Handle unconvertable psudo literals
	if (std::isnan(value) || std::isinf(value)) {
		std::cout << "impossible" << std::endl;
		return ;
	}
	// Handle unconvertable value exceeding char range
	if (value < std::numeric_limits<char>::min() ||
		value > std::numeric_limits<char>::max()) {
		std::cout << "impossible" << std::endl;
		return ;
	}
	// Handle unconvertable float or double value
	if (value - static_cast<int>(value) != 0) {
		std::cout << "impossible" << std::endl;
		return ;
	}
	char c = static_cast<char>(value);
	// Handle non-displayable chars
	if (c < 32 || c > 126) {
		std::cout << "Non displayable" << std::endl;
		return ;
	}
	std::cout << "'" << c << "'" << std::endl;
}

void ScalarConverter::toInt(double value) {
	std::cout << "int: ";

	// Handle unconvertable psudo literals
	if (std::isnan(value) || std::isinf(value)) {
		std::cout << "impossible" << std::endl;
		return ;
	}
	// Handle unconvertable value exceeding int range
	if (value < std::numeric_limits<int>::min() ||
		value > std::numeric_limits<int>::max()) {
		std::cout << "impossible" << std::endl;
		return ;
	}
	int i = static_cast<int>(value);
	std::cout << i << std::endl;
}