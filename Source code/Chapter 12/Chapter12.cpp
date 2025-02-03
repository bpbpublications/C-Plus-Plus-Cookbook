#include <iostream>
#include <ranges>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <unordered_set>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <functional>
#include <numeric>
#include <cmath>

class Chapter12_1_1 {
private:
	static void WalkTheRange(std::string title, std::ranges::range auto r) {
		using R = decltype(r);
		using Elem = std::ranges::range_value_t<R>;
		std::cout << "Looking at range for " << title << " / "
			<< typeid(R).name() << std::endl
			<< " of " << typeid(Elem).name()
			<< ", size=" << std::ranges::size(r) << ", ssize=" << std::ranges::ssize(r)
			<< ", empty=" << std::boolalpha << std::ranges::empty(r)
			<< std::endl;
		for (auto it = std::ranges::begin(r); it != std::ranges::end(r); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl << std::endl;
	}

public:
	static void LookAtBasics() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<int> myVector = { 17, 31, 37, 42, 67 };
		WalkTheRange("vector", myVector);
		//
		int cArray[] = { 17, 31, 37, 42, 67 };
		auto cArrayCount = sizeof(cArray) / sizeof(int);
		auto sub = std::ranges::subrange(cArray, cArrayCount);
		WalkTheRange("C style array (via subrange)", sub);
		//
		std::list<double> myList = { 17.1, 31.2, 37.3, 42.4, 67.5 };
		WalkTheRange("list", myList);
		//
		std::deque<int> myQueue = { 17, 31, 37, 42, 67 };
		WalkTheRange("deque", myQueue);
		//
		std::unordered_set<std::string> mySet = { "Hello", "World", "how", "are", "you?" };
		WalkTheRange("set", mySet);
		//
		// does not work with range functionality yet
		//std::map<char, std::string> myMap = { { '1', "Hello" }, {'2', "World"} };
		//WalkTheRange("map", myMap);
	}
};

class Chapter12_1_2 {
private:
	static void WalkTheReverseRange(std::string title, std::ranges::range auto r) {
		using R = decltype(r);
		using Elem = std::ranges::range_value_t<R>;
		std::cout << "Looking at range for " << title << " / "
			<< typeid(R).name() << std::endl
			<< " of " << typeid(Elem).name()
			<< ", size=" << std::ranges::size(r) << ", ssize=" << std::ranges::ssize(r)
			<< ", empty=" << std::boolalpha << std::ranges::empty(r)
			<< std::endl;
#ifdef _MSC_VER
		for (auto it = std::ranges::crbegin(r); it != std::ranges::crend(r); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
#endif
	}

public:
	static void LookAtBasicsInReverse() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		std::vector<int> myVector = { 17, 31, 37, 42, 67 };
		WalkTheReverseRange("vector", myVector);
		//
		int cArray[] = { 17, 31, 37, 42, 67 };
		auto cArrayCount = sizeof(cArray) / sizeof(int);
		auto sub = std::ranges::subrange(cArray, cArrayCount);
		WalkTheReverseRange("C style array (via subrange)", sub);
		//
		std::list<double> myList = { 17.1, 31.2, 37.3, 42.4, 67.5 };
		WalkTheReverseRange("list", myList);
		//
		std::deque<int> myQueue = { 17, 31, 37, 42, 67 };
		WalkTheReverseRange("deque", myQueue);
		//
		std::unordered_set<std::string> mySet = { "Hello", "World", "how", "are", "you?" };
		WalkTheReverseRange("set", mySet);
	}
};

class Chapter12_1_3 {
public:
	static void LookAtData() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		std::string input{ "Hello C++23" };
		char* ptr = std::ranges::data(input);

		// does not compile, since cannot set non-const pointer to const ptr
		//char* ptr = std::ranges::cdata(input);
		const char* cptr = std::ranges::cdata(input);
		std::cout << "Input is: " << ptr << std::endl
			<< "and so is:" << cptr << std::endl << std::endl;
	}
};

#pragma region Chapter12_2
struct Sum
{
	void operator()(int n) { sum += n; }
	int sum{ 0 };
};

struct Append
{
	void operator()(std::string w) { sentence += w + " "; }
	std::string sentence{};
};

struct AppendLoudly
{
	void operator()(std::string& w)
	{
		std::transform(w.begin(), w.end(), w.begin(), ::toupper);
		sentence += w + " ";
	}
	std::string sentence{};
};

class Chapter12_2_1 {
public:
	static void DoForEach() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		std::vector<std::string> myWords = { "C++", "23", "is", "a", "great", "release" };

		auto PrintFn = [](const auto& w) { std::cout << w << std::endl; };
		std::cout << "The words being printed separately:" << std::endl;
		std::ranges::for_each(myWords, PrintFn);
		std::cout << std::endl;

		auto [it, output] = std::ranges::for_each(myWords, Append());
		std::cout << "The sentence being printed:" << std::endl;
		std::cout << output.sentence;
		if (it == myWords.end()) {
			std::cout << "!" << std::endl;
		}
		std::cout << std::endl;

		auto sub = std::ranges::subrange(myWords, myWords.size());
		auto [itLoud, outputLoud] = std::ranges::for_each(sub, AppendLoudly());
		//auto [itLoud, outputLoud] = std::ranges::for_each(myWords, AppendLoudly());
		std::cout << "The words being printed again:" << std::endl;
		std::ranges::for_each(myWords, PrintFn);
		std::cout << "The sentence being shouted:" << std::endl;
		std::cout << outputLoud.sentence;
		if (itLoud == myWords.end()) {
			std::cout << "!" << std::endl;
		}
	}
};

class Chapter12_2_2 {
public:
	static void DoForEachN() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		std::deque<int> myQueue = { 17, 31, 37, 42, 67 };

		auto PrintFn = [](const auto& n) { std::cout << n << " "; };
		auto DoubleFn = [](auto& n) { n *= 2; };

		std::ranges::for_each_n(myQueue.begin(), myQueue.size(), PrintFn);
		std::cout << std::endl;

		std::ranges::for_each_n(myQueue.begin(), 3, DoubleFn);

		std::ranges::for_each_n(++(myQueue.rbegin()), 4, PrintFn);
		std::cout << std::endl;
	}
};
#pragma endregion Chapter12_2

class Chapter12_3_1 {
public:
	static void DoCounts() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<std::string> dishes = {
			"Linguine with cream sauce",
			"Macaroni and cheese",
			"Chef salad",
			"Chicken with 2 buttermilk biscuits",
			"Tomato soup",
			"Broiled chicken",
			"Escargot topped with garlic butter" };

		std::vector<size_t> dishLengths;
		for (const auto& d : dishes) {
			dishLengths.push_back(d.length());
		}

		const auto lengthToLookFor = 34;
		auto longDishCount = std::ranges::count(dishLengths.begin(), dishLengths.end(), lengthToLookFor);
		std::cout << "Found " << longDishCount << " dishes that were " << lengthToLookFor << std::endl;

		auto NonDairyCountFn = [](const auto& d) { return not
			(d.find("cream") != std::string::npos
				|| d.find("cheese") != std::string::npos
				|| d.find("butter") != std::string::npos
				|| d.find("milk") != std::string::npos); };
		size_t nonDairyDishCount = std::ranges::count_if(
			dishes.begin(), dishes.end(), NonDairyCountFn);
		std::cout << "Found " << nonDairyDishCount <<
			" dishes that did not contain: cheese, milk, cream, or butter" << std::endl;
	}
};

class Chapter12_3_2 {
public:
	static void DoAnyAllNone() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<std::string> menu1 = {
			"Linguine with cream sauce",
			"Macaroni and cheese",
			"Chef salad",
			"Chicken with 2 buttermilk biscuits",
			"Tomato soup",
			"Broiled chicken",
			"Escargot topped with garlic butter" };

		const std::vector<std::string> menu2 = {
		"Linguine with cream sauce",
		"Macaroni and cheese",
		"Chicken with 2 buttermilk biscuits",
		"Escargot topped with garlic butter" };

		const std::vector<std::string> menu3 = {
		"Chef salad",
		"Tomato soup",
		"Broiled chicken" };

		const auto IsDairyFn = [](const auto& d) { return
			(d.find("cream") != std::string::npos
				|| d.find("cheese") != std::string::npos
				|| d.find("butter") != std::string::npos
				|| d.find("milk") != std::string::npos); };
		auto PrintFn = [](const auto& s) { std::cout << s << ", "; };

		for (const auto& menu : { menu1, menu2, menu3 }) {
			auto anyOfResult = std::ranges::any_of(menu, IsDairyFn);
			auto allOfResult = std::ranges::all_of(menu, IsDairyFn);
			auto noneOfResult = std::ranges::none_of(menu, IsDairyFn);

			std::cout << "For our menu choices: ";
			std::ranges::for_each(menu, PrintFn);
			std::cout << std::endl;

			std::cout << "Any have dairy is " << std::boolalpha << anyOfResult << std::endl;
			std::cout << "All have dairy is " << std::boolalpha << allOfResult << std::endl;
			std::cout << "None have dairy is " << std::boolalpha << noneOfResult << std::endl;
			std::cout << std::endl;
		}
	}
};

class Chapter12_4_1 {
public:
	static void LookForMismatch() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::deque<int> myQueue1 = { 17, 31, 37, 42, 67 };
		const std::deque<int> myQueue2 = { 17, 31, 37, 24, 67 };

		const auto PrintFn = [](const auto& n) { std::cout << n << ", "; };

		auto result = std::ranges::mismatch(myQueue1, myQueue2);

		std::cout << "Range stopped matching for queue1 at:";
		std::ranges::for_each(myQueue1.begin(), ++result.in1, PrintFn);
		std::cout << std::endl;
		std::cout << "Range stopped matching for queue2 at:";
		std::ranges::for_each(myQueue2.begin(), ++result.in2, PrintFn);
		std::cout << std::endl;
	}
};

class Chapter12_4_2 {
public:
	static void LookAtEqual() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::deque<int> myQueue1 = { 17, 31, 37, 42, 67 };
		const std::deque<int> myQueue2 = { 17, 31, 37, 24, 67 };
		const std::deque<int> myQueue3 = { 17, 31, 37, 42, 67 };
		const std::vector<std::deque<int>> queues = { myQueue1, myQueue2, myQueue3 };

		const auto PrintFn = [](const auto& n) { std::cout << n << ", "; };
		for (int i = 0; i <= 2; i++) {
			std::cout << "Printing container #" << i + 1 << ": ";
			auto currentQueue = queues[i];
			std::ranges::for_each(currentQueue, PrintFn);
			std::cout << std::endl;
		}

		auto result12 = std::ranges::equal(myQueue1, myQueue2);
		auto result23 = std::ranges::equal(myQueue2, myQueue3);
		auto result13 = std::ranges::equal(myQueue1, myQueue3);

		std::cout << "Queue1 and queue2 are equal is " << std::boolalpha << result12 << std::endl;
		std::cout << "Queue2 and queue3 are equal is " << std::boolalpha << result23 << std::endl;
		std::cout << "Queue1 and queue3 are equal is " << std::boolalpha << result13 << std::endl;
	}
};

class Chapter12_4_3 {
public:
	static void LookAtLexographicalCompare() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		std::vector<char> v1{ 'a', 'b', 'c', 'd' };
		std::vector<char> v2{ 'A', 'b', 'c', 'd' };
		std::vector<char> v3{ 'a', 'b', 'c', 'd', 'e' };
		std::vector<char> v4{ 'x', 'y', 'z' };
		std::vector<std::vector<char>> vs = { v1, v2, v3, v4 };

		auto PrintFn = [](const auto& c) { std::cout << c << ", "; };
		int i = 1;
		for (const auto& currentContainer : vs) {
			std::cout << "Printing container #" << i++ << ": ";
			std::ranges::for_each(currentContainer, PrintFn);
			std::cout << std::endl;
		}

		auto result12 = std::ranges::lexicographical_compare(v1, v2);
		auto result11 = std::ranges::lexicographical_compare(v1, v1);
		auto result13 = std::ranges::lexicographical_compare(v1, v3);
		auto result14 = std::ranges::lexicographical_compare(v1, v4);

		std::cout << "Container1 < Container2 is " << std::boolalpha << result12 << std::endl;
		std::cout << "Container1 < Container3 is " << std::boolalpha << result13 << std::endl;
		std::cout << "Container1 < Container4 is " << std::boolalpha << result14 << std::endl;
		std::cout << "Container1 < Container1 is " << std::boolalpha << result11 << std::endl;
	}
};

class Chapter12_5_1 {
public:
	static void LookAtFind() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::deque<int> myQueue = { 17, 34, 37, 42, 67, 88 };
		auto IsMultipleOfSeven = [](int n) { return n % 7 == 0; };
		auto IsMultipleOfSeventeen = [](int n) { return n % 17 == 0; };
		auto PrintFn = [](const auto& n) { std::cout << n << ", "; };

		std::cout << "Full range: ";
		std::ranges::for_each(myQueue, PrintFn);
		std::cout << std::endl;

		bool found37 = std::ranges::find(myQueue, 37) != myQueue.end();
		std::cout << (found37 ? "Was" : "Was not") << " able to find "
			<< 37 << " in the range" << std::endl << std::endl;

		auto itAlmostEnd = myQueue.end() - 3;
		auto sub = std::ranges::subrange(myQueue.begin(), itAlmostEnd);
		std::cout << "Partial range: ";
		std::ranges::for_each(sub, PrintFn);
		std::cout << std::endl;

		bool found88 = std::ranges::find(sub, 88) != itAlmostEnd;
		std::cout << (found88 ? "Was" : "Was not") << " able to find "
			<< 88 << " in the range" << std::endl;

		auto foundMultiple = std::ranges::find_if(myQueue, IsMultipleOfSeven);
		if (foundMultiple != myQueue.end()) {
			std::cout << "Found multiple of 7 in the range, "
				<< *foundMultiple << ", at index " << (foundMultiple - myQueue.begin())
				<< std::endl;
		}
		else {
			std::cout << "Found multiple of 7 was not found in the range" << std::endl;
		}

		auto foundMultipleInSubRange = std::ranges::find_if_not(sub, IsMultipleOfSeventeen);
		if (foundMultipleInSubRange != sub.end()) {
			std::cout << "Found something that was not a multiple of 17 in the range, "
				<< *foundMultipleInSubRange << ", at index "
				<< (foundMultipleInSubRange - myQueue.begin())
				<< std::endl;
		}
		else {
			std::cout << "The whole range is multiples of 17" << std::endl;
		}
	}
};

class Chapter12_5_2 {
public:
	static void LookAtFindFirstOf() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		struct Point { int x, y; };
		const std::vector<int> vector1 = { 2,3, 5,7, 1,8 };
		const std::vector<int> vector2 = { -2,3, 4, 5,7 };
		const std::vector<Point> points1 = { {2,3}, {5,7}, {1,8} };
		const std::vector<Point> points2 = { {1,3}, {4,4}, {5,7}, {8,1} };
		auto IsMatch = [](Point a, Point b) { return a.x == b.x && a.y == b.y; };

		auto PrintNumberFn = [](const auto& n) { std::cout << n << ", "; };
		auto PrintPointFn = [](const Point& p)
			{ std::cout << "(" << p.x << "," << p.y << "), "; };

		std::cout << "Values in vector1: ";
		std::ranges::for_each(vector1, PrintNumberFn);
		std::cout << std::endl;
		std::cout << "Values in vector2: ";
		std::ranges::for_each(vector2, PrintNumberFn);
		std::cout << std::endl;

		auto foundVector12 = std::ranges::find_first_of(vector1.begin(), vector1.end(),
			vector2.begin(), vector2.end());
		if (foundVector12 != vector1.end())
		{
			auto distance = std::distance(vector1.begin(), foundVector12);
			std::cout << "Found value from vector2 (" << *foundVector12
				<< ") in vector1 at index " << distance << std::endl;
		}
		else
		{
			std::cout << "Did not find value from vector2 in vector1" << std::endl;
		}

		std::cout << std::endl;
		std::cout << "Values in points1: ";
		std::ranges::for_each(points1, PrintPointFn);
		std::cout << std::endl;
		std::cout << "Values in points2: ";
		std::ranges::for_each(points2, PrintPointFn);
		std::cout << std::endl;

		auto foundPoint12 = std::ranges::find_first_of(points1, points2, IsMatch);
		if (foundVector12 != vector1.end())
		{
			auto distance = std::distance(points1.begin(), foundPoint12);
			std::cout << "Found point from points2 ("
				<< foundPoint12->x << "," << foundPoint12->y << ") "
				<< "in points1 at index " << distance << std::endl;
		}
		else
		{
			std::cout << "Did not find value from points2 in points1" << std::endl;
		}

		auto foundProj12 = std::ranges::find_first_of(points1, points2, {},
			&Point::x, &Point::y);
		if (foundProj12 != points1.end())
		{
			auto distance = std::distance(points1.begin(), foundProj12);
			std::cout << "Found y value from points2 in x values of points1 ("
				<< foundProj12->x << "," << foundProj12->y << ") "
				<< " at index " << distance
				<< std::endl;
		}
		else
		{
			std::cout << "Did not find value from points1 in points1" << std::endl;
		}
	}
};

class Chapter12_5_3 {
public:
	static void LookAtSearch() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<int> vector1{ 3, -1, -2, -3, 1, 2, 3, 4, 5, 1, 2, 3, 6 };
		const std::vector<int> term{ 1, 2, 3 };
		auto PrintFn = [](const auto& n) { std::cout << n << ", "; };
		auto IsAbsEqualFn = [](const int a, const int b) { return abs(a) == abs(b); };

		std::cout << "Values in vector1: ";
		std::ranges::for_each(vector1, PrintFn);
		std::cout << std::endl;
		std::cout << "Values in search term: ";
		std::ranges::for_each(term, PrintFn);
		std::cout << std::endl << std::endl;

		auto found1 = std::ranges::search(vector1, term);
		if (not found1.empty()) {
			const auto foundStart = std::distance(vector1.begin(), found1.begin());
			const auto foundEnd = std::distance(vector1.begin(), found1.end());
			std::cout << "Found search term in vector1, starting at index ["
				<< foundStart << "] (" << *(found1.begin()) << ") to index ["
				<< foundEnd - 1 << "] (" << *((found1.end()) - 1) << ")" << std::endl;
		}
		else
		{
			std::cout << "Could not find term in vector1" << std::endl;
		}

		auto found2 = std::ranges::search(vector1, term, IsAbsEqualFn);
		if (not found2.empty()) {
			const auto foundStart = std::distance(vector1.begin(), found2.begin());
			const auto foundEnd = std::distance(vector1.begin(), found2.end());
			std::cout << "Found search term (via predicate) in vector1, starting at index ["
				<< foundStart << "] (" << *(found2.begin()) << ") to index ["
				<< foundEnd - 1 << "] (" << *((found2.end()) - 1) << ")" << std::endl;
		}
		else
		{
			std::cout << "Could not find term (via predicate) in vector1" << std::endl;
		}
	}
};

class Chapter12_5_4 {
public:
	static void LookAtAdjacentFind() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<int> vector1 = { 2, 3, 5, -5, 7, 1, 8, 8 };
		auto PrintFn = [](const auto& n) { std::cout << n << ", "; };
		auto IsAbsEqualFn = [](const int a, const int b) { return abs(a) == abs(b); };

		std::cout << "Values in vector1: ";
		std::ranges::for_each(vector1, PrintFn);
		std::cout << std::endl;

		auto found1 = std::ranges::adjacent_find(vector1);
		if (found1 != vector1.end()) {
			auto distance = std::distance(vector1.begin(), found1);
			std::cout << "Found equal values in vector1 (" << *found1
				<< ") at index " << distance << std::endl;
		}
		else {
			std::cout << "Did not find equal adjecent values in vector1" << std::endl;
		}
		std::cout << std::endl;

		auto foundAbs = std::ranges::adjacent_find(vector1, IsAbsEqualFn);
		if (foundAbs != vector1.end()) {
			auto distance = std::distance(vector1.begin(), foundAbs);
			std::cout << "Found absolute-equal values in vector1 (" << *foundAbs
				<< ") at index " << distance << std::endl;
		}
		else {
			std::cout << "Did not find absolute-equal adjecent values in vector1" << std::endl;
		}
	}
};

class Chapter12_5_5 {
public:
	static void LookAtContains() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::deque<int> myQueue = { 17, -34, 37, 42, 67, 88 };
		auto IsAbsEqualFn = [](const int n) { return abs(n); };
		auto PrintFn = [](const auto& n) { std::cout << n << ", "; };
		std::deque<int> myQueue2 = { 34, -37, -42 };

		std::cout << "Full range: ";
		std::ranges::for_each(myQueue, PrintFn);
		std::cout << std::endl;

		bool found37 = std::ranges::contains(myQueue, 37);
		std::cout << (found37 ? "Was" : "Was not") << " able to find "
			<< 37 << " in the range" << std::endl << std::endl;

		auto itAlmostEnd = myQueue.end() - 3;
		auto sub = std::ranges::subrange(myQueue.begin(), itAlmostEnd);
		std::cout << "Partial range: ";
		std::ranges::for_each(sub, PrintFn);
		std::cout << std::endl;

		bool found88 = std::ranges::contains(sub, 88);
		std::cout << (found88 ? "Was" : "Was not") << " able to find "
			<< 88 << " in the range" << std::endl;

		std::cout << "Small range: ";
		std::ranges::for_each(myQueue2, PrintFn);
		std::cout << std::endl;
		bool foundsub = std::ranges::contains_subrange(myQueue, myQueue2, {}, IsAbsEqualFn, IsAbsEqualFn);
		std::cout << (foundsub ? "Was" : "Was not") << " able to find "
			<< " the small range in the main range (via the projections)" << std::endl;
	}
};

class Chapter12_5_6 {
public:
	static void LookAtStartsEndsWith() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::deque<int> myQueue = { 17, -34, 37, 42, 67, 88 };
		auto IsAbsEqualFn = [](const int n) { return abs(n); };
		auto IsAbsMatch = [](const int& a, const int& b) { return abs(a) == abs(b); };
		auto PrintFn = [](const auto& n) { std::cout << n << ", "; };
		const std::deque<int> myQueueStart = { -17, 34, -37 };
		const std::deque<int> myQueueEnd = { -42, -67, 88 };

		std::cout << "Full range: ";
		std::ranges::for_each(myQueue, PrintFn);
		std::cout << std::endl;

		std::cout << "Start search range: ";
		std::ranges::for_each(myQueueStart, PrintFn);
		std::cout << std::endl;

#ifdef _MSC_VER
		bool foundStart = std::ranges::starts_with(myQueue, myQueueStart);
		bool foundStartAbs = std::ranges::starts_with(myQueue, myQueueStart, {}, IsAbsEqualFn, IsAbsEqualFn);
		std::cout << (foundStart ? "Was" : "Was not") << " able to find the search range"
			" at the start of the main range" << std::endl;
		std::cout << (foundStartAbs ? "Was" : "Was not") << " able to find the search range"
			" at the start of the main range, using absolute comparison" << std::endl;
#endif

		std::cout << std::endl << "End search range: ";
		std::ranges::for_each(myQueueEnd, PrintFn);
		std::cout << std::endl;

#ifdef _MSC_VER
		bool foundEnd = std::ranges::ends_with(myQueue, myQueueEnd);
		bool foundEndAbs = std::ranges::ends_with(myQueue, myQueueEnd, IsAbsMatch);
		std::cout << (foundEnd ? "Was" : "Was not") << " able to find the search range"
			" at the end of the main range" << std::endl;
		std::cout << (foundEndAbs ? "Was" : "Was not") << " able to find the search range"
			" at the end of the main range, using absolute comparison" << std::endl;
#endif
	}
};

void LookAtChapter12Topics()
{
	// works with compiler?					when tested	  clang	msvc	gcc
	Chapter12_1_1::LookAtBasics();			// 2023.11.27	yes	yes		yes
	Chapter12_1_2::LookAtBasicsInReverse(); //2023.11.27	yes	yes		yes
	Chapter12_1_3::LookAtData();			// 2023.11.27	yes	yes		yes
	Chapter12_2_1::DoForEach();				// 2023.11.27	yes	yes		yes
	Chapter12_2_2::DoForEachN();			// 2023.11.27	no	yes		no
	Chapter12_3_1::DoCounts();				// 2023.11.27	yes	yes		yes
	Chapter12_3_2::DoAnyAllNone();			// 2023.11.27	yes	yes		yes
	Chapter12_4_1::LookForMismatch();		// 2023.11.27	yes	yes		yes
	Chapter12_4_2::LookAtEqual();			// 2023.11.27	yes	yes		yes
	Chapter12_4_3::LookAtLexographicalCompare();// 2023.11.27 y	yes		yes
	Chapter12_5_1::LookAtFind();			// 2023.11.27	yes	yes		yes
	Chapter12_5_2::LookAtFindFirstOf();		// 2023.11.27	yes	yes		yes
	Chapter12_5_3::LookAtSearch();			// 2023.11.27	yes	yes		yes
	Chapter12_5_4::LookAtAdjacentFind();	// 2023.11.27	yes	yes		yes
	Chapter12_5_5::LookAtContains();		// 2023.11.27	yes	yes		yes
	Chapter12_5_6::LookAtStartsEndsWith();	// 2023.11.27	no	yes		no
}
