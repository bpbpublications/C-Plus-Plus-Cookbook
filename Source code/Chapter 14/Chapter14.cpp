#include <iostream>
#include <ranges>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <functional>
#include <numeric>
#include <cmath>
#include <array>
#include <iomanip>
#include <sstream>
#include <memory>
#include <string>
#include <random>
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <stack>
#include <cctype>

static void PrintRange(std::string title, std::ranges::range auto r, std::string sep, bool printQuotes) {
	if (not title.empty()) {
		std::cout << title << " ";
	}
	else {
		std::cout << "Full range : ";
	}
	if (sep == "\n") {
		std::cout << sep;
	}

	auto rCount = std::ranges::size(r);
	for (auto i=0; i< rCount; i++) {
		if (printQuotes) std::cout << "'";
		std::cout << r[i];
		if (printQuotes) std::cout << "'";
		if (i != rCount-1) std::cout << sep;
	}
	std::cout << std::endl;
}
static void PrintRange(std::ranges::range auto r, std::string title = "") {
	using R = decltype(r);
	using Elem = std::ranges::range_value_t<R>;
	static std::string sep{ ", " };
	if (std::is_convertible_v<Elem, int>) {
		sep = ", ";
	}
	else {
		sep = " ";
	}

	PrintRange(title, r, sep, false);
}

#pragma region Chapter14_Section1
static void LookAtHeap() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::deque<int> myQueue = { 18, 50, 99, 17, 67, 42 };
	//std::ranges::sort(myQueue);
	PrintRange(myQueue, "Original range");
	auto isHeapResult = std::ranges::is_heap(myQueue);
	std::cout << "range" << (isHeapResult ? " is " : " is not ") << "a max heap" << std::endl;
	std::cout << std::endl;

	std::ranges::make_heap(myQueue);
	PrintRange(myQueue, "Max-heap range");
	isHeapResult = std::ranges::is_heap(myQueue);
	std::cout << "range" << (isHeapResult ? " is currently " : " is still not ") << "a max heap" << std::endl;
	std::cout << std::endl;

	std::ranges::make_heap(myQueue, std::greater());
	PrintRange(myQueue, "Min-heap range");
	isHeapResult = std::ranges::is_heap(myQueue, std::greater());
	std::cout << "range" << (isHeapResult ? " is currently " : " is still not ") << "a min heap" << std::endl;
	std::cout << std::endl;

	// go back to max-heap
	std::ranges::make_heap(myQueue);
	myQueue.emplace_back(77);
	PrintRange(myQueue, "Max-heap range, with extra value appended");
	std::cout << "range" << (std::ranges::is_heap(myQueue) ?
		" is currently " : " is not ") << "a max heap" << std::endl;
	std::ranges::push_heap(myQueue);
	PrintRange(myQueue, "Max-heap range, after push_heap()");
	std::cout << "range" << (std::ranges::is_heap(myQueue) ?
		" is currently " : " is still not ") << "a max heap" << std::endl;
	std::cout << std::endl;
	for (auto i = std::ssize(myQueue); i >= 0; --i) {
		std::ranges::pop_heap(myQueue.begin(), myQueue.begin()+i);
		PrintRange(myQueue, "After pop# " + std::to_string(i) + ": ");
	}
	std::cout << std::endl;

	std::ranges::make_heap(myQueue);
	PrintRange(myQueue, "Make into Max-heap range, one last time");
	std::ranges::sort_heap(myQueue);
	PrintRange(myQueue, "After sort_heap");
}
#pragma endregion Chapter14_Section1

#pragma region Chapter14_Section2
// no code recipes provided
#pragma endregion Chapter14_Section2

#pragma region Chapter14_Section3
static void LookAtModifying_Copy() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::deque<int> myNumberQueue = { 99, 17, 37, 75, 34, 67, 42, 99 };
	std::vector<int> myNumberVector;

	PrintRange(myNumberQueue, "Source");
	PrintRange(myNumberVector, "Target before copy: ");
	std::ranges::copy(myNumberQueue, std::back_inserter(myNumberVector));
	PrintRange(myNumberVector, "Target after copy : ");
	std::cout << std::endl;

	myNumberVector.clear();
	auto IsMultipleOfThree = [](int n) { return n % 3 == 0; };
	std::ranges::copy_if(myNumberQueue, std::back_inserter(myNumberVector), IsMultipleOfThree);
	PrintRange(myNumberVector, "Target after copy of multiples of 3 : ");
	std::cout << std::endl;

	const std::deque<std::string> myWordQueue = { "the", "C++23", "release", "has", "a", "lot", "of", "range", "functionality" };
	std::string introWords[3]{ "Don't", "you", "agree" };
	PrintRange(myWordQueue, "Original sentence");
	std::vector<std::string> myStringVector(myWordQueue.size() - 1 + introWords->length() -1);
	std::ranges::copy_backward(myWordQueue, myStringVector.end());
	std::ranges::copy_n(introWords, 3, myStringVector.begin());
	PrintRange(myStringVector, "Copied (backwards) sentence");
}
#pragma endregion Chapter14_Section3

#pragma region Chapter14_Section4
static void LookAtModifying_Move() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::deque<std::string> yesterdaysMenuChoices = { "roasted potato", "broccoli", "spicy chicken" };
	std::vector<std::string> todaysSoupChoices;

	PrintRange("Yesterday's dishes (before) :", yesterdaysMenuChoices, "\n", true);
	PrintRange("Today's soup choices (before) :", todaysSoupChoices, ", ", true);
	std::cout << std::endl;
	std::ranges::move(yesterdaysMenuChoices, std::back_inserter(todaysSoupChoices));
	PrintRange("Yesterday's dishes (after) :", yesterdaysMenuChoices, ", ", true);
	PrintRange("Today's soup choices (after) :", todaysSoupChoices, "\n", true);
	std::cout << std::endl;

	std::vector<std::string> todaysSpecialSoupChoices(todaysSoupChoices.size()+1);
	std::vector<std::string> specialMenu{ "Whatever else people didn't eat" };
	std::ranges::move_backward(todaysSoupChoices.begin(), todaysSoupChoices.end(), todaysSpecialSoupChoices.end());
	std::ranges::move(specialMenu.begin(), specialMenu.end(), todaysSpecialSoupChoices.begin());
	PrintRange("Today's special soup choices :", todaysSpecialSoupChoices, "\n", true);
}

static void LookAtModifying_FillAndRemove() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::vector<char> message(15);
	const std::string source{ "C++23 is great" };

	std::ranges::fill(message, '!');
	PrintRange("Message :", message, " ", true);
	auto it = message.begin();
	for (auto i = 0; i < source.size(); i++, it++) {
		std::ranges::fill_n(it, 1, source[i]);
		PrintRange("Message :", message, " ", true);
	}
	std::cout << std::endl;

	auto removeResult = std::ranges::remove(message, '!');
	PrintRange("Message after remove:", std::ranges::subrange(message.begin(), removeResult.begin()), " ", true);
	message.erase(removeResult.begin(), removeResult.end());
	auto IsVowelOrSpace = [](char c) { return c == ' ' || c == 'a' || c == 'e'
		|| c == 'i' || c == 'o' || c == 'u'; };
	removeResult = std::ranges::remove_if(message, IsVowelOrSpace);
	PrintRange("Message after remove_if:", std::ranges::subrange(message.begin(), removeResult.begin()), " ", true);
	std::cout << std::endl;

	message.clear();
	std::ranges::copy(source, std::back_inserter(message));
	std::vector<char> target;
	std::ranges::remove_copy_if(message, std::back_inserter(target), IsVowelOrSpace);
	PrintRange("Message after remove_copy_if:", message, " ", true);
	PrintRange("Destination after remove_copy_if:", target, " ", true);
}

static void LookAtShiftAndRotate() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_lib_shift
	std::vector<char> message;
	std::ranges::copy("C++23 is great!", std::back_inserter(message));
	PrintRange("Original message:", message, " ", false);

	std::ranges::shift_left(message, 1);
	PrintRange("message after shift left:", message, " ", false);
	std::ranges::shift_right(message, 1);
	PrintRange("message after shift right:", message, " ", false);
	std::ranges::shift_left(message, 3);
	PrintRange("message after shift left 3:", message, " ", false);
	std::ranges::shift_right(message, 3);
	PrintRange("message after shift right 3:", message, " ", false);
	std::cout << std::endl;

	std::deque<int> myNumberQueue = { 99, 17, 37, 75, 34, 67, 42, 99 };
	PrintRange(myNumberQueue, "Original range:");
	std::ranges::shift_left(myNumberQueue, 4);
	PrintRange(myNumberQueue, "After shift_left 4:");
	std::ranges::shift_right(myNumberQueue, 4);
	PrintRange(myNumberQueue, "After shift_right 4:");
	std::cout << std::endl;

	std::vector<std::string> words = { "C++", "23", "is", "a", "fantastic", "release", "!" };
	PrintRange(words, "Original words:");
	std::ranges::shift_left(words, 3);
	PrintRange("After shift_left 3:", words, " ", true);
	std::ranges::shift_right(words, 3);
	PrintRange("After shift_right 3:", words, " ", true);
	std::cout << std::endl;

	std::vector<std::string> textMessage{ "C++", "23", "is", "great!" };
	PrintRange("Original text message:", textMessage, " ", true);
	std::ranges::rotate(textMessage, textMessage.begin()+1);
	PrintRange("text message rotated +1:", textMessage, " ", true);
	std::ranges::rotate(textMessage, textMessage.end() - 3);
	PrintRange("text message rotated -3:", textMessage, " ", true);
	std::ranges::rotate(textMessage, textMessage.begin() + 2);
	PrintRange("text message rotated +2:", textMessage, " ", true);
	std::cout << std::endl;

	std::deque<std::string> target;
	std::ranges::rotate_copy(textMessage, textMessage.begin() + 1, std::back_inserter(target));
	PrintRange("rotated_copy result:", target, " ", true);
#endif
}

static void LookAtReplaceAndSwap() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::deque<int> myNumberQueue = { 99, 17, 37, 75, 34, 67, 42, 99 };
	PrintRange(myNumberQueue, "Original numbers:");
	std::ranges::replace(myNumberQueue, 99, 66);
	PrintRange(myNumberQueue, "Numbers after replace:");

	auto IsEven= [](int n) { return n % 2 == 0; };
	std::ranges::replace_if(myNumberQueue, IsEven, 1);
	PrintRange(myNumberQueue, "Numbers after replace_if:");
	std::cout << std::endl;

	myNumberQueue = { 99, 17, 37, 75, 34, 67, 42, 99 };
	std::deque<std::string> target(myNumberQueue.size());
	std::ranges::replace_copy(myNumberQueue, target.begin(), 99, 66);
	PrintRange(target, "Destination after replace_copy:");
	target.clear();
	target.resize(myNumberQueue.size());
	std::ranges::replace_copy_if(myNumberQueue, target.begin(), IsEven, 1);
	PrintRange(target, "Destination after replace_copy_if:");
	std::cout << std::endl;

	std::deque<std::string> message{ "C++", "23", "is", "a", "great", "& exciting", "release!" };
	std::vector<std::string> menuIdea{ "to make your", "linquine", "very", "tasty", "add", "a", "creamy", "sauce" };
	PrintRange("original message:", message, " ", true);
	PrintRange("original menu idea:", menuIdea, " ", true);
	std::ranges::swap_ranges(std::ranges::subrange(message.begin() + 4, message.begin() + 5+1), 
		std::ranges::subrange(menuIdea.begin() + 2, menuIdea.begin() + 3+1));
	PrintRange("message after swap:", message, " ", true);
	PrintRange("menu idea after swap:", menuIdea, " ", true);
	std::cout << std::endl;
}

static void LookAtReverseShuffleSampleUnique() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::deque<std::string> utensils{ "butter knife", "oyster fork", "salad fork",
		"soup spoon","knife and fork", "dessert fork" };
	PrintRange("original order:", utensils, ", ", false);
	std::ranges::reverse(utensils);
	PrintRange("after reverse:", utensils, ", ", false);
	std::vector<std::string> target;
	std::ranges::reverse_copy(utensils, std::back_inserter(target));
	PrintRange("target, after re-reverse:", target, ", ", false);
	std::cout << std::endl;

	std::array courses{ "hors d'oeuvre", "soup", "appetizer", "salad", "main course", "palate cleanser", "dessert","mignardise"};
	PrintRange("order of 8 course meal:", courses, ", ", false);
	std::random_device rd;
	std::mt19937 ranGen{ rd() };
	for (auto i = 0; i < 5; i++) {
		std::ranges::shuffle(courses, ranGen);
		PrintRange("course after shuffle#" + std::to_string(i+1) + ":", courses, ", ", false);
	}
	std::cout << std::endl;

	courses = { "hors d'oeuvre", "soup", "appetizer", "salad", "main course", "palate cleanser", "dessert","mignardise" };
	target.clear();
	for (auto i = 1; i <= 5; i++) {
		target.clear();
		std::ranges::sample(courses, std::back_inserter(target), i, ranGen);
		PrintRange("course after sample#" + std::to_string(i) + ":", target, ", ", false);
	}
	std::cout << std::endl;

	std::vector<std::string> manyUtensils{ "knife", "fork", "fork", "spoon", "knife", "spoon", "knife", "fork", "spoon" };
	PrintRange("duplicated utensils  : ", manyUtensils, ", ", false);
	std::ranges::sort(manyUtensils);
	std::deque<std::string> moreUtensils;
	std::ranges::copy(manyUtensils, std::back_inserter(moreUtensils)); // to use later
#pragma warning(push)
#pragma warning(suppress : 26478) 	// NOTE: seems like false warning; https://stackoverflow.com/questions/77051369/msvc-gives-warning-c26478-using-stdmove-on-constant-variables
	const auto [dupFirst, dupLast] = std::ranges::unique(manyUtensils);
#pragma warning(pop)
	manyUtensils.erase(dupFirst, dupLast);
	PrintRange("de-duplicated utensils:", manyUtensils, ", ", false);
	target.clear();
	std::ranges::unique_copy(moreUtensils, std::back_inserter(target));
	PrintRange("utensils after unique_copy:", target, ", ", false);
}

class NumberDoublingGenerator {
public:
	int operator()() { value *= 2; return value; }
private:
	int value{ 1 };
};

static void LookAtTransformAndGenerate() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::string term1("hello c++23!");

	PrintRange("term before:", term1, ", ", true);
	std::ranges::transform(term1.begin(), term1.end(), term1.begin(),
		[](unsigned char c) -> unsigned char { return std::toupper(c); });
	PrintRange("term after :", term1, ", ", true);
	std::cout << std::endl;

	auto TextPadder = [](const char c) -> std::string { return " " + std::string(1,c) + " "; };
	std::vector<std::string> term2;
	std::ranges::transform(term1, std::back_inserter(term2), TextPadder);
	PrintRange("term2 :", term2, ", ", true);
	std::cout << std::endl;

	std::vector<std::string> keys{ "a", "b", "c", "d", "e", "f", "g", "h", "i" };
	std::vector<std::string> values{ "z", "y", "x", "w", "v", "u", "t", "s", "r" };
	std::map<std::string, std::string> dictionary;
	auto MakePair = [](const std::string k, const std::string v) 
		-> std::pair<std::string,std::string>{ return std::make_pair(k,v); };
	std::ranges::transform(keys, values, std::inserter(dictionary, dictionary.end()), MakePair);
	std::cout << "Created map:" << std::endl;
	for (auto kvp : dictionary) {
		std::cout << "Key=" << kvp.first << ", " << kvp.second << std::endl;
	}
	std::cout << std::endl;

	std::vector<int> numbers(10);
	for (int i = 0; i < numbers.size(); i++) {
		std::ranges::generate(numbers, NumberDoublingGenerator());
	}
	PrintRange(numbers, "Generated range:");
}
#pragma endregion Chapter14_Section4

void LookAtChapter14Topics()
{
	// Does it work with your compiler?			when tested			clang			gcc			msvc
	LookAtHeap();							//	2023.10.22			yes				yes			yes
	LookAtModifying_Copy();					//  2023.10.22			yes				yes			yes
	LookAtModifying_Move();					//	2023.10.22			yes				yes			yes
	LookAtModifying_FillAndRemove();		//	2023.10.22			yes				yes			yes
	LookAtShiftAndRotate();					//	2023.10.22			no				no			yes
	LookAtReplaceAndSwap();					//	2023.10.22			yes				yes			yes
	LookAtReverseShuffleSampleUnique();		//	2023.10.22			yes				yes			yes
	LookAtTransformAndGenerate();			//	2023.10.22			yes				yes			yes
}
