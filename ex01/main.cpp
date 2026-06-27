#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main(void) {
	Data data;
	data.id = 1234;
	data.name = "test";

	std::cout << "=========Serialize and Deserialize========="<< std::endl;
	Data* ptr = &data;
	std::cout << "Original ptr address: " << ptr << std::endl;
	uintptr_t raw = Serializer::serialize(ptr);
	std::cout << "Raw number after serialization: " << raw << std::endl;
	Data* deserialized_ptr = Serializer::deserialize(raw);
	std::cout << "Deserialized ptr address: " << deserialized_ptr << std::endl;
	std::cout << "Deserialized data id: " << deserialized_ptr->id << std::endl;
	std::cout << "Deserialized data name: " << deserialized_ptr->name << std::endl;

	std::cout << "======Deserialized ptr same as original======"<< std::endl;
	deserialized_ptr->id = 5678;
	deserialized_ptr->name = "new";
	std::cout << "Original data id: " << ptr->id << std::endl;
	std::cout << "Original data name: " << ptr->name << std::endl;

	return 0;
}