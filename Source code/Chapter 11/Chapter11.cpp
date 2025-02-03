#include <vector>
#include <ranges>
#include <iostream>
#include <type_traits>
#include <array>
#include <algorithm>

#pragma region Chapter11_Section1
class Chapter11_1 {
public:
	static void FindInRange() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<int> numbers{ 1, 5, 17, 42, 55 };
		std::vector<int> numbersBad{ 1, 5, 17, 24, 55 };
		auto answerGood = std::find(numbers.begin(), numbers.end(), 42);
		std::cout << "Found good answer " << *answerGood << std::endl;
		auto answerBad = std::find(numbersBad.begin(), numbersBad.end(), 42);
		if (answerBad == numbersBad.end()) {
			std::cout << "Bad answer not found" << std::endl;
		}
		else {
			std::cout << *answerBad << std::endl;
		}

		auto answerGood2 = std::ranges::find(numbers, 42);
		std::cout << "Found good answer in range " << *answerGood2 << std::endl;
		auto answerBad2 = std::ranges::find(numbersBad, 42);
		if (answerBad2 == numbersBad.end()) {
			std::cout << "Bad answer not found in range" << std::endl;
		}
		else {
			std::cout << "Found bad answer in range" << *answerBad2 << std::endl;
		}
	}
};
#pragma endregion Chapter11_Section1

#pragma region Chapter11_Section2
class Chapter11_2_1 {
private:
	static void PrintString(std::string s) {
		std::cout << s << std::endl;
	}
	static void PrintStringView(std::string_view s) {
		std::cout << s << std::endl;
	}

public:
	static void StringViewExample() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::string s = "Hello C++23";
		PrintString(s);
		PrintStringView(s);
	}
};

template<class R>
concept __simple_view =                     // exposition only
std::ranges::view<R> && std::ranges::range<const R> &&
std::same_as<std::ranges::iterator_t<R>, std::ranges::iterator_t<const R>>&&
std::same_as<std::ranges::sentinel_t<R>, std::ranges::sentinel_t<const R>>;

class Chapter11_2_2 {
private:
	static void PrintView(auto view) {
		std::cout << typeid(view).name() << std::endl;
		for (int n : view) {
			std::cout << n << ", ";;
		}
		std::cout << std::endl;
	}

public:
	static void CreateViewToPrint() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<int> numbers{ 1, 5, 17, 42, 55 };
		PrintView(numbers);
		PrintView(std::views::all(numbers));
		PrintView(std::ranges::subrange(std::begin(numbers) + 1, std::end(numbers) - 1));
	}
};
#pragma endregion Chapter11_Section2

#pragma region Chapter11_Section3
class Chapter11_3 {
private:
	static void PrintSpan(std::span<int> span) {
		std::cout << "Number of items= " << span.size() << std::endl;
		for (auto i : span) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

public:
	static void CreateSpanToPrint() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<int> numbersVector{ 1, 5, 17, 42, 55 };
		PrintSpan(numbersVector);
		int numberArray[]{ 1, 5, 17, 42, 55, 67 };
		PrintSpan(numberArray);
	}
};
#pragma endregion Chapter11_Section3

#pragma region Chapter11_Section4
class Chapter11_4 {
private:
	static void LookAtSizedRange(std::ranges::sized_range<> auto range) {
		std::cout << "The size is " << range.size() << std::endl;
	}

public:
	static void CreateRangeToSize() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<int> numbersVector{ 1, 5, 17, 42, 55 };
		LookAtSizedRange(numbersVector);
	}
};
#pragma endregion Chapter11_Section4

#pragma region Chapter11_Section5
// example not essential for the content
#pragma endregion Chapter11_Section5

#pragma region Chapter11_Section6
class Chapter11_6 {
public:
	static void LookAtSubrange() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<int> numbersVector{ 1, 5, 17, 42, 55, 77, 121, 255 };

		std::cout << "All of vector: ";
		for (auto it = numbersVector.begin();
			it != numbersVector.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl << std::endl;

		auto startingIt = numbersVector.begin() += 2;
		auto endingIt = numbersVector.end() -= 1;
		auto sub = std::ranges::subrange(startingIt, endingIt);
		std::cout << "making subrange of third to second last, size="
			<< sub.size() << ": ";
		for (auto it = sub.begin(); it != sub.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "subrange (front-end) is " << sub.front() << "-" << sub.back()
			<< std::endl << std::endl;

		auto partialSub = sub.advance(3);
		std::cout << "partial subrange after advancing 3, size="
			<< partialSub.size() << ": ";
		for (auto it = partialSub.begin(); it != partialSub.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl << std::endl;

		partialSub = sub.advance(-2);
		std::cout << "partial subrange after advancing -2, size="
			<< partialSub.size() << ": ";
		for (auto n : partialSub) {
			std::cout << n << " ";
		}
		std::cout << std::endl << std::endl;

		std::cout << "getting an element of the original subrange, [1]="
			<< sub[1] << std::endl;
	}
};
#pragma endregion Chapter11_Section6

#pragma region Chapter11_Section7
class Chapter11_7_1 {
public:
	static void DanglingProblem() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		Chapter11_7_1* chapterToBeDelete = new Chapter11_7_1();
		Chapter11_7_1* pChapter = chapterToBeDelete;
		delete chapterToBeDelete;
		// pChapter is left dangling, will get exception if used

		int* pNumber = nullptr;
		{
			int numbers[5] = { 24, 31, 42, 55, 67 };
			pNumber = &numbers[1];
		}
		// numbers has gone out of scope, pNumber is left dangling

		std::vector<int>::iterator it;
		{
			std::vector<int> numbersVector{ 1, 5, 17, 42, 55, 77, 121, 255 };
			it = numbersVector.begin();
		}
		// the vector goes out of scope, and the iterator is left dangling
	}
};

class Chapter11_7_2 {
public:
	static void DanglingIterProblem() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		auto arrayThatWillCauseProblems = [] { return std::array{ 24, 31, 42, 55, 67 }; };
		auto badIter = std::ranges::max_element(arrayThatWillCauseProblems());
		if (std::is_same_v< std::ranges::dangling, decltype(badIter)>) {
			std::cout << "Bad iter cannot be used" << std::endl;
			//auto x = *badIter;
		}
	}
};

template <typename T, std::size_t N>
struct BorrowedSpan : std::span<T, N> { };
template <typename T, std::size_t N>
inline constexpr bool std::ranges::enable_borrowed_range<BorrowedSpan<T, N>> = true;

class Chapter11_7_3 {
public:
	static void UseBorrowedRange() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		auto mySpanByValue = [] {
			static int values[5]{ 24, 31, 42, 55, 67 };
			return BorrowedSpan<int, std::size(values)>{ values };
			};

		if (std::ranges::borrowed_range<BorrowedSpan<int, 1>>) {
			std::cout << "BorrowedSpan knows how not to leave dangling iterators" << std::endl;
		}

		auto goodIter = std::ranges::max_element(mySpanByValue());
		if (std::is_same_v<std::ranges::dangling, decltype(goodIter)> == false) {
			std::cout << "Good iter has current value of " << *goodIter << std::endl;
		}
	}
};
#pragma endregion Chapter11_Section7

#pragma region Chapter11_Section8
template <class T>
class MyView : public std::ranges::view_interface<MyView<T>> {
public:
	MyView(const std::vector<T>& vec) :
			vbegin(vec.cbegin()), 
			vend(vec.cend()) {}
	auto begin() const { return vbegin; }
	auto end() const { return vend; this->end(); }
private:
	typename std::vector<T>::const_iterator vbegin, vend;
};

class Chapter11_8 {
public:
	static void CreateViewInterface() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<std::string> ingredients =
		{ "salt", "pepper", "garlic", "thyme", "soy sauce" };
		MyView vv{ ingredients };
		if (vv.empty() == false) {
			std::cout << "There are " << vv.size() << " ingredients" << std::endl;
			for (auto it = vv.begin(); it != vv.end(); it++) {
				std::cout << *it << std::endl;
			}
			std::cout << "To repeat, they are: " << std::endl;
			for (auto i : vv) {
				std::cout << i << std::endl;
			}
		}
	}
};
#pragma endregion Chapter11_Section8

#pragma region Chapter11_Section9
// example not essential for the content
#pragma endregion Chapter11_Section9

void LookAtChapter11Topics()
{
	// works with compiler?						when tested			clang	gcc		msvc
	Chapter11_1::FindInRange();					// 20231031			yes		yes		yes
	Chapter11_2_1::StringViewExample();			// 20231031			yes		yes		yes
	Chapter11_2_2::CreateViewToPrint();			// 20231031			yes		yes		yes
	Chapter11_3::CreateSpanToPrint();			// 20231031			yes		yes		yes
	Chapter11_4::CreateRangeToSize();			// 20231031			yes		yes		yes
	Chapter11_6::LookAtSubrange();				// 20231031			yes		yes		yes
	/* do not need to run examples for
	*	section 7, for viewing only */
	Chapter11_7_1::DanglingProblem();			// 20231031			yes		yes		yes
	Chapter11_7_2::DanglingIterProblem();		// 20231031			yes		yes		yes
	Chapter11_7_3::UseBorrowedRange();			// 20231031			yes		yes		yes
	Chapter11_8::CreateViewInterface();			// 20231031			yes		yes		yes
}
