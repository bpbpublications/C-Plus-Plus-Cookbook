module;
#include <iostream>

export module Module10_1_1;

export class Chapter10_1_1 {
public:
	static void GiveWelcome() {
		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
		std::cout << "Welcome to C++23\n";
	}
};