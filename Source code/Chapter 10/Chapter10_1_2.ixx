#include <iostream>

export module BPBPublishing.CPP23Book.Chapter10_1_2;

// even if from another module, the same class cannot be exported like this
//export class Chapter10_1_1 {
//public:
//	static void GiveWelcome() {
//		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
//		std::cout << "Welcome to C++23\n";
//	}
//};

export class Chapter10_1_2a {
public:
	static void GiveWelcome() {
		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
		std::cout << "Welcome to C++23!!!\n";
	}
};

export class Chapter10_1_2b {
public:
	static void GiveWelcomeAgain() {
		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
		std::cout << "Welcome to C++23 again\n";
	}
};