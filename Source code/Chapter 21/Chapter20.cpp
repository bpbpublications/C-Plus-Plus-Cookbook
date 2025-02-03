#include <concepts>
#include <iostream>
#ifdef __cpp_lib_print
#include <print>
#endif
#include <iomanip>
#include <ranges>
#include <algorithm>
#include <string>
#include <chrono>
#include <ctime>
#include <time.h>
#include <cassert>
#include <vector>
#include <ranges>
#include <thread>
#include <ranges>
#include <vector>
#include <limits>
#include <numeric>
#include <numbers>

#include <bit>
#include <cstdint>
#include <concepts>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <utility>
#ifdef __STDCPP_FLOAT16_T__
#include <stdfloat>
#endif
#include <array>
#include <charconv>
#include <string_view>
#include <system_error>
#include <expected>

#pragma region Chapter20_Section2
class DangerousThing {
private:
	int _v1;
	std::string _v2;
public:
	DangerousThing(int i1) : _v1(i1), _v2() {
		// perform long or resource-laden operation
	}
	DangerousThing(const std::string& s1) : _v2(s1), _v1() {
		// perform long or resource-laden operation
	}
	operator int() const { return _v1; }
};

class DangerousThing2 {
private:
	int _v1;
public:
	DangerousThing2() = default;
	DangerousThing2(int i1) : _v1(i1) {
		// perform long or resource-laden operation
	}
};

class Chapter20_2_1 {
private:
	static void WorkOnDangerousThing(const DangerousThing& dt) {}
	static void WorkOnDangerousThing2(const DangerousThing2& dt) {}

public:
	static void LookAtExplicit_Recap_WithoutExplicit() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		DangerousThing dt1 = DangerousThing(1);
		DangerousThing dt2{ 2 };
		DangerousThing dt3 = 3;
		WorkOnDangerousThing(4);
		/*does not compile, since cannot implicity convert from const char* to string,
			and then to DangerousThing */
		// WorkOnDangerousThing("Hello");
		// 
		WorkOnDangerousThing(std::string("Hello")); // this works because explicitly creating a string, which can be used to implicitly create DangerousThing
		WorkOnDangerousThing(DangerousThing("Hello")); // this works because only doing 1 implicit conversion from const char* to string
		int oddOperation = 1 + dt1;

		WorkOnDangerousThing2({});
	}
};

class SaferThing {
private:
	int _v1;
	std::string _v2;
public:
	explicit SaferThing() = default;
	explicit SaferThing(int i1) : _v1(i1), _v2() {}
	explicit SaferThing(const std::string& s1) : _v2(s1), _v1() {}
	explicit operator bool() const { return true; }
	explicit operator int() const { return _v1; }
};

class Chapter20_2_2 {
private:
	static void WorkOnSaferThing(const SaferThing& dt) {}

public:
	static void LookAtExplicit_Recap_UsingExplicit() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		SaferThing st1 = SaferThing(1);
		SaferThing st2{ 2 };
		// these no longer works because cannot do implicitly
		// SaferThing st3 = 3;
		// WorkOnSaferThing(4);
		//
		WorkOnSaferThing(SaferThing("Hello"));

		SaferThing ot1(1);
		if (ot1) {} // can be use because of operator bool
		//bool flag3 = ot1; // can be used in an if-block as above, but not to capture the value
		//const bool flag4 = ot1; // even const bool cannot capture value of operator function
		// int oddOperation = 1 + ot1; // does not compile, since cannot add different types
		int oddOperation = 1 + int(ot1);
	}
};

template <typename T>
class SafeAndEasierThing {
public:
	SafeAndEasierThing() = default;
	explicit(!std::is_trivial_v<T>) SafeAndEasierThing(T&& t) : value(std::move(t)) {	}
	explicit(!std::is_trivial_v<T>) SafeAndEasierThing(const T& t) : value(t) {}
	//explicit(sizeof(T) < 10) SafeAndEasierThing(const T& t) : value(t) {} // possible option for constructor

	explicit(!std::is_trivial_v<T>) operator T() const { return value; }
private:
	T value;
};

class Chapter20_2_3 {
private:
	static void WorkWithSafeAndEasierThing(const SafeAndEasierThing<int>& a) {}
	template <typename T2>
	static void WorkWithSafeAndEasierThing(const SafeAndEasierThing<T2> a) { }

public:
	static void LookAtSaferAndEasierThing() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		WorkWithSafeAndEasierThing(1); // does allow trivial creation of SafeAndEasierThing that can be passed to function
		// WorkWithSafeAndEasierThing(DangerousThing{1}); // cannot create SafeAndEasierThing from non-trivial
		SafeAndEasierThing<DangerousThing> st1{ DangerousThing { 1 } };
		WorkWithSafeAndEasierThing(st1);
	}
};

class Chapter20_2 {
public:
	static void LookAtExplicit() {
		Chapter20_2_1::LookAtExplicit_Recap_WithoutExplicit();
		Chapter20_2_2::LookAtExplicit_Recap_UsingExplicit();
		Chapter20_2_3::LookAtSaferAndEasierThing();
	}
};
#pragma endregion Chapter20_Section2

#pragma region Chapter20_Section3
#define CurrentLevel 123
#define TargetLevel  130

class Chapter20_3 {
public:
	static void LookAtWarning() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if __cplusplus >= 202302L
#if CurrentLevel < TargetLevel
		#warning "Code may not build, or work, as hoped"
#endif
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};
#pragma endregion Chapter20_Section3


class Chapter20_4 {
public:
	static void LookAtLifetimes() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if __cpp_lib_start_lifetime_as	>= 202207L
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

#ifdef For_Example_Only
// C code in another file
void c_api_delete_handle(int* handle);
struct resource_deleter {
	void operator()(int* handle) {
		c_api_delete_handle(handle);
	}
};

// C++ code
class Chapter20_5 {
public:
	static void LookAtOutPtr() {
		// C++ code
		std::unique_ptr<int, resource_deleter> resource(nullptr);
		auto errNumber = c_api_create_handle(
			24, std::out_ptr(resource)
		);
	}
};
#endif

class Chapter20_6_1 {
private:
	static void PrintOutChars(const auto... args)
	{
		std::array<char, 10> strBuffer;

		std::to_chars_result result = std::to_chars(strBuffer.data(), strBuffer.data() + strBuffer.size(), args...);
		if (result.ptr != nullptr) {
			std::cout << std::quoted(std::string_view(strBuffer.data(), result.ptr)) << '\n';
		}
		else {
			std::cout << std::make_error_code(result.ec).message() << '\n';
		}
	}

public:
	static void LookAtToChars_recap() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		const float pi = 3.14159F;
		PrintOutChars(37);
		PrintOutChars(-pi);
		PrintOutChars(-pi, std::chars_format::fixed);
		PrintOutChars(-pi, std::chars_format::scientific, 3);
		PrintOutChars(3.1415926535, std::chars_format::fixed, 6);
	}
};

class Chapter20_6_2 {
public:
	static void LookAtToChars() {
		Chapter20_6_1::LookAtToChars_recap();

		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::array<char, 10> strBuffer;
#if __cpp_lib_constexpr_charconv >= 202207L
		std::to_chars_result result = std::to_chars(strBuffer.data(), strBuffer.data() + strBuffer.size(), 42);
		if (result.ptr != NULL) {
			std::cout << "Result=" << std::string_view(strBuffer.data(), result.ptr) << std::endl;
		}
		else {
			std::cout << "Problem" << std::make_error_code(result.ec).message() << std::endl;
		}
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

#ifdef __cpp_lib_expected
template<typename T>
std::expected<int, std::string> ParseTextToNumber(const std::string_view s) {
	T value{};
	std::from_chars_result result = std::from_chars(s.data(), s.data() + s.size(), value);
	if (result.ec == std::errc{}) {
		return value;
	}
	else {
		return std::unexpected(std::make_error_code(result.ec).message());
	}
}
#endif

class Chapter20_6_3 {
public:
	static void LookAtFromChars() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

#ifdef __cpp_lib_expected
		{
			std::cout << "Looking at integers" << std::endl;
			auto intStrs = { "42", "123456789012345", "2023C++31" };
			for (auto str : intStrs) {
#if __cpp_lib_constexpr_charconv >= 202207L
				auto result = ParseTextToNumber<int>(str);
				if (result.has_value()) {
					std::cout << "For input" << std::quoted(str) << ", parsed value: " << result.value() << std::endl;
				}
				else {
					std::cout << "For input" << std::quoted(str) << ", got error: " << result.error() << std::endl;
				}
#else
				std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
			}
		}

		{
			std::cout << "Looking at floats" << std::endl;
			auto floatStrs = { "42.37", "123456789012345", "2023C++31" };
			for (auto str : floatStrs) {
#if __cpp_lib_constexpr_charconv >= 202207L
				auto result = ParseTextToNumber<float>(str);
				if (result.has_value()) {
					std::cout << "For input" << std::quoted(str) << ", parsed value: " << result.value() << std::endl;
				}
				else {
					std::cout << "For input" << std::quoted(str) << ", got error: " << result.error() << std::endl;
				}
#endif
			}
		}
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

class Chapter20_7 {
public:
	static void LookAtBitSet() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		constexpr std::bitset<8> b1{ "00101010" };
		static_assert(b1 == 42);
	}
};

class Chapter20_8 {
public:
	static void LookAtToUnderlying() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		enum class Meal : char {
			Breakfast,
			Lunch,
			Dinner,
		};
		static_assert(std::is_same_v<char, decltype(std::to_underlying(Meal::Breakfast))>);

		enum struct Cutlery : long {
			SoupSpoon,
			DessertSpoon,
			ButterKnife,
			OysterFork,
			SaladFork,
			DinnerFork,
			DinnerKnife,
			DessertFork,
		};
		static_assert(std::is_same_v<long, decltype(std::to_underlying(Cutlery::SaladFork))>);

		enum PastaNoodle : unsigned {
			AngelHair,
			EggNoodle,
			Fettuccine,
			Fusilli,
			Lasagna,
			Linguine,
			Macaroni,
			Manicotti,
			Orzo,
			Penne,
			Rigatoni,
			Rotelle,
			Rotini,
			Spaghetti,
		};
		static_assert(std::is_same_v<unsigned, decltype(std::to_underlying(AngelHair))>);
	}
};

#pragma region Chapter20_Section9
struct Thing {
	Thing() = delete;
};
struct OtherThing {
	int x;
	int y;
};
struct Dish {};
struct Menu {
	// other code
	std::vector<Dish> GetSpecials() { return std::vector<Dish>{}; }
};
Menu GetMenu() { return Menu{}; }
OtherThing GetOtherThing() { return OtherThing{}; }

class Chapter20_9 {
public:
	static void LookAtInitialization() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		// Thing t1; // cannot create because constructor is deleted
		// Thing t2 {}; // after C++17, can no longer instantiate with aggregate initialization

		OtherThing ot1(42, 67);
		OtherThing ot2{ 42, 67 };

		int numbers1[4](27, 37, 42, 67);
		int numbers2[4]{ 27,37,42,67 };

		//for (auto&& special : GetMenu().GetSpecials()) { // may not be safe
		for (auto menu = GetMenu(); auto && special : menu.GetSpecials()) {
		}

		auto [x, y] = GetOtherThing();
		static auto [x2, y2] = GetOtherThing(); // now works in C++20
		thread_local auto [x3, y3] = GetOtherThing(); // now works in C++20
		auto fn = [x] { return x > 42; }; // fixed problem that this did not work in C++17
	}
};
#pragma endregion Chapter20_Section9


void LookAtChapter20Topics() {
	// works with compiler?					when tested		clang	msvc	gcc
	Chapter20_2::LookAtExplicit();			// 2023.12.04	yes		yes		yes
	Chapter20_3::LookAtWarning();			// 2023.12.04	yes		no		yes
	Chapter20_4::LookAtLifetimes();			// 2023.12.04	no		no		no
	Chapter20_6_2::LookAtToChars();			// 2023.12.04	yes		yes		yes
	Chapter20_6_3::LookAtFromChars();		// 2023.12.04	maybe	yes		yes
	Chapter20_7::LookAtBitSet();			// 2023.12.04	yes		yes		yes
	Chapter20_8::LookAtToUnderlying();		// 2023.12.04	yes		yes		yes
	Chapter20_9::LookAtInitialization();	// 2023.12.04	yes		yes		yes
}
