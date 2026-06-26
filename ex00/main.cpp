#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Invalid input: Please enter 1 string literal" << std::endl;
		return (1);
	}
	ScalarConverter::convert(argv[1]);
	return (0);
}