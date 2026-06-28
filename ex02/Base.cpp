#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void) {
	// Only seed once even if calling functions multiple times
	// to avoid rand() returns same value every time
	static bool seeded = false;
	if (!seeded) {
		srand(static_cast<unsigned>(std::time(NULL)));
		seeded = true;
	}
	int r = rand() % 3;
	if (r == 0) {
		std::cout << "Object A is generated" << std::endl;
		return new A;
	} else if (r == 1) {
		std::cout << "Object B is generated" << std::endl;
		return new B;
	} else {
		std::cout << "Object C is generated" << std::endl;
		return new C;
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "Object A is identified by pointer" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "Object B is identified by pointer" << std::endl;
	} else {
		std::cout << "Object C is identified by pointer" << std::endl;
	}
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "Object A is identified by reference" << std::endl;
		return;
	} catch (...) {}

	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "Object B is identified by reference" << std::endl;
		return;
	} catch (...) {}

	std::cout << "Object C is identified by reference" << std::endl;
}