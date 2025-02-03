#include <concepts>
#include <iterator>
#include <vector>
#include <deque>
#include <array>
#include <set>
#include <map>
#include <array>
#include <queue>
#include <iostream>
#include <forward_list>

#pragma region Chapter4_Section1
template<typename T>
	requires std::weakly_incrementable<typename T::iterator>
static void CycleThroughIngredientsPreAndPost(T collection) {
	auto iter = collection.begin();
	auto count = 0;
	while (iter != collection.end()) {
		std::cout << "Adding ingredient: " << *iter;
		if (count % 2 == 0) {
			std::cout << "\t\t\t\t(post-increment)";
			iter++;
		}
		else {
			std::cout << "\t\t\t\t(pre-increment)";
			++iter;
		}

		std::cout << std::endl;
		count++;
	}
}

class Chapter4_1 {
public:
	static void WeaklyIterateThroughIngredients() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::array<std::string, 5> ingredientsToAdd = { "hot sauce", "oregano", "vinegar", "course salt", "pepper" };
		CycleThroughIngredientsPreAndPost(ingredientsToAdd);
	}
};
#pragma endregion Chapter4_Section1

#pragma region Chapter4_Section2
template <typename T>
	requires std::input_or_output_iterator<typename T::iterator>
static void CycleThroughNumbersToUpdate(T& collection) {
	auto iter = collection.begin();
	auto count = 0;
	while (iter != collection.end()) {
		if (count % 2 == 1) {
			std::cout << "(changing value iterator is looking at)\t\t";
			auto temp = *iter;
			temp++;
			*iter = temp;
		}
		std::cout << "value=" << *iter << std::endl;
		count++;
		iter++;
	}
}

class Chapter4_2 {
private:
	static void PrintNumbers(const char* title, std::vector<int>& numbers) {
		std::cout << std::endl << "Printing numbers " << title << "\t\t:";
		for (auto it = numbers.begin(); it != numbers.end(); it++) {
			if (it != numbers.begin()) {
				std::cout << ", ";
			}

			std::cout << *it;
		}
		std::cout << std::endl << std::endl;
	}

public:
	static void IterateAndUpdate() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> numbers= { 27, 67, 37, 7, 77 };
		PrintNumbers("Before changes", numbers);
		CycleThroughNumbersToUpdate(numbers);
		PrintNumbers("After changes", numbers);
	}
};
#pragma endregion Chapter4_Section2

#pragma region Chapter4_Section3
// no example required
#pragma endregion Chapter4_Section3

#pragma region Chapter4_Section4
// no example required
#pragma endregion Chapter4_Section4

#pragma region Chapter4_Section5
// no example required
#pragma endregion Chapter4_Section5

#pragma region Chapter4_Section6
// no example required
#pragma endregion Chapter4_Section6

#pragma region Chapter4_Section7
// no example required
#pragma endregion Chapter4_Section7

#pragma region Chapter4_Section8
// no example required
#pragma endregion Chapter4_Section8

#pragma region Chapter4_Section9
// no example required
#pragma endregion Chapter4_Section9

#pragma region Chapter4_Section10
template < typename T>
requires std::forward_iterator<typename T::iterator>
static void CycleThroughItems(const std::string title, T collection) {
	auto startingIter = collection.begin();
	auto endIter = collection.end();
	auto curentIter = startingIter;
	std::cout << "first pass of : " << title << std::endl;
	for (; curentIter != endIter; ++curentIter) {
		if (curentIter != startingIter) {
			std::cout << ", ";
		}
		std::cout << *curentIter;
	}
	std::cout << std::endl;
	//
	std::cout << "second pass:" << std::endl;
	for (curentIter = startingIter; curentIter != endIter; ++curentIter) {
		if (curentIter != startingIter) {
			std::cout << ", ";
		}
		std::cout << *curentIter;
	}
	std::cout << std::endl << std::endl;
}

class Chapter4_10 {
public:
	static void LookAtCollectionsForward() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> vectorNumbers = { 1,2,3,4,5 };
		CycleThroughItems("vector of numbers", vectorNumbers);

		std::deque<double> dequeNumbers = { 1.01,2.02,3.03,4.05,5.05 };
		CycleThroughItems("double queue of numbers", dequeNumbers);

		std::array<char, 5> arrayLetters = { 'a','b','c','d','e' };
		CycleThroughItems("array of letters", arrayLetters);

		std::set<int> set = { 1,2,3,4,5 };
		CycleThroughItems("set", set);

		std::forward_list<int> forward_list = { 1,2,3,4,5 };
		CycleThroughItems("forward_list", set);

		std::queue<double> queueNumbers(dequeNumbers);
		// does not compile
		// CycleThroughItems("queue", queueNumbers);
	}
};
#pragma endregion Chapter4_Section10

#pragma region Chapter4_Section11
template < typename T>
	requires std::bidirectional_iterator<typename T::iterator>
static void CycleThroughItemsBackwards(const std::string title, T collection) {
	auto startingIter = collection.begin();
	auto lastIter = (collection.end()); lastIter--;
	auto curentIter = lastIter;
	std::cout << "first pass of : " << title << std::endl;
	for (; ; --curentIter) {
		if (curentIter != lastIter) {
			std::cout << ", ";
		}
		std::cout << *curentIter;
		if (curentIter == startingIter) break;
	}
	std::cout << std::endl;
	std::cout << "second pass:" << std::endl;
	for (curentIter = lastIter; ; --curentIter) {
		if (curentIter != lastIter) {
			std::cout << ", ";
		}
		std::cout << *curentIter;
		if (curentIter == startingIter) break;
	}
	std::cout << std::endl << std::endl;
}

class Chapter4_11 {
public:
	static void LookAtCollectionsBackward() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> vectorNumbers = { 1,2,3,4,5 };
		CycleThroughItemsBackwards("vector of numbers", vectorNumbers);

		std::deque<double> dequeNumbers = { 1.01,2.02,3.03,4.05,5.05 };
		CycleThroughItemsBackwards("double queue of numbers", dequeNumbers);

		std::array<char, 5> arrayLetters = { 'a','b','c','d','e' };
		CycleThroughItemsBackwards("array of letters", arrayLetters);

		std::set<int> set = { 1,2,3,4,5 };
		CycleThroughItemsBackwards("set", set);

		std::forward_list<int> forward_list = { 1,2,3,4,5 };
		CycleThroughItemsBackwards("forward_list", set);
	}
};
#pragma endregion Chapter4_Section11

#pragma region Chapter4_Section12
template < typename T>
requires std::random_access_iterator <typename T::iterator>
static void FirstSimpleLookAtRandom(T& collection) {
	auto iter = collection.begin();
	std::cout << "current value at beginning=" << *iter << std::endl;
	iter++;
	std::cout << "current value after inc 1 =" << *iter << std::endl;
	iter--;
	std::cout << "current value after dec 1 =" << *iter << std::endl;
	++iter;
	std::cout << "current value after inc 1 =" << *iter << std::endl;
	--iter;
	std::cout << "current value after dec 1 =" << *iter << std::endl;
	//
	iter += 3;
	std::cout << "current value after inc 3 =" << *iter << std::endl;
	iter -= 2;
	std::cout << "current value after dec 2 =" << *iter << std::endl;
	//
	std::cout << "current value of fourth # =" 
			<< collection[4] << std::endl;
}

class Chapter4_12_1 {
public:
	static void SimpleLookAtVector() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> vectorNumbers = { 1,2,3,4,5 };

		FirstSimpleLookAtRandom(vectorNumbers);
	}
};

class Chapter4_12_2 {
private:
	static void RepositionIterator(const std::random_access_iterator auto beginning,
			int delta,
			std::random_access_iterator auto& current) {
		const std::random_access_iterator auto before(current);
		if (delta == 1) {
			++current;
		}
		else if (delta == -1) {
			current--;
		}
		else if (delta < 0) {
			current -= std::abs(delta);
		}
		else {
			current += delta;
		}
		//
		auto distanceFromBeginning = std::distance(beginning, current);
		std::cout << "after moving " << delta << ", value@"
			<< " [" << distanceFromBeginning << "]=" << *current
			<< ", distance changed=" << std::distance(before, current)
			<< std::endl;
	}

	template<typename T>
		requires std::random_access_iterator<typename T::iterator>
	static void SimpleLookAtRandomDistance(T& collection) {
		// start with the current at the beginning
		auto current = collection.begin();
		RepositionIterator(collection.begin(), 0, current);
		RepositionIterator(collection.begin(), 1, current);
		RepositionIterator(collection.begin(), -1, current);
		RepositionIterator(collection.begin(), 3, current);
		RepositionIterator(collection.begin(), -2, current);

		std::cout << "current value of fourth # =" << collection[4] << std::endl;
	}

public:
	static void SimpleLookAtVector() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> vectorNumbers = { 1,2,3,4,5 };

		std::cout << "values : ";
		auto index = 0;
		for (auto it = vectorNumbers.begin(); it != vectorNumbers.end(); ++it) {
			if (it != vectorNumbers.begin()) {
				std::cout << ", ";
			}
			std::cout << "v[" << index++ << "]= " << *it;
		}
		std::cout << std::endl << std::endl;
		SimpleLookAtRandomDistance(vectorNumbers);
		std::queue q1(vectorNumbers);
		// does not compile since queue does not comply to concept
		// SimpleLookAtRandomDistance(q1);
	}
};
#pragma endregion Chapter4_Section12

#pragma endregion Chapter4_Section13
class Chapter4_13 {
private:
	static void
		RepositionIterator(const std::random_access_iterator auto beginning,
			int delta, std::random_access_iterator auto& current) {
		const std::random_access_iterator auto before(current);
		current += delta;
		auto distanceFromBeginning = std::distance(beginning, current);
		std::cout << "after moving " << delta << ", value@"
			<< " [" << distanceFromBeginning << "]=" << *current
			<< ", distance changed=" << std::distance(before, current)
			<< std::endl;
	}

	template<typename T>
		requires std::random_access_iterator<typename T::iterator>
	static void SimpleLookAtRandomDistance(T& collection) {
		// start with the current at the beginning
		auto current = collection.begin();
		RepositionIterator(collection.begin(), 0, current);
		RepositionIterator(collection.begin(), 1, current);
		RepositionIterator(collection.begin(), -1, current);
		RepositionIterator(collection.begin(), 3, current);
		RepositionIterator(collection.begin(), -2, current);

		std::cout << "current value of fourth # =" << collection[4] << std::endl;
	}

	static void RepositionContiguousIterator(std::random_access_iterator auto beginning,
		int delta, std::contiguous_iterator auto& current) {
		const std::random_access_iterator auto before(current);
		current += delta;
		//
		auto absDist = std::distance(beginning, current);
		auto addrBefore = std::to_address(before);
		auto addrAfter = std::to_address(current);
		std::cout << "value after moving " << delta << ", current value@"
			<< " [" << absDist << "]=" << *current
			<< ", distance changed=" << std::distance(before, current)
			<< ",\n\t\taddrBefore=" << addrBefore
			<< ", addrAfter=" << addrAfter
			<< ", address diff=" << (addrAfter - addrBefore)
			<< std::endl;
	}

	template<typename T>
		requires std::contiguous_iterator<typename T::iterator>
	static void SimpleLookAtContiguous(T& collection) {
		// start with the current at the beginning
		auto current = collection.begin();
		RepositionContiguousIterator(collection.begin(), 0, current);
		RepositionContiguousIterator(collection.begin(), 1, current);
		RepositionContiguousIterator(collection.begin(), -1, current);
		RepositionContiguousIterator(collection.begin(), 3, current);
		RepositionContiguousIterator(collection.begin(), -2, current);

		std::cout << "current value of fourth # =" << collection[4] << std::endl;
	}

public:
	static void SimpleLookAtVectorAndDeque() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque<double> dequeNumbers = { 1.01,2.02,3.03,4.05,5.05 };
		std::cout << "Look at random deque\n";
		std::cout << "double values : ";
		auto index = 0;
		for (auto it = dequeNumbers.begin(); it != dequeNumbers.end(); ++it) {
			if (it != dequeNumbers.begin()) {
				std::cout << ", ";
			}
			std::cout << "v[" << index++ << "]= " << *it;
		}
		std::cout << std::endl << std::endl;

		SimpleLookAtRandomDistance(dequeNumbers);

		std::vector<int> vectorNumbers = { 1,2,3,4,5 };
		std::cout << "\ninteger values : ";
		index = 0;
		for (auto it = vectorNumbers.begin(); it != vectorNumbers.end(); ++it) {
			if (it != vectorNumbers.begin()) {
				std::cout << ", ";
			}
			std::cout << "v[" << index++ << "]= " << *it;
		}
		std::cout << std::endl << std::endl;

		std::cout << "Look at contiguous vector\n";
		SimpleLookAtContiguous(vectorNumbers);

		// fails to compile since a deque is not contiguous
		// std::cout << "Look at contiguous deque\n";
		// SimpleLookAtContiguous(dequeNumbers);
	}
};

void LookAtChapter4Topics() {
	// works with compiler?								when tested		clang	gcc		msvc
	Chapter4_1::WeaklyIterateThroughIngredients();	//  2023.11.04		yes		yes		yes
	Chapter4_2::IterateAndUpdate();					//  2023.11.04		yes		yes		yes
	Chapter4_10::LookAtCollectionsForward();		//  2023.11.04		yes		yes		yes
	Chapter4_11::LookAtCollectionsBackward();		//  2023.11.04		yes		yes		yes
	Chapter4_12_1::SimpleLookAtVector();			//  2023.11.04		yes		yes		yes
	Chapter4_12_2::SimpleLookAtVector();			//  2023.11.04		yes		yes		yes
	Chapter4_13::SimpleLookAtVectorAndDeque();		//  2023.11.04		yes		yes		yes
}
