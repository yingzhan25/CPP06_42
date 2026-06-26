#include "ScalarConverter.hpp"
#include <sstream>
#include <limits>
#include <cmath>
#include <cctype>
#include <iomanip>

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
	if (!std::isprint(str[1]))
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

// Float should have f/F and . or e/E, integer not counted as float
bool ScalarConverter::isFloat(const std::string& str) {
	if (str.empty())
		return false;
	if (str[str.length() - 1] != 'f' && str[str.length() - 1] != 'F')
		return false;
	std::string withoutF = str.substr(0, str.length() - 1);
	if (withoutF.find('.') == std::string::npos && withoutF.find('e') == std::string::npos && withoutF.find('E') == std::string::npos)
		return false;
	std::stringstream ss(withoutF);
	float num;
	ss >> num;
	return (!ss.fail() && ss.eof());
}

// Double should have . or e/E, integer not counted as double
bool ScalarConverter::isDouble(const std::string& str) {
	if (str.empty())
		return false;
	if (str[str.length() - 1] == 'f' || str[str.length() - 1] == 'F')
		return false;
	if (str.find('.') == std::string::npos && str.find('e') == std::string::npos && str.find('E') == std::string::npos)
		return false;
	std::stringstream ss(str);
	double num;
	ss >> num;
	return (!ss.fail() && ss.eof());
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
	if (!std::isprint(c)) {
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

void ScalarConverter::toFloat(double value) {
	std::cout << "float: ";

	float f = static_cast<float>(value);
	// Handle output of float nan
	if (std::isnan(f)) {
		std::cout << "nanf" << std::endl;
		return ;
	}
	// Handle output of float inf
	if (std::isinf(f)) {
		if (f > 0)
			std::cout << "+inff" << std::endl;
		else
			std::cout << "-inff" << std::endl;
		return ;
	}
	// Set output precision to 1, fixed instead of scientific
	std::cout << std::fixed << std::setprecision(1);
	std::cout << f << "f" << std::endl;
}

void ScalarConverter::toDouble(double value) {
	std::cout << "double: ";

	// Handle output of double nan
	if (std::isnan(value)) {
		std::cout << "nan" << std::endl;
		return ;
	}
	// Handle output of double inf
	if (std::isinf(value)) {
		if (value > 0)
			std::cout << "+inf" << std::endl;
		else
			std::cout << "-inf" << std::endl;
		return ;
	}
	// Set output precision to 1, fixed instead of scientific
	std::cout << std::fixed << std::setprecision(1);
	std::cout << value << std::endl;
}

void ScalarConverter::printImpossible() {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::convert(const std::string& str) {
	double value = 0.0;

	if (isChar(str)) {
		char c = str[1];
		value = static_cast<double>(c);
	}
	else if (isPsudoLiteral(str)) {
		if (str == "nan" || str == "nanf")
			value = std::numeric_limits<double>::quiet_NaN();
		else if (str == "inf" || str == "inff" || str == "+inf" || str == "+inff")
			value = std::numeric_limits<double>::infinity();
		else
			value = -std::numeric_limits<double>::infinity();
	}
	else if (isInt(str)) {
		std::stringstream ss(str);
		long long num;
		ss >> num;
		value = static_cast<double>(num);
	}
	else if (isFloat(str)) {
		std::string withoutF = str.substr(0, str.length() - 1);
		std::stringstream ss(withoutF);
		float num;
		ss >> num;
		value = static_cast<double>(num);
	}
	else if (isDouble(str)) {
		std::stringstream ss(str);
		ss >> value;
	}
	else {
		printImpossible();
		return ;
	}
	toChar(value);
	toInt(value);
	toFloat(value);
	toDouble(value);
}