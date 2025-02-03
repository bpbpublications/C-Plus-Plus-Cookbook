#include <concepts>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <array>
#include <stack>
#include <queue>
#include <deque>
#include <ranges>
//#include <flatset>
//#include <flatmap>
#include <iterator>
#include <type_traits>
#include <array>
#include <memory>
#include <type_traits>
#include <utility>
#include <algorithm>
#ifdef __cpp_lib_mdspan
#include <mdspan>
#endif

static void LookAtContains() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::vector<int> v{ 4, 17, 37, 42, 67 };
	std::list<int> l{ 4, 17, 37, 42, 67 };
	std::array<int,5> a{ 4, 17, 37, 42, 67 };
	std::deque<int> d{ 4, 17, 37, 42, 67 };
	std::queue<int> q{d};
	std::stack<int> st{d};
	std::set<int> se{ 4, 17, 37, 42, 67 };
	std::map<int, char> m{ {4,'a'}, {17,'b'}, {37,'c'}, {42,'d'}, {67,'e'} };
	std::string message{ "C++23 is great!" };
	std::multiset<int> ms{ 4, 17, 37, 42, 67, 4 };
	std::multimap<int, char> mm{ {4,'a'}, {17,'b'}, {37,'c'}, {42,'d'}, {67,'e'}, {37,'f'} };

	std::cout << "vector can use ranges::contains=" << std::boolalpha << std::ranges::contains(v,42) << std::endl;
	std::cout << "list can use ranges::contains=" << std::boolalpha << std::ranges::contains(v,42) << std::endl;
	std::cout << "array can use ranges::contains=" << std::boolalpha << std::ranges::contains(a, 42) << std::endl;
	std::cout << "deque can use ranges::contains=" << std::boolalpha << std::ranges::contains(d, 42) << std::endl;
	//std::cout << "queue cannot use ranges::contains=" << std::boolalpha << std::ranges::contains(q, 42) << std::endl;
	//std::cout << "stack cannot use ranges::contains=" << std::boolalpha << std::ranges::contains(st, 42) << std::endl;

	std::cout << "set contains value=" << std::boolalpha << se.contains(42) << std::endl;
	std::cout << "set can use also ranges::contains=" << std::boolalpha << std::ranges::contains(se, 42) << std::endl;
	std::cout << "map contains value=" << std::boolalpha << m.contains(42) << std::endl;
	std::cout << "multiset contains value=" << std::boolalpha << ms.contains(42) << std::endl;
	std::cout << "multimap contains value=" << std::boolalpha << mm.contains(42) << std::endl;
	std::cout << "string contains value=" << message.contains("23") << std::endl;
}

static void LookAtFlatMapSet() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef NOTYET
	std::flat_set fs{};
	std::flat_map fm{};
	std::flat_multiset fms{};
	std::flat_multimap fmm{};
#endif
}

static void PrintSpan(std::string title, const std::span<int>& span) {
	std::cout << title << std::endl;
	for (int n : span) {
		std::cout << n << ", ";;
	}
	std::cout << std::endl;
}

static void LookAtCountedIterator() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::vector<int> manyNumbers = { 4, 42, 2, 99, 37, 17, 67, 14, 27, 33, 65 };
	std::counted_iterator<std::vector<int>::iterator> numberCounter{ manyNumbers.begin() + 3, 4 };
	std::counted_iterator<std::vector<int>::iterator> otherNumberCounter{ numberCounter };
	std::counted_iterator<std::vector<int>::iterator> yetAnotherNumberCounter{ numberCounter };
	PrintSpan("Original numbers", manyNumbers);
	std::cout << "Original count=" << manyNumbers.size() << std::endl;
	std::cout << "counted_iterator count=" << numberCounter.count() << std::endl;
	for (; numberCounter.count() != 0; ++numberCounter) {
		std::cout << "Current value=" << *numberCounter << ", distance to end=" << numberCounter.count() << std::endl;
	}

	std::ranges::subrange sub{ otherNumberCounter.base(), manyNumbers.end() };
	PrintSpan("Looking at numbers", sub);
	std::cout << std::endl;
	for (; otherNumberCounter != std::default_sentinel; otherNumberCounter++) {
		std::cout << "Other current value=" << *otherNumberCounter << ", distance to end=" << otherNumberCounter.count() << std::endl;
	}
	std::cout << std::endl;
	for (auto n = 0; n < yetAnotherNumberCounter.count(); n++) {
		std::cout << "yet Other current value [" << n << "]=" << yetAnotherNumberCounter[n] << std::endl;
	}
}

template<typename T>
void CheckBound(std::string title) {
	auto isBounded = std::is_bounded_array_v<T>;
	std::cout << std::boolalpha << title << (isBounded ? " is bounded" : " is not bounded");
	auto isUnbounded = std::is_unbounded_array_v<T>;
	std::cout << ", and is " << (isUnbounded ? "unbounded" : "not unbounded") << std::endl;
}
static void LookAtBounded() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	CheckBound<int>("int");
	CheckBound<int[]>("int[]");
	CheckBound<int[3]>("int[3]");
	CheckBound<int[][3]>("int[][3]");
	CheckBound<int[2][3]>("int[2][3]");
	CheckBound<std::array<int, 3>>("std::array<int, 3>");
	CheckBound<std::vector<int>>("std::vector<int>");
	CheckBound<std::counted_iterator<std::vector<int>::iterator>>("std::counted_iterator<std::vector<int>::iterator>");
}

static void LookAtToArray() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	auto c1 = { 1,2,3 };
	auto c3 = { 1.2, 3.4, 5.6 };
	std::map<int,char> m4 = { {1, 'a'}, {2, 'b'}, {3, 'c'}};
	auto s5 = "Hello C++23";
	int c7[3] = {1,2,3};
	int c8[2][3] = { {1,2,3}, {4,5,6} };

	// c1 is a std::initializer_list<int> and cannot be used in this case
	// auto a1 = std::to_array(c1);
	auto a2 = std::to_array({ 1,2,3 });
	std::cout << "Resulting type of a2: " << typeid(a2).name() << std::endl;
	
	auto a3 = std::to_array({ 1.2, 3.4, 5.6 });
	std::cout << "Resulting type of a3: " << typeid(a3).name() << std::endl;

	// cannot convert since m4 is a map
	// auto a4 = std::to_array(m4);
	auto a4 = std::to_array<std::pair<int,char>>({ {1, 'a'}, {2, 'b'}, {3, 'c'} });
	std::cout << "Resulting type of a4: " << typeid(a4).name() << std::endl;

	// cannot convert a const char *
	// auto a5 = std::to_array(s5);
	auto a6 = std::to_array("Hello C++23");
	std::cout << "Resulting type of a6: " << typeid(a6).name() << std::endl;

	auto a7 = std::to_array(c7);
	std::cout << "Resulting type of a7: " << typeid(a7).name() << std::endl;
	// compiler error for multidimensional arrays
	// auto a8 = std::to_array(c8);
}

static void LookAtErase() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::vector<int> originalNumbers = { 4, 42, 99, 37, 17, 27, 33, 65 };
	PrintSpan("Original numbers", originalNumbers);

	std::vector<int> manyNumbers{ originalNumbers };
	auto gone = manyNumbers.erase(manyNumbers.begin() + 3, manyNumbers.begin() + 5);
	PrintSpan("After vector erase", manyNumbers);
	std::cout << std::endl;

	std::vector<int> manyNumbers2{ originalNumbers };
	PrintSpan("before std::erase", manyNumbers2);
	auto result2 = std::erase(manyNumbers2, 42);
	std::cout << "# of 42 erased=" << result2 << std::endl;
	auto result3 = std::erase(manyNumbers2, 999);
	std::cout << "# of 999 erased=" << result3 << std::endl;
	PrintSpan("after std::erase", manyNumbers2);
	std::cout << std::endl;

	auto EndsWith7 = [](const auto& n) { return n % 10 == 7; };
	std::vector<int> manyNumbers3{ originalNumbers };
	PrintSpan("before std::erase_if", manyNumbers3);
	auto result4 = std::erase_if(manyNumbers3, EndsWith7);
	PrintSpan("before std::erase_if", manyNumbers3);
	std::cout << "# of *7 erased=" << result4 << std::endl;

	std::deque<int> dNumbers { 4, 42, 99, 37, 17, 27, 33, 65 };
	std::array<int,8> aNumbers { 4, 42, 99, 37, 17, 27, 33, 65 };
	std::list<int> lNumbers{ 4, 42, 99, 37, 17, 27, 33, 65 };
	std::set<int> seNumbers{ 4, 42, 99, 37, 17, 27, 33, 65 };
	std::map<int, char> mNumbers{ {4,'a'}, {42,'b'}, {99,'c'} };
	std::stack<int> stNumbers{ dNumbers };
	std::queue<int> qNumbers{ dNumbers };

	std::erase(dNumbers, 99);
	//std::erase(aNumbers, 99);
	std::erase(lNumbers, 99);
	//std::erase(seNumbers, 99);
	auto KeyEndsWith7 = [](const std::pair<int, char>& kvp) { return kvp.first % 10 == 7; };
	std::erase_if(mNumbers, KeyEndsWith7);
	//std::erase(stNumbers, 99);
	//std::erase(qNumbers, 99);
}

static void LookAtPairConstructors() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::deque<int> dNumbers{ 4, 42, 99, 37, 17, 27, 33, 65 };
	auto count = dNumbers.size();
	for (auto i = 0; i < count; i++) {
		std::cout << "number[" << i << "]=" << dNumbers[i] 
			<< (i>=1 && i<=(count-3-1) ? " * " : " ") << std::endl;
	}
	std::stack<int> stNumbers1{ dNumbers };
	std::cout << "Stack1 size=" << stNumbers1.size() << std::endl;
	std::stack<int> stNumbers2{ dNumbers.begin()+1, dNumbers.end()-3 };
	std::cout << "Stack2 size=" << stNumbers2.size() << std::endl;
	std::queue<int> qNumbers3{ dNumbers.begin() + 1, dNumbers.end() - 3 };
	std::cout << "Queue3 size=" << qNumbers3.size() << std::endl;
}

static void LookAtDefaultArguments() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
	std::map<std::string, std::vector<std::string>> m1;
#ifdef __cpp_lib_pair_ctor_default_tmpl_args
	m1.emplace("Hello", {});
	std::cout << "Has key? " << m1.contains("Hello") << ", vector size=" << m1["Hello"].size() << std::endl;
//#else
//	m1.emplace("Hello", std::vector<std::string>{});
#endif
}

static void LookAtPushRange() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_lib_containers_ranges
	std::deque<int> someNumbers{ 4, 42, 99, 37 };
	std::deque<int> moreNumbers{ 17, 27, 33, 65 };
	std::stack<int> st{ someNumbers };
	std::cout << "Stack starting with " << st.size();
	st.push_range(moreNumbers);
	std::cout << ", and now has " << st.size() << std::endl;
	//
	std::queue<int> q{ someNumbers };
	std::cout << "Queue starting with " << q.size();
	q.push_range(moreNumbers);
	std::cout << ", and now has " << q.size() << std::endl;
#endif
}

// from https://en.cppreference.com/w/cpp/container/mdspan link https://godbolt.org/z/PK7bccGr3
static void LookAtMdspan() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_lib_mdspan
	std::vector v = { 4, 42, 99, 37, 17, 27, 33, 65 };

	auto ms2 = std::mdspan(v.data(), 2, 4);
	std::cout << "Two dimensional 2x4" << std::endl;
	for (auto i = 0; i != ms2.extent(0); i++) {
		for (auto j = 0; j != ms2.extent(1); j++) {
			std::cout << "[" << i << "," << j << "]=" << ms2[i, j] << "   ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Three dimensional 2x2x2" << std::endl;
	//auto ms3 = std::experimental::mdspan(v.data(), 2, 2, 2);
	auto ms3 = std::mdspan(v.data(), 2, 2, 2);
	for (auto i = 0; i != ms3.extent(0); i++) {
		for (auto j = 0; j != ms3.extent(1); j++) {
			for (auto k = 0; k != ms3.extent(2); k++) {
				std::cout << "[" << i << "," << j << "," << k << "]=" << ms3[i, j, k] << "   ";
				ms3[i, j, k] += 1000;
			}
			std::cout << std::endl;
}
	}
	std::cout << std::endl;

	std::cout << "Original vector, after modifications" << std::endl;
	for (auto i = 0; i < v.size(); i++) {
		std::cout << "v[" << i << "]=" << v[i] << std::endl;
	}
#endif
}

void LookAtChapter17Topics()
{
	// works with compiler?			when tested			clang	gcc		msvc
	LookAtContains();			//	2023.10.21			yes		yes		yes
	LookAtFlatMapSet();			//	2023.10.21			no		no		no
	LookAtCountedIterator();	//	2023.10.21			yes		yes		yes
	LookAtBounded();			//	2023.10.21			yes		yes		yes
	LookAtToArray();			//	2023.10.21			yes		yes		yes
	LookAtErase();				//	2023.10.21			yes		yes		yes
	LookAtPairConstructors();	//	2023.10.21			yes		yes		yes
	LookAtDefaultArguments();	//	2023.10.21			no		no		no
	LookAtPushRange();			//	2023.10.21			no		no		yes
	LookAtMdspan();				//	2023.10.21			no		no		no
}
