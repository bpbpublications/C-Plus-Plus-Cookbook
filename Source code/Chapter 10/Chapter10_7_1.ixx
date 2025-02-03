export module Module10_7_1;

import std.core;

export class Class10_7_1 {
public:
	static void UseStd() {
		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;

		std::string message = "Hello C++23";
		std::cout << message << std::endl;
		std::vector<int> numbers(5);
	}
};