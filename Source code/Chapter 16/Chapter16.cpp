#include <iostream>
#include <ranges>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <cctype>
#include <concepts>
#include <format>
#ifdef __cpp_lib_generator
#include <generator>
#endif
#include <numeric>
#ifdef __cpp_lib_print
#endif

static void PrintView(std::string title, auto view) {
	auto PrintValues = [](auto n) { std::cout << n << ", "; };

	std::cout << title << ": ";
	for (auto i : view) {
		PrintValues(i);
	}
	std::cout << std::endl;
}

static void LookAtRepeatAndCartesianProduct() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl; 
#ifdef __cpp_lib_ranges_repeat
	PrintView("Easy as", std::ranges::views::repeat(1, 3));
	PrintView("What do you think of this release", std::ranges::views::repeat("C++23 is great!\n", 5));
	PrintView("Countdowns", std::ranges::views::repeat(54321) | std::views::take(4));
//#else  // since your compiler hasn't implemented it ywt, we are just showing what the output would look like
//	std::cout << "Easy as: " << 1 << ", " << 1 << ", " << 1 << ", " << std::endl;
//	std::cout << "What do you think of this release: " << "C++23 is great!\n" << "C++23 is great!\n" << "C++23 is great!\n"
//		<< "C++23 is great!\n" << "C++23 is great!\n" << std::endl;
//	std::cout << "Countdowns: " << 54321 << ", " << 54321 << ", " << 54321 << ", " << 54321 << ", " << std::endl;
#endif
	std::cout << std::endl;

	auto meats = std::array<std::string,2>{ "spicy sausage", "ham" };
	auto cheeses = std::vector<std::string>{ "sharp cheddar", "gruyere" , "feta" };
	auto vegetables = std::deque<std::string>{ "spinach", "tomato" , "mushrooms" };
#ifdef __cpp_lib_ranges_cartesian_product
	for (auto n{1}; auto const & [meat, cheese, veg] : std::views::cartesian_product(meats, cheeses, vegetables)) {
		std::cout << "{" << meat << " & " << cheese << " & " << veg << "}";
		std::cout << (n++ % 4 ? "\n" : ", ");
	}
//#else  // since your compiler hasn't implemented it ywt, we are just showing what the output would look like
//	auto meatCount{ 0 }, cheeseCount{ 0 }, vegetableCount{ 0 };
//	do {
//		do {
//			do {
//				std::cout << '\"' << meats[meatCount] << " & " << cheeses[cheeseCount]
//					<< " & " << vegetables[vegetableCount] << "\"";
//				std::cout << ", ";
//			} while (++vegetableCount < vegetables.size());
//			std::cout /*<< "."*/ << std::endl;
//			vegetableCount = 0;
//
//		} while (++cheeseCount < cheeses.size());
//		cheeseCount = 0;
//
//	} while (++meatCount < meats.size());
#endif
}

static void LookAtIota() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	PrintView("Easy as", std::views::iota(1, 4));
	PrintView("Easy as", std::views::iota('a', 'd'));

	auto numbers = std::views::iota(2, 9) | std::views::stride(2);
	PrintView("Doubled", numbers);
	auto numbers2 = std::views::iota(1, 5) | std::views::transform([](int n) {return n * 2; });
	PrintView("More doubled", numbers2);
	auto almostUnlimitedNumbers = std::views::iota(2) | std::views::stride(2) | std::views::take(4);
	PrintView("Still more doubled", almostUnlimitedNumbers);
}

#if defined(__cpp_lib_generator) && defined(__cpp_lib_shift)
std::generator<int> FibonacciGenerator() {
	std::vector<int> fibSet{ 0,1 };
	auto result = fibSet[0];
	auto next = std::accumulate(fibSet.begin(), fibSet.end(), 0);
	std::ranges::shift_left(fibSet, 1);
	fibSet[1] = next;
	co_yield result;
}
#endif

static void LookAtGenerator() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if defined(__cpp_lib_generator) && defined(__cpp_lib_shift)
	auto gen{ FibonacciGenerator() };
	PrintView("Some Fibonacci numbers", gen | std::views::take(10));
//#else 
//	std::cout << "since your compiler hasn't implemented it ywt, we are just showing what the output would look like" << std::endl;
//	auto n{ 0 };
//	std::vector<int> fibSet{ 0,1 };
//	while (n < 10) {
//		std::cout << fibSet[0] << ", ";
//		auto next = std::accumulate(fibSet.begin(), fibSet.end(), 0);
//		std::ranges::shift_left(fibSet, 1);
//		fibSet[1] = next;
//		n++;
//	}
//	std::cout << std::endl;
#endif
}

static void LookAtRangeFormat() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	// https://en.cppreference.com/w/cpp/23#C.2B.2B23_library_features
#if defined(  __cpp_lib_format)
#ifdef __clang__	// in Oct 2023, it was sometimes working in the clang (widberg) version in godbolt, but not clang the clang (trunk)
	//https://www.youtube.com/watch?v=EQELdyecZlU&t=3069s
	std::vector<std::string> breads { "sourdough", "brioche", "naan" };
	std::cout << std::format("{}\n", breads) << std::endl; 

	//https://youtu.be/b0NkuoUkv0M?t=1173
	std::vector<std::pair<std::string, int>> breadRankingsV { {"sourdough", 1}, { "brioche",3 }, { "naan",2 } };
	std::cout << std::format("{}\n", breadRankingsV) << std::endl;

	std::set<std::pair<std::string, int>> breadRankingsS { {"sourdough", 1}, { "brioche",3 }, { "naan",2 } };
	std::cout << std::format("{}\n", breadRankingsS) << std::endl;

	std::map<std::string, int> breadRankingsM { {"sourdough", 1}, { "brioche",3 }, { "naan",2 } };
	std::cout << std::format("{}\n", breadRankingsM) << std::endl;
	std::cout << std::endl;

	std::vector<uint8_t> mac{ 0xc0, 0xab, 0x17, 0x2a };
	std::cout << "The mac address is: " << std::format("{}", mac) << std::endl;
	std::cout << "The hex value mac address is: " << std::format("{::02x}", mac) << std::endl;
	std::cout << "The no brackets, hex value mac address is: " << std::format("{:n:02x}", mac) << std::endl;
	std::cout << "The delimited hex value mac address is: " << std::format("{:02x}", mac) << std::endl;
	std::cout << std::endl;

	std::deque<std::vector<int>> multipleValues{ {1,2,3}, {4,6,8}, {42,67,255} };
	std::cout << "Values are: " << std::format("{}", multipleValues) << std::endl;
	std::cout << "Hex values are: " << std::format("{:#x}", multipleValues) << std::endl;
	std::cout << "No bracket, filled hex values are: " << std::format("{n:!22:#x}", multipleValues) << std::endl;
#endif
//#else // since your compiler hasn't implemented it ywt, we are just showing what the output would look like
//	std::cout << "[sourdough, brioche, naan]" << std::endl;
//	std::cout << "[(sourdough,1), (brioche,3), (naan,2)]" << std::endl;
//	std::cout << "[(sourdough,1), (brioche,3), (naan,2)]" << std::endl;
//	std::cout << "{sourdough: 1, brioche: 3, naan: 2}" << std::endl;
//	std::cout << std::endl;
//	std::cout << "The mac address is: [192, 168, 23, 42]" << std::endl;
//	std::cout << "The hex value mac address is: [c0, ab, 17, 2a]" << std::endl;
//	std::cout << "The no brackets, hex value mac address is: c0, ab, 17, 2a" << std::endl;
//	std::cout << "The delimited hex value mac address is: c0:ab:17:2a" << std::endl;
//	std::cout << std::endl;
//	std::cout << "Values are: [ [1, 2, 3], [4, 6, 8], [42, 67, 255] ]" << std::endl;
//	std::cout << "Hex values are: [ [0x01, 0x02, 0x03], [0x04, 0x06, 0x08], [0x2a, 0x43, 0xff] ]" << std::endl;
//	std::cout << "No bracket, filled hex values are: !![0x01, 0x02, 0x03]!!, !![0x04, 0x06, 0x08]!!, !![0x2a, 0x43, 0xff]!!" << std::endl;
#endif
}

struct NumberHolder {
	int n;  
};
static void LookAtSwapRanges() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::vector<int> numbersOdd{ 17, 37, 67, 99 };
	std::vector<int> numbersEven{ 2, 34, 42, 88 };

	PrintView("odd values", numbersOdd);
	PrintView("even values", numbersEven);
	std::ranges::swap(numbersOdd, numbersEven);
	PrintView("what were odd values", numbersOdd);
	PrintView("what were even values", numbersEven);
	std::swap_ranges(numbersOdd.begin(), numbersOdd.end(), numbersEven.begin());
	PrintView("odd values after swap_ranges", numbersOdd);
	PrintView("even values after swap_ranges", numbersEven);
	std::cout << std::endl;

	std::vector<int> easyNumbers{ 1, 2, 3 };
	PrintView("easy values before", easyNumbers);
	std::ranges::swap(numbersOdd, easyNumbers);
	PrintView("what were odd values", numbersOdd);
	PrintView("what were easy values", easyNumbers);
	std::cout << std::endl;

	std::array array1{ 99,98,97 };
	std::array array2{ 96,95,94 };
	std::array array3{ 93,92 };
	PrintView("array1 before", array1);
	PrintView("array2 before", array2);
	PrintView("array3 before", array3);
	std::ranges::swap(array1, array2);
	PrintView("array1 after 1-2 swap", array1);
	PrintView("array2 after 1-2 swap", array2);
	// cannot swap different sizes for all container types
	// std::ranges::swap(array1, array3);
	std::ranges::swap_ranges(array1, array3);
	PrintView("array1 after 1-3 swap_ranges", array1);
	PrintView("array2 after 1-3 swap_ranges", array3);
	std::cout << std::endl;

	const std::vector<int> hardNumbers{ 7, 7, 8, 10 };
	// cannot swap, since one instance is const
	// std::ranges::swap(numbersOdd, hardNumbers);
	// std::ranges::swap_ranges(numbersOdd, hardNumbers);
	// std::swap_ranges(numbersOdd.begin(), numbersOdd.end(), hardNumbers.begin());

	std::deque<int> otherNumbers{ 1, 2, 3 };
	// will not compile, since cannot swap between these different containers
	// std::ranges::swap(numbersOdd, otherNumbers);
	PrintView("numbersEven before", numbersEven);
	PrintView("otherNumbers before", otherNumbers);
	auto otherNumbersSwapResult = std::ranges::swap_ranges(numbersEven, otherNumbers);
	PrintView("numbersEven after ranges::swap_ranges", numbersEven);
	PrintView("otherNumbers after ranges::swap_ranges", otherNumbers);

	NumberHolder numbersHeld[]{ 101, 102, 103 };
	int digits[]{ 1,2,3 };
	// works on some compilers
	// std::ranges::swap(digits, numbersHeld);
	// std::ranges::swap_ranges(numbersHeld, digits);
	// std::swap_ranges(numbersHeld.begin(), numbersHeld.end(), digits.begin());
}

static void LookAtRangesTo() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	auto LessThan99 = [](auto n) { return n < 99; };
	auto Doubler = [](auto n) { return n * 2; };
	std::deque<int> source{ 17, 37, 67, 99 };

	PrintView("source", source);
	auto result = source | std::views::filter(LessThan99) | std::views::transform(Doubler)
		| std::ranges::to<std::vector>();
	PrintView("source after work", source);
	PrintView("result of work", result);
	std::cout << "Result type= " << typeid(result).name() << std::endl;
}

void LookAtChapter16Topics()
{
	// Does it work with your compiler?			when tested			clang			gcc			msvc
	LookAtIota();							//	2023.10.21			yes				yes			no
	LookAtRepeatAndCartesianProduct();		//	2023.10.21			yes				no			yes
	LookAtGenerator();						//	2023.10.21			no				no			no
	LookAtRangeFormat();					//	2023.10.21			maybe*			no			no	* with clang (widberg) on godbolt, not the trunk
	LookAtSwapRanges();						//	2023.10.21			yes				yes			yes
	LookAtRangesTo();						//	2023.10.21			no				no			yes
}
