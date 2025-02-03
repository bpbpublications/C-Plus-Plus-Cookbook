export module Module10_7_2;

#ifdef NOT_FULLY_WORKING_YET
// https ://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170
import std.compat;
#else
import std.core;
#endif

export class Class10_7_2 {
public:
	static void UseStdCompat() {
		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;

		std::string message = "Hello C++23";
		std::cout << message << std::endl;
		std::vector<int> numbers(5);
	}
};