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

class Chapter15_2 {
public:
	static void PrintAllAndEmpty(std::string title, std::ranges::view auto view) {
		std::cout << title << std::endl;
		std::cout << "Distance= " << std::distance(view.begin(), view.end())
			<< ", size=" << view.size() << std::endl;
		std::cout << "View is " << (view.empty() ? "empty" : "not empty") << std::endl;
		std::cout << std::endl;
	}

	static void LookAtAllAndEmptyAndSingle() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<int> severalNumbers{ 4, 37, 99, 17, 67, 42 };
		const auto allResult = std::views::all(severalNumbers);
		PrintAllAndEmpty("views::all", allResult);

		const std::ranges::empty_view<std::string> emptyResult;
		PrintAllAndEmpty("ranges::empty_view", emptyResult);

		const std::ranges::single_view<long> singleResult{ 42 };
		PrintAllAndEmpty("ranges::single_view", singleResult);
	}
};

class Chapter15 {
public:
	static void PrintView(std::string title, auto view) {
		auto PrintNumbers = [](auto n) { std::cout << n << ", "; };

		std::cout << title << ": ";
		for (auto i : view) {
			PrintNumbers(i);
		}
		std::cout << std::endl;
	}
};

class Chapter19_3 {
public:
	static void LookAtTakeAndDrop() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		auto IsEven = [](auto n) { return n % 2 == 0; };

		const std::vector<int> severalNumbers{ 4, 42, 2, 22, 99, 37, 17, 67, 14, 27, 33, 7, 6, 65, 25 };
		Chapter15::PrintView("all", severalNumbers);

		const auto someAtStart = std::ranges::views::take(severalNumbers, 5);
		Chapter15::PrintView("take 5", someAtStart);

		const auto someEvenAtStart = std::ranges::views::take_while(severalNumbers, IsEven);
		Chapter15::PrintView("take_while even", someEvenAtStart);

		const auto someAfterStart = std::ranges::views::drop(severalNumbers, 7);
		Chapter15::PrintView("drop 7", someAfterStart);

		const auto someOddAfterStart = std::ranges::views::drop_while(severalNumbers, IsEven);
		Chapter15::PrintView("drop_while even", someOddAfterStart);

		const auto dropSomeAndTakeSome = std::ranges::views::take(std::ranges::views::drop(severalNumbers, 7), 3);
		Chapter15::PrintView("drop 7 and take 3", dropSomeAndTakeSome);

		const auto it99 = std::ranges::find(severalNumbers, 99);
		const auto someAfter99 = std::views::counted(it99, 4);
		Chapter15::PrintView("4 after 99", someAfter99);
		const auto someAfter99_2 = std::views::counted(severalNumbers.begin() + 4, 4);
		Chapter15::PrintView("4 after 99 (again)", someAfter99_2);
		std::cout << std::endl;
	}
};

class Chapter15_4 {
public:
	static void LookAtTakeAndDropWithComposition() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		auto IsEven = [](auto n) { return n % 2 == 0; };

		const std::vector<int> severalNumbers{ 4, 42, 2, 22, 99, 37, 17, 67, 14, 27, 33, 7, 6, 65, 25 };
		Chapter15::PrintView("all", severalNumbers);

		const auto someAtStart = severalNumbers | std::ranges::views::take(5);
		Chapter15::PrintView("take 5", someAtStart);

		const auto someEvenAtStart = severalNumbers | std::views::take_while(IsEven);
		Chapter15::PrintView("take_while even", someEvenAtStart);

		const auto someAfterStart = severalNumbers | std::ranges::views::drop(7);
		Chapter15::PrintView("drop 7", someAfterStart);

		const auto someOddAfterStart = severalNumbers | std::ranges::views::drop_while(IsEven);
		Chapter15::PrintView("drop_while even", someOddAfterStart);

		const auto dropSomeAndTakeSome = severalNumbers | std::ranges::views::drop(7) | std::ranges::views::take(3);
		Chapter15::PrintView("drop 7 and take 3", dropSomeAndTakeSome);

		const auto someAfter99 = severalNumbers | std::ranges::views::drop_while([](auto n) { return n != 99; })
			| std::ranges::views::take(4);
		Chapter15::PrintView("4 after 99", someAfter99);
	}
};

class Chapter15_5 {
public:
	static void LookAtFilterAndTransform() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		auto IsOdd = [](auto n) { return n % 2 == 1; };
		auto Doubler = [](auto n) { return n * 2; };

		const std::vector<int> severalNumbers{ 4, 42, 2, 22, 99, 37, 17, 67, 14, 27, 33, 7, 6, 65, 25 };
		Chapter15::PrintView("original numbers", severalNumbers);

		auto justOdd = severalNumbers | std::views::filter(IsOdd);
		Chapter15::PrintView("odds", justOdd);
		const auto doubleOdds = severalNumbers | std::views::filter(IsOdd) | std::views::transform(Doubler);
		Chapter15::PrintView("the odds are doubled ", doubleOdds);
		auto justOddsDoubled = justOdd | std::views::transform(Doubler);
		Chapter15::PrintView("previous odds doubled", justOddsDoubled);

		const std::string message = "C++23 is great!";
		auto CheckInput = [](auto c) -> std::string {
			if (isalpha(c)) return "letter '" + std::string(1, c) + '\'';
			else if (isdigit(c)) return "number '" + std::string(1, c) + '\'';
			else return "symbol '" + std::string(1, c) + '\'';
			};
		const auto inspectmessageOutput = message | std::views::transform(CheckInput);
		for (auto s : inspectmessageOutput) {
			std::cout << s << std::endl;
		}
	}
};

class Chapter15_6 {
public:
	static void LookAtJoinAndSplit() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::deque<std::vector<int>> bunchesOfNumbers{ {4, 42, 2}, {22, 99, 37}, {17}, {67, 14, 27, 33, 7}, {6, 65, 25} };
		for (auto i = 0; i < bunchesOfNumbers.size(); i++) {
			Chapter15::PrintView("bunch " + std::to_string(i + 1) + ", size=" + std::to_string(bunchesOfNumbers[i].size()), bunchesOfNumbers[i]);
		}
		const auto joinedNumbers = std::ranges::join_view(bunchesOfNumbers);
		auto d = std::ranges::distance(joinedNumbers);
		Chapter15::PrintView("after join, size=" + std::to_string(d) + ": ", joinedNumbers);
		std::cout << std::endl;

		std::deque<std::string> words = { "I", "like", "C++23" };
		std::cout << "Words, size=" + std::to_string(words.size()) + ": ";
		for (auto w : words) std::cout << w << ".";
		std::cout << std::endl;
		const auto joinedCharacters = std::ranges::join_with_view(words, ".");
		d = std::ranges::distance(joinedCharacters);
		std::cout << "joined characters, size=" + std::to_string(d) + ": ";
		for (auto s : joinedCharacters) std::cout << s;
		std::cout << std::endl << std::endl;

		const std::string sentence = { "I like C++23" };
		std::cout << "sentence, size=" + std::to_string(sentence.size()) + ": " + sentence << std::endl;
		const std::string splitter = " ";
		// NOTE: (at least for MS VS compiler) splitter must be a separate variable, otherwise will not split
		auto splitWords = std::views::split(sentence, splitter);
		std::cout << "split words: " << std::endl;
		for (auto wi : splitWords) {
			std::cout << std::quoted(std::string_view(wi.begin(), wi.end())) << std::endl;
		}
		std::cout << std::endl;

		const std::vector<int> manyNumbers{ 4, 42, 2, 99, 22, 99, 37, 17, 67, 14, 99, 27, 33, 7, 6, 99, 65, 25 };
		Chapter15::PrintView("many delimited numbers", manyNumbers);
		const auto splitterNumber = 99;
		const auto splitNumbers = std::ranges::views::lazy_split(manyNumbers, splitterNumber);
		d = std::ranges::distance(splitNumbers);
		auto splitCounter = 0;
		for (auto g : splitNumbers) {
			Chapter15::PrintView("bunch " + std::to_string(splitCounter + 1) + ", size=" +
				std::to_string(std::ranges::distance(g)), g);
			splitCounter++;
		}
	}
};

class Chapter15_7 {
public:
	static void LookAtKeysAndValues() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::map<int, std::string> collection{ {1,"Welcome"}, {2, "to"}, {3,"C++23"} };

		const auto keys = std::views::keys(collection);
		Chapter15::PrintView("keys:", keys);

		const auto values = std::views::values(collection);
		Chapter15::PrintView("keys:", values);
		std::cout << std::endl;

		const std::vector<std::tuple<int, float, std::string>> microwavableFood{ {330, 450.0, "butter chicken"}, { 170, 490.0, "popcorn"}, {120, 430.0, "rice"} };
		Chapter15::PrintView("cookingSeconds:", std::views::elements<0>(microwavableFood));
		Chapter15::PrintView("calories:", std::views::elements<1>(microwavableFood));
		Chapter15::PrintView("food:", std::views::elements<2>(microwavableFood));
		std::cout << std::endl;

		const std::vector<std::tuple<int, float>> microwavableFood2{ {330, 450.0}, { 170, 490.0}, {120, 430.0} };
		Chapter15::PrintView("keys2:", std::views::keys(microwavableFood2));
		Chapter15::PrintView("values2:", std::views::values(microwavableFood2));
		std::cout << std::endl;

		const std::vector<std::pair<int, float>> microwavableFood3{ {330, 450.0}, { 170, 490.0}, {120, 430.0} };
		Chapter15::PrintView("keys3:", std::views::keys(microwavableFood3));
		Chapter15::PrintView("values3:", std::views::values(microwavableFood3));
		std::cout << std::endl;

		Chapter15::PrintView("keys4:", std::views::keys(microwavableFood));
		Chapter15::PrintView("values4:", std::views::values(microwavableFood));
	}
};

#pragma region Chapter15_Section8
auto PrintSubrange = [](std::ranges::viewable_range auto&& r) {
	std::cout << "{";
	for (auto i = 0; i < std::ranges::distance(r); i++) {
		if (i > 0) std::cout << " ";
		std::cout << r[i];
	}
	std::cout << "}, ";
	};

class Chapter15_8 {
public:
	static void LookAtSlideAndChunk() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<int> manyNumbers{ 4, 42, 2, 99, 37, 17, 67, 14, 27, 33, 65 };
		Chapter15::PrintView("original numbers", manyNumbers);
		std::cout << std::endl;

		for (auto width = 1; width <= 5; width++) {
			const auto windows = manyNumbers | std::views::slide(width);
			std::cout << "Windows of width " << width << ": ";
			std::ranges::for_each(windows, PrintSubrange);
			std::cout << std::endl;
		}
		std::cout << std::endl;

		for (auto width = 1; width <= 5; width++) {
			const auto chunks = manyNumbers | std::views::chunk(width);
			std::cout << "Chunks of width " << width << ": ";
			std::ranges::for_each(chunks, PrintSubrange);
			std::cout << std::endl;
		}
		std::cout << std::endl;

		auto chunkBys = manyNumbers | std::views::chunk_by(std::ranges::less{});
		std::cout << "Chunks of using < : ";
		std::ranges::for_each(chunkBys, PrintSubrange);
		std::cout << std::endl << std::endl;

		const std::string sentence = { "I like C++23" };
		auto fn = [](char x, char y) { return not(x == ' ' or y == ' '); };
		auto chunkByWords = sentence | std::views::chunk_by(fn);
		std::cout << "Chunks of words: ";
		std::ranges::for_each(chunkByWords, PrintSubrange);
		std::cout << std::endl << std::endl;

		Chapter15::PrintView("original numbers", manyNumbers);
		const auto strideView = manyNumbers | std::views::stride(3);
		Chapter15::PrintView("stride of 3 ", strideView);
		std::cout << std::endl;
	}
	
	static void LookAtAdjacent() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<int> manyNumbers{ 4, 42, 2, 99, 37, 17, 67, 14, 27, 33, 65 };
		Chapter15::PrintView("original numbers for adjacent", manyNumbers);
		constexpr std::size_t adjacentWindowSize{ 8 };
		std::cout << "adjacent groups, using window size= " << adjacentWindowSize << " : " << std::endl;
#ifdef __cpp_lib_ranges_zip
		const auto adjacentResult = manyNumbers | std::views::adjacent<adjacentWindowSize>;
		for (auto ar : adjacentResult) {
			std::cout << "{" << std::get<0>(ar) << ", " << std::get<1>(ar) << ", "
				<< std::get<2>(ar) << ", " << std::get<3>(ar) << ", "
				<< std::get<4>(ar) << ", " << std::get<5>(ar) << ", "
				<< std::get<6>(ar) << ", " << std::get<7>(ar) << "}" << std::endl;
		}
#endif
		std::cout << std::endl;

		const std::vector<int> someNumbers{ 5, 40, 300, 2000, 10000 };
		Chapter15::PrintView("original numbers for adjacent_transform", someNumbers);
		constexpr std::size_t adjacentTransformWindowSize{ 4 };
		std::cout << "adjacent_transform groups, using window size= " << adjacentTransformWindowSize << " : " << std::endl;
		auto AdjacentTransformFn = [](auto... ints) { return (... + ints); };
#ifdef __cpp_lib_ranges_zip
		const auto adjacentTransformView = std::views::adjacent_transform<adjacentTransformWindowSize>(AdjacentTransformFn);
#else
		std::cout << "feature is currently not working" << std::endl;
#endif
		const auto adjacentResult2 = someNumbers | adjacentTransformView;
		for (auto viewValue : adjacentResult2) {
			std::cout << viewValue << ", ";
		}
		std::cout << std::endl << std::endl;
	}
};
#pragma endregion Chapter15_Section8

class Chapter15_9 {
public:
	static void LookAtZip() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		std::vector<std::string> breakfasts{ "bacon and eggs", "waffles", "cereal", "porridge" };
		std::deque<std::string> lunches{ "chicken salad", "club sandwich", "carrot soup" };
		std::array<std::string, 5> dinners{ "spaghetti", "tacos", "chicken fried rice", "lasagna", "salmon" };

		Chapter15::PrintView("breakfasts: ", breakfasts);
		Chapter15::PrintView("lunches: ", lunches);
		Chapter15::PrintView("dinners: ", dinners);
		std::cout << std::endl;

#ifdef __cpp_lib_ranges_zip
		const auto mealResults = std::views::zip(breakfasts, lunches, dinners);
		std::cout << "Resulting meals" << std::endl;
		for (std::tuple<std::string&, std::string&, std::string&> elem : mealResults) {
			std::cout << std::get<0>(elem) << ", "
				<< std::get<1>(elem) << ", "
				<< std::get<2>(elem) << std::endl;
		}

		auto CombineMeal = [](auto b, auto l, auto d) { return b + ", " + l + ", " + d; };
		const auto combos = std::views::zip_transform(CombineMeal, breakfasts, lunches, dinners);
		Chapter15::PrintView("meals: ", combos);
#else
		std::cout << "feature is currently not working" << std::endl;
#endif
	}
};

class Chapter15_10 {
public:
	static void LookAtReverse() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<std::string> meals{ "breakfast", "lunch", "dinner" };
		Chapter15::PrintView("meals: ", meals);

		const auto backwardMeals = meals | std::views::reverse;
		Chapter15::PrintView("backward Meals: ", backwardMeals);

		const std::ranges::reverse_view moreBackwardMeals{ meals };
		Chapter15::PrintView("more backward Meals: ", moreBackwardMeals);
	}
};

class Chapter15_11 {
public:
	static void LookAtSpecialAdaptors() {
		std::cout << std::endl << "Examples in: " << __FUNCTION__ << std::endl;
		const std::vector<std::string> message{ "C++23", "is", "great", "!", "Is", "it", "not", "?" };
		Chapter15::PrintView("message", message);
		std::cout << "Address of message=" << &message[0] << ", size=" << std::ranges::size(message) << std::endl;
		const std::ranges::ref_view refAll{ message };
		std::cout << "type of ref_view is: " << typeid(refAll).name() << std::endl;
		std::cout << "Address of refAll=" << &refAll[0] << ", size=" << std::ranges::size(refAll) << std::endl;
		const auto allOfMessage = std::views::all(message);
		std::cout << "Address of All=" << &allOfMessage[0] << ", size=" << std::ranges::size(allOfMessage) << std::endl;
		std::cout << "type of all result is: " << typeid(allOfMessage).name() << std::endl;
		const auto few = message | std::views::take(3);
		Chapter15::PrintView("few", few);
		std::cout << "Address of take result=" << &few[0] << ", size=" << std::ranges::size(few) << std::endl;
		const std::ranges::ref_view refFew{ few };
		std::cout << "Address of ref of take result=" << &refFew[0] << ", size=" << std::ranges::size(refFew) << std::endl;
		Chapter15::PrintView("ref of few", refFew);

		const std::ranges::owning_view owner{ std::vector<std::string> { "C++23", "is", "great" } };
		Chapter15::PrintView("owner of the message", std::ranges::subrange(owner));

		const std::deque<int> numbers{ 1,2,3,4,5 };
		Chapter15::PrintView("all", numbers);
		const auto someOffset = std::counted_iterator{ numbers.begin(), std::ssize(numbers) };
		const auto someNumbers = std::ranges::subrange(someOffset + 2, std::default_sentinel);
		Chapter15::PrintView("some", someNumbers);
		//auto cannotAdd = std::accumulate(someNumbers.begin(), std::default_sentinel, 0);
		const auto commonViewOfSomeNumbers = std::ranges::common_view{ someNumbers };
		const auto canAdd = std::accumulate(commonViewOfSomeNumbers.begin(), commonViewOfSomeNumbers.end(), 0);
		std::cout << "Sum=" << canAdd << std::endl;

#ifdef __cpp_lib_ranges_as_const
		const auto constRangeofSomeNumbers = std::ranges::as_const_view{ someNumbers };
		std::cout << "type of as_const result is: " << typeid(constRangeofSomeNumbers).name() << std::endl;
#else
		std::cout << "feature is currently not working" << std::endl;
#endif

#ifdef __cpp_lib_ranges_as_rvalue
		const auto rValueRangeofSomeNumbers = std::ranges::as_rvalue_view{ someNumbers };
		std::cout << "type of as_rvalue result is: " << typeid(rValueRangeofSomeNumbers).name() << std::endl;
#endif
	}
};

void LookAtChapter15Topics()
{
	// works with compiler?							when tested	  clang	msvc	gcc
	Chapter15_2::LookAtAllAndEmptyAndSingle();	//    2023.11.30	yes	yes		yes
	Chapter19_3::LookAtTakeAndDrop();			//    2023.11.30	yes	yes		yes
	Chapter15_4::LookAtTakeAndDropWithComposition();//2023.11.30	yes	yes		yes
	Chapter15_5::LookAtFilterAndTransform();	//    2023.11.30	yes	yes		yes
	Chapter15_6::LookAtJoinAndSplit();			//    2023.11.30	yes	yes		yes
	Chapter15_7::LookAtKeysAndValues();			//    2023.11.30	yes	yes		yes
	Chapter15_8::LookAtSlideAndChunk();			//    2023.11.30	yes	yes		yes
	Chapter15_8::LookAtAdjacent();				//    2023.11.30	yes	yes		yes
	Chapter15_9::LookAtZip();					//    2023.11.30	yes	yes		mostly
	Chapter15_10::LookAtReverse();				//    2023.11.30	yes	yes		yes
	Chapter15_11::LookAtSpecialAdaptors();		//    2023.11.30	yes	yes		yes
}
