#include <iostream>
#include <string>
#include <exception>
#include "Convert.hpp"
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error\nPlease use with 1 value" << std::endl;
		return (1);
	}

	std::string	input;

	input = argv[1];

	Convert conv(input);

	conv.print();


	return (0);
}