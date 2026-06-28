#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main(void) {

	std::cout << "========Generate only once========" << std::endl;
	Base* object = generate();
	identify(object);
	identify(*object);
	delete object;

	std::cout << "======Generate multiple times======" << std::endl;
	// Create array of pointers on stack
	Base* objects[3];
	for (int i = 0; i < 3; i++) {
		objects[i] = generate();
	}
	for (int i = 0; i < 3; i++) {
		identify(objects[i]);
	}
	for (int i = 0; i < 3; i++) {
		identify(*objects[i]);
	}
	for (int i = 0; i < 3; i++) {
		delete objects[i];
	}

	return 0;
}