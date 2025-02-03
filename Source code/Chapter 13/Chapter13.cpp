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
#include <stdint.h>

class Chapter13_1 {
public:
	static void LookAtMinMax() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		const std::deque<int> myQueue = { 99, 17, 37, 34, 67, 42, 99 };
		auto PrintFn = [](const auto& n) { std::cout << n << ", "; };

		std::cout << "Full range: ";
		std::ranges::for_each(myQueue, PrintFn);
		std::cout << std::endl;

		const auto minNum = std::ranges::min(myQueue);
		const auto maxNum = std::ranges::max(myQueue);
		std::cout << "Min=" << minNum << ", and Max=" << maxNum << std::endl;

		const auto minIt = std::ranges::min_element(myQueue);
		const auto maxIt = std::ranges::max_element(myQueue);
		const auto minDistance = std::distance(myQueue.begin(), minIt);
		const auto maxDistance = std::distance(myQueue.begin(), maxIt);
		std::cout << "Found Min at index [" << minDistance << "]= " << *minIt
			<< ", and Max at index [" << maxDistance << "]= " << *maxIt << std::endl;

		std::cout << std::endl << "Or if want to figure out both at same time:" << std::endl;
		std::ranges::minmax_result<decltype(myQueue)::value_type> minMax =
			std::ranges::minmax(myQueue);
		std::cout << "Min=" << minMax.min << ", and Max=" << minMax.max << std::endl;
		auto [min2It, max2It] = std::ranges::minmax_element(myQueue);
		const auto min2Distance = std::distance(myQueue.begin(), min2It);
		const auto max2Distance = std::distance(myQueue.begin(), max2It);
		std::cout << "Found Min at index [" << min2Distance << "]= " << *min2It
			<< ", and Max at index [" << max2Distance << "]= " << *max2It << std::endl << std::endl;

		std::vector<int> myVector = {};
		// cannot get min/max on empty range, or else exception
		// auto maxVector = std::ranges::max(myVector);
		const auto maxItVector = std::ranges::max_element(myVector);
		auto vBegin = myVector.begin();
		auto vEnd = myVector.end();
		if (std::ranges::empty(myVector)) {
			if (maxItVector == vEnd && maxItVector == vBegin) {
				std::cout << "Makes sense for the max to point to the beginning or end"
					<< std::endl << " (both null) since no items in the range." << std::endl;
			}
		}

		std::cout << std::endl << "Clamping results:" << std::endl;
		const int lowerClamp = 40;
		const int higherClamp = 45;
		for (auto n : myQueue) {
			auto clampedResult = std::ranges::clamp(n, lowerClamp, higherClamp);
			if (clampedResult == n) {
				std::cout << "Value of " << n << " was within range of "
					<< lowerClamp << "-" << higherClamp << std::endl;
			}
			else if (clampedResult == lowerClamp) {
				std::cout << "Value of " << n << " was below lower limit " << lowerClamp << std::endl;
			}
			else if (clampedResult == higherClamp) {
				std::cout << "Value of " << n << " was above upper limit " << higherClamp << std::endl;
			}
		}
	}
};

class Chapter13_Common {
public:
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
		auto PrintFn = [](const auto& x) { std::cout << x << sep; };

		if (not title.empty()) {
			std::cout << title << " ";
		}
		else {
			std::cout << "Full range : ";
		}
		std::ranges::for_each(r, PrintFn);
		std::cout << std::endl;
	}
};

class Chapter13_2_1 {
private:
	static void CheckIfSorted(std::ranges::range auto r)
	{
		if (std::ranges::is_sorted(r, std::ranges::greater())) {
			std::cout << "Range is sorted in descending order" << std::endl;
		}
		else if (std::ranges::is_sorted(r, std::ranges::less())) {
			std::cout << "Range is sorted in ascending order" << std::endl;
		}
		else {
			std::cout << "Range is not sorted" << std::endl;
		}
	}

public:

	struct NumberAndWord {
		int number;
		std::string word;
		template<class Os> friend
			Os& operator<< (Os& os, NumberAndWord const& p) {
			return os << std::left << std::setw(8) << p.number << " : "
				<< p.word << '\n';
		}
	};

	static void LookAtSort() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque<int> myQueue = { 99, 17, 37, 34, 67, 42, 99 };

		Chapter13_Common::PrintRange(myQueue);
		CheckIfSorted(myQueue);

		std::ranges::sort(myQueue);
		Chapter13_Common::PrintRange(myQueue, "Afer sort: ");
		CheckIfSorted(myQueue);
		std::cout << std::endl;

		std::vector<std::string> words = { "C++", "23", "is", "a", "fantastic", "release", "!" };
		Chapter13_Common::PrintRange(words, "My sentence before sort: ");
		std::ranges::sort(words);
		Chapter13_Common::PrintRange(words, "Afer doing a word sort : ");
		std::cout << std::endl;

		const std::deque<int> myQueue2 = { 99, 17, 37, 34, 67, 42, 99 };
		std::vector<NumberAndWord> myPairs;
		for (int i = 0; i < myQueue2.size(); i++) {
			myPairs.push_back({ myQueue2[i], words[i] });
		}
		Chapter13_Common::PrintRange(myPairs, "Before a projected sort: \n");
		std::ranges::sort(myPairs, std::ranges::greater(), &NumberAndWord::word);
		Chapter13_Common::PrintRange(myPairs, "Afer a projected sort: \n");
		std::cout << std::endl;
	}
};

class Chapter13_2_2 {
public:
	static void LookAtPartialSort() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque<int> myQueue3 = { 99, 17, 37, 34, 67, 42, 99 };
		Chapter13_Common::PrintRange(myQueue3, "Before partial sort of 3 items: ");
		std::ranges::partial_sort(myQueue3, myQueue3.begin() + 3);
		Chapter13_Common::PrintRange(myQueue3, "After partial sort of 3 items: ");
		auto partiallySortedIt = std::ranges::is_sorted_until(myQueue3);
		auto partiallySortedDistance = std::distance(myQueue3.begin(), partiallySortedIt) - 1;
		std::cout << "Seems to be sorted for: " << partiallySortedDistance << " items." << std::endl;
		std::cout << std::endl;

		const std::deque<int> myQueue4 = { 99, 17, 37, 34, 67, 42, 99 };
		Chapter13_Common::PrintRange(myQueue4, "Source pre partial_sort_copy : ");
		std::vector<int> myVectorDest = { 1, 2, 3 };
		Chapter13_Common::PrintRange(myVectorDest, "Dest before partial_sort_copy: ");
		auto partialSortCopyResult = std::ranges::partial_sort_copy(myQueue4, myVectorDest);
		Chapter13_Common::PrintRange(myQueue4, "Source after partial_sort_copy  : ");
		Chapter13_Common::PrintRange(myVectorDest, "Dest after the partial_sort_copy: ");
		std::cout << std::endl;

		std::deque<int> myQueue5 = { 37, 99, 17, 34, 67, 42, 99 };
		Chapter13_Common::PrintRange(myQueue5, "Before nth sort: ");
		auto partialNthSortResult = std::ranges::nth_element(myQueue5, myQueue5.begin() + 4);
		Chapter13_Common::PrintRange(myQueue5, "After nth sort : ");
		std::cout << std::endl;

		std::deque<int> myQueue6 = { 37, 99, 17, 34, 67, 42, 99 };
		Chapter13_Common::PrintRange(myQueue6, "Before partitioned: ");
		auto Partition42Fn = [](int n) { return n <= 42; };
		auto partitionSub = std::ranges::partition(myQueue6, Partition42Fn);
		Chapter13_Common::PrintRange(myQueue6, "After partitioned : ");
		auto isPartitioned = std::ranges::is_partitioned(myQueue6, Partition42Fn);
		std::cout << "Size of partition tail =" << partitionSub.size()
			<< ", and " << (isPartitioned ? "is" : "is not") << " partitioned" << std::endl;
		auto partitionPoint = std::ranges::partition_point(myQueue6, Partition42Fn);
		auto partitionDistance = std::distance(myQueue6.begin(), partitionPoint);
		std::cout << "Partition is split after " << partitionDistance << " items" << std::endl;
	}
};

class Chapter13_3_1 {
public:
	static void LookAtRangeSearch() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque myQueue7 = { 37, 99, 17, 34, 67, 42, 99, 4, 23, 27 };
		std::ranges::sort(myQueue7);
		Chapter13_Common::PrintRange(myQueue7, "After sorted: ");

		if (std::ranges::binary_search(myQueue7, 42)) {
			std::cout << "Found 42 via binary search" << std::endl;
			std::cout << std::endl;
		}

		const auto lower = std::ranges::lower_bound(myQueue7, 42);
		const auto upper = std::ranges::upper_bound(myQueue7, 42);
		Chapter13_Common::PrintRange(std::ranges::subrange(lower, upper), "Lower to Upper bounds: ");
		Chapter13_Common::PrintRange(std::ranges::subrange(myQueue7.begin(), lower), "Start to Lower bounds: ");
		Chapter13_Common::PrintRange(std::ranges::subrange(upper, myQueue7.end()), "Above upper bounds: ");
		std::cout << std::endl;

		const auto equalRangeResult = std::ranges::equal_range(myQueue7, 42);
		const auto beforeEqualRange = std::ranges::subrange(myQueue7.begin(), equalRangeResult.begin());
		const auto AfterEqualRange = std::ranges::subrange(equalRangeResult.begin() + 1, myQueue7.end());
		Chapter13_Common::PrintRange(equalRangeResult, "EqualRange: ");
		Chapter13_Common::PrintRange(beforeEqualRange, "Before EqualRange: ");
		Chapter13_Common::PrintRange(AfterEqualRange, "After EqualRange: ");
		std::cout << std::endl;

		const std::deque<int> myMiniQueue1 = { 17, 37 };
		const auto includeResult1 = std::ranges::includes(myQueue7, myMiniQueue1);
		std::cout << "The big range " << (includeResult1 ? "includes" : "does not include") << " the ";
		Chapter13_Common::PrintRange(myMiniQueue1, "smaller Range: ");
		const std::deque<int> myMiniQueue2 = { 1, 99 };
		const auto includeResult2 = std::ranges::includes(myQueue7, myMiniQueue2);
		std::cout << "The big range " << (includeResult2 ? "includes" : "does not include") << " this ";
		Chapter13_Common::PrintRange(myMiniQueue2, "other mini Range: ");
	}
};

class Chapter13_3_2 {
public:
	static void LookAtSetOperations() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque<int> myQueue8 = { 37, 99, 17, 34, 67, 42, 99, 4, 23, 18, 27 };
		std::ranges::sort(myQueue8);
		Chapter13_Common::PrintRange(myQueue8, "Sorted First Range: ");
		std::array<int, 5> myList9 = { 99, 1, 67, 42, 65 };
		std::ranges::sort(myList9);
		Chapter13_Common::PrintRange(myList9, "Sorted Second Range: ");
		std::cout << std::endl;

		std::vector<int> myVectorIntersection{};
		std::ranges::set_intersection(myQueue8, myList9, std::back_inserter(myVectorIntersection));
		Chapter13_Common::PrintRange(myVectorIntersection, "Set intersection: ");

		std::vector<int> myVectorUnion{};
		std::ranges::set_union(myQueue8, myList9, std::back_inserter(myVectorUnion));
		Chapter13_Common::PrintRange(myVectorUnion, "Set union: ");

		std::vector<int> myVectorDiff{};
		std::ranges::set_difference(myQueue8, myList9, std::back_inserter(myVectorDiff));
		Chapter13_Common::PrintRange(myVectorDiff, "Set difference {first (not in) second}: ");
		std::vector<int> myVectorDiff2{};
		std::ranges::set_difference(myList9, myQueue8, std::back_inserter(myVectorDiff2));
		Chapter13_Common::PrintRange(myVectorDiff2, "Set difference {second (not in) first}: ");

		std::vector<int> myVectorSymmetricDiff{};
		std::ranges::set_symmetric_difference(myQueue8, myList9, std::back_inserter(myVectorSymmetricDiff));
		Chapter13_Common::PrintRange(myVectorSymmetricDiff, "Set symmetric difference (first,second): ");
	}
};

class Chapter13_3_3 {
public:
	static void LookAtMerge() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque<int> myQueue10 = { 37, 99, 17, 34, 67 };
		std::ranges::sort(myQueue10);
		Chapter13_Common::PrintRange(myQueue10, "Sorted First Range: ");
		std::array<int, 6> myList11 = { 42, 99, 4, 23, 18, 27 };
		std::ranges::sort(myList11);
		Chapter13_Common::PrintRange(myList11, "Sorted Second Range: ");
		{
			std::vector<int> myVectorMerge{};
			const auto ret = std::ranges::merge(myQueue10, myList11, std::back_inserter(myVectorMerge));
			Chapter13_Common::PrintRange(myVectorMerge, "Merged output (presized)   : ");
		}
		{
			std::vector<int> myVectorMerge{};
			myVectorMerge.resize(myQueue10.size() + myList11.size());
			const auto ret = std::ranges::merge(myQueue10, myList11, myVectorMerge.begin());
			Chapter13_Common::PrintRange(std::ranges::subrange(myVectorMerge.begin(), ret.out), "Merged output (back-insert): ");
		}
		std::cout << std::endl;

		std::vector<int> myVector12 = { 1, 4, 17, 18, 67, 99, 99,     23, 27, 34, 37, 42, 65 };
		Chapter13_Common::PrintRange(myVector12, "Before inline merge, sorted by halves:");
		auto inlineMergeResult = std::ranges::inplace_merge(myVector12.begin(), myVector12.begin() + 7, myVector12.end());
		Chapter13_Common::PrintRange(myVector12, "After we executed the inline merge   :");
	}
};

class Chapter13_4 {
public:
	static void LookAtPermutations() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::deque<int> myQueue13 = { 99, 18, 42, 67 };
		Chapter13_Common::PrintRange(myQueue13, "Original range:");
		std::cout << std::endl;

		std::ranges::sort(myQueue13);
		int counter = 0;
		do {
			std::stringstream ss;
			ss << "Next #";
			ss << counter++;
			ss << ": ";
			Chapter13_Common::PrintRange(myQueue13, ss.str());
		} while (std::ranges::next_permutation(myQueue13).found);
		std::cout << std::endl;

		std::ranges::sort(myQueue13, std::greater());
		counter = 0;
		do {
			std::stringstream ss;
			ss << "Prev #";
			ss << counter++;
			ss << ": ";
			Chapter13_Common::PrintRange(myQueue13, ss.str());
		} while (std::ranges::prev_permutation(myQueue13).found);

		const std::array<int, 4> myArray14 = { 18, 42, 99, 67 };
		const std::array<int, 3> myArray15 = { 42, 99, 67 };
		const std::vector<int> myVector16 = { 18, 42, 66, 67 };
		const auto myArray14PermResult = std::ranges::is_permutation(myQueue13, myArray14);
		const auto myArray15PermResult = std::ranges::is_permutation(myQueue13, myArray15);
		const auto myVector16PermResult = std::ranges::is_permutation(myQueue13, myVector16);
		std::cout << "This " << (myArray14PermResult ? "  is  " : "is not") << " a permutation:";
		Chapter13_Common::PrintRange(myArray14, " ");
		//
		std::cout << "This " << (myArray15PermResult ? "  is  " : "is not") << " a permutation:";
		Chapter13_Common::PrintRange(myArray15, " ");
		//
		std::cout << "This " << (myVector16PermResult ? "  is  " : "is not") << " a permutation:";
		Chapter13_Common::PrintRange(myVector16, " ");
	}
};

class Chapter13_5 {
public:
	static void LookAtFolds() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::vector<int> myVector17 = { 1, 2, 3, 4 };
		Chapter13_Common::PrintRange(myVector17);

		auto addLeftVector = std::ranges::fold_left(myVector17, 0, std::plus<int>());
		auto multVector = std::ranges::fold_left(myVector17, 1, std::multiplies<int>());
		std::cout << "The adding fold-left total is: " << addLeftVector << ", " << std::endl
			<< "and the multiplication fold total is: " << multVector << std::endl;
		std::cout << std::endl;
		//int x = ((((((0 * 10) + 1) * 10) + 2) + 3) * 10) + 4;
		//int y = (((((((0 * 10) + 4) * 10) + 3) * 10) + 2) * 10) + 1;

		auto MultiplyLeftFn = [](const auto& existing, const auto& v) { return (existing * 10) + v; };
		auto MultiplyRightFn = [](const auto& v, const auto& existing) { return (existing * 10) + v; };
		auto shiftLeftVector = std::ranges::fold_left(myVector17, 0, MultiplyLeftFn);
		auto shiftRightVector = std::ranges::fold_right(myVector17, 0, MultiplyRightFn);
		std::cout << "The shifting fold-left total is: " << shiftLeftVector << " vs fold-right is: " << shiftRightVector << std::endl;
	}
};

void LookAtChapter13Topics()
{
	// works with compiler?					when tested		clang	msvc	gcc
	Chapter13_1::LookAtMinMax();			//2023.12.09	yes		yes		yes
	Chapter13_2_1::LookAtSort();			//2023.12.09	yes		yes		yes
	Chapter13_2_2::LookAtPartialSort();		//2023.12.09	yes		yes		yes
	Chapter13_3_1::LookAtRangeSearch();		//2023.12.09	yes		yes		yes
	Chapter13_3_2::LookAtSetOperations();	//2023.12.09	yes		yes		yes
	Chapter13_3_3::LookAtMerge();			//2023.12.09	yes		yes		yes
	Chapter13_4::LookAtPermutations();		//2023.12.09	yes		yes		yes
	Chapter13_5::LookAtFolds();				//2023.12.09	yes		yes		yes
}