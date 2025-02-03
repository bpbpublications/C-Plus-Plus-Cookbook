#include<concepts>
#include<utility>
#include<vector>
#include<functional>
#include <string>
#include <iostream>
#include <iterator>
#include <random>
#include <cstdlib>

#pragma region Chapter6_Section1
template<typename Fn>
concept Adjuster = std::invocable<Fn&, int>;

class Chapter6_1_1 {
private:
	static void PrintModifiedCalorieCounts(const std::vector<int>& calories, Adjuster auto adjuster) {
		for (auto& cal : calories) {
			std::cout << adjuster(cal) << std::endl;
		}
	}

public:
	static void LookAtCalorieCounts() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> calorieCounts{ 100, 222, 333, 4000 };
		PrintModifiedCalorieCounts(calorieCounts, [](int v) { return v + 10; });
	}
};

// reused from previous section
//template<typename Fn>
//concept Adjuster = std::invocable<Fn&, int>;

static bool CheckIfOdd(int value) { return value % 2; }

struct SomeAdjuster {
	int operator()(int value) { return value * 2; }
};

class Chapter6_1_2 {
private:
	static void PrintModifiedCalorieCounts(const std::vector<int>& calories, Adjuster auto adjuster) {
		for (auto& cal : calories) {
			std::cout << adjuster(cal) << ", ";
		}
		std::cout << std::endl << std::endl;
	}

public:
	static void LookAtCalorieCounts() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> calorieCounts{ 100, 222, 333, 4000 };
		PrintModifiedCalorieCounts(calorieCounts, [](int v) { return v + 10; });

		auto adjuster1 = [](int v) { return v * 2; };
		PrintModifiedCalorieCounts(calorieCounts, adjuster1);

		auto adjuster2 = [](int v) { return v / 4.2; };
		PrintModifiedCalorieCounts(calorieCounts, adjuster2);

		auto adjuster3 = [](int v) { return "# is:" + std::to_string(v / 2.0) + "!"; };
		PrintModifiedCalorieCounts(calorieCounts, adjuster3);

		PrintModifiedCalorieCounts(calorieCounts, CheckIfOdd);

		PrintModifiedCalorieCounts(calorieCounts, SomeAdjuster{});
	}
};
#pragma endregion Chapter6_Section1

#pragma region Chapter6_Section2
template < typename Fn>
concept Adjuster6_2 = std::regular_invocable<Fn&, int>;

class Chapter6_2 {
private:
	static void PrintModifiedCalorieCounts(const std::vector<int>& calories, Adjuster6_2 auto adjuster) {
		for (auto& cal : calories) {
			std::cout << adjuster(cal) << ", ";
		}
		std::cout << std::endl << std::endl;
	}

public:
	static void LookAtCalorieCounts() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> calorieCounts{ 100, 222, 333, 4000 };
		PrintModifiedCalorieCounts(calorieCounts, [](int v) { return v + 10; });

		auto adjuster1 = [](int v) { return v * 2; };
		PrintModifiedCalorieCounts(calorieCounts, adjuster1);

		auto adjuster2 = [](int v) { return v / 4.2; };
		PrintModifiedCalorieCounts(calorieCounts, adjuster2);

		auto adjuster3 = [](int v) { return "# is:" + std::to_string(v / 2.0) + "!"; };
		PrintModifiedCalorieCounts(calorieCounts, adjuster3);

		PrintModifiedCalorieCounts(calorieCounts, CheckIfOdd);

		PrintModifiedCalorieCounts(calorieCounts, SomeAdjuster{});
	}
};
#pragma endregion Chapter6_Section2

#pragma region Chapter6_Section3
template<typename Fn>
concept LowChecker = std::predicate<Fn&, int>;

class Chapter6_3 {
private:
	static void PrintModifiedCalorieCounts(const std::vector<int>& calories, LowChecker auto adjuster) {
		for (auto& cal : calories) {
			if (adjuster(cal)) {
				std::cout << cal << ", ";
			}
		}
		std::cout << std::endl << std::endl;
	}

public:
	static void LookAtLowCalorieCounts() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> calorieCounts{ 10, 22, 99, 333 };
		auto checkIfLow = [](int v) -> bool { return v < 70; };
		PrintModifiedCalorieCounts(calorieCounts, checkIfLow);
	}
};
#pragma endregion Chapter6_Section3

#pragma region Chapter6_Section4
// sample code not required
#pragma endregion Chapter6_Section4

#pragma region Chapter6_Section5
// sample code not required
#pragma endregion Chapter6_Section5

#pragma region Chapter6_Section6
// sample code not required
#pragma endregion Chapter6_Section6

#pragma region Chapter6_Section7
// sample code not required
#pragma endregion Chapter6_Section7

#pragma region Chapter6_Section8
// sample code not required
#pragma endregion Chapter6_Section8

#pragma region Chapter6_Section9
// sample code not required
#pragma endregion Chapter6_Section9

#pragma region Chapter6_Section10
// sample code not required
#pragma endregion Chapter6_Section10

void LookAtChapter6Topics() {
	// works with compiler?						when tested		clang	gcc		msvc
	Chapter6_1_1::LookAtCalorieCounts();	// 2023.11.05		yes		yes		yes
	Chapter6_1_2::LookAtCalorieCounts();	// 2023.11.05		yes		yes		yes
	Chapter6_2::LookAtCalorieCounts();		// 2023.11.05		yes		yes		yes
	Chapter6_3::LookAtLowCalorieCounts();	// 2023.11.05		yes		yes		yes
}
