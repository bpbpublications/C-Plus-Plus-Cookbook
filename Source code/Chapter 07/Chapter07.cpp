#include <concepts>
#include <cmath>
#include <iostream>
#include <list>
#include <numeric>
#include <string>

// for now we are ignoring we are 
#pragma warning( disable : 4244 )

#ifdef __clang__
static const char* COMPILER = __VERSION__;
#elif __GNUC__
static const char* COMPILER = "gcc: " __VERSION__;
#elif (_MSC_VER)
static std::string COMPILER = std::string("MSVC: " + std::to_string(_MSC_VER));
#endif

#pragma region 7_1
class Chapter7_1_1 {
private:
	static unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static int LookAtPotatoCount() {
		unsigned int guests = 5;
		unsigned int household = 4;
		unsigned int unexpected = 2;
		auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_1_Average = 2.0;
		auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average;
		auto safePotatoCount = std::ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average);

		std::cout << "probable=" << probablyPotatoCount << ", maybe=" << maybePotatoCount << ", result=" << safePotatoCount << std::endl;
		return safePotatoCount;
	}
public:
	static void PrintThePotatoCount() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		auto number = LookAtPotatoCount();
		std::cout << "The potato count is: " << number << std::endl;
	}
};

class Chapter7_1_2 {
private:
	static unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static int LookAtPotatoCount() {
		unsigned int guests = 5;
		unsigned int household = 4;
		unsigned int unexpected = 2;
		auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_1_Average = 2.0;
		auto potatoCount = std::ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average);

		//std::cout << "probable=" << probablyPotatoCount << ", maybe=" << maybePotatoCount << ", result=" << safePotatoCount << std::endl;
		return potatoCount;
	}

public:
	static int PrintThePotatoCount() {
		//std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		return  LookAtPotatoCount();
		//std::cout << "The potato count is: " << number << std::endl;
	}
};

class Chapter7_1_3 {
private:
	static unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_1_Average = 2.0;
		auto potatoCount = std::ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average);

		return potatoCount;
	}

public:
	static int PrintThePotatoCount() {
		// std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		return LookAtPotatoCount();
		//std::cout << "The potato count is: " << number << std::endl;
	}
};

class Chapter7_1_4 {
private:
	static constexpr unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

public:
	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_1_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average);
#endif

		//std::cout << "probable=" << probablyPotatoCount << ", maybe=" << maybePotatoCount << ", result=" << potatoCount << std::endl;
		return potatoCount;
	}

public:
	static int PrintThePotatoCount() {
		// std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		return LookAtPotatoCount();
		// std::cout << "The potato count is: " << number << std::endl;
	}
};

// same as 4, but compiling with optimization
class Chapter7_1_5 {
private:
	static constexpr unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_1_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_1_Average);
#endif
		//std::cout << "probable=" << probablyPotatoCount << ", maybe=" << maybePotatoCount << ", result=" << potatoCount << std::endl;
		return potatoCount;
	}

public:
	static int PrintThePotatoCount() {
		//std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		return LookAtPotatoCount();
		//std::cout << "The potato count is: " << number << std::endl;
	}
};
#pragma endregion 7_1

class Chapter7_2 {
private:
	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

#ifndef __clang__
	constexpr static int LookAtPotatoCountWithWeights(int(*list)[2], size_t count) {
		std::list<double>* weightedCount = new std::list<double>();

		// TODO: how can we check if our percentages add up to 100? 
		int totalPercent{ 0 };
		for (size_t i = 0; i < count; ++i) {
			totalPercent += list[i][1];
			weightedCount->push_back(list[i][0] * list[i][1]);
		}
		long total = std::accumulate(weightedCount->begin(), weightedCount->end(), 0);
		delete weightedCount;

		if (totalPercent != 100) {
			std::cout << "Math is a little bit off, should be 100%, but instead is: " << totalPercent << std::endl;
		}

		return constexpr_ceil(total / (totalPercent * 1.0));
	}

	constexpr static int UpdatedLookAtPotatoCount() {
		int list[3][2] = { {9,80}, {10,15}, {11, 5} };
		auto result = LookAtPotatoCountWithWeights(list, 3);
		return result;
	}
#endif

public:
	static void PrintThePotatoCount() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

#ifdef __clang__
		std::cout << "not implemented yet" << std::endl;
#else
		auto number = UpdatedLookAtPotatoCount();
		std::cout << "The potato count is: " << number << std::endl;
#endif
	}
};

#pragma region 7_3
class Chapter7_3_1 {
private:
	static constexpr unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_3_Average = 2.0;
		auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_3_Average);
		// cannot do output at compile time
		//std::cout << "probable=" << probablyPotatoCount << ", maybe=" << maybePotatoCount << ", result=" << potatoCount << std::endl;

		// we would get a compiler error
		// static_assert(potatoCount == 12);
		return potatoCount;
	}

public:
	static void PrintThePotatoCount() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		auto number = LookAtPotatoCount();
		std::cout << "The potato count is: " << number << std::endl;
	}
};

class Chapter7_3_2 {
private:
#ifdef _MSC_VER
	static constexpr unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}
#else
	static consteval unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}
#endif
	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_3_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_3_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_3_Average);

		static_assert(potatoCount == 12);
#endif

		return potatoCount;
	}

public:
	static void PrintThePotatoCount() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;
#ifndef __GNUC__
		std::cout << "only partially implemented" << std::endl;
#endif

		auto number = LookAtPotatoCount();
		std::cout << "The potato count is: " << number << std::endl;
	}
};
#pragma endregion 7_3

class Chapter7_4 {
private:
	static consteval unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_4_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_4_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_4_Average);

		static_assert(potatoCount == 12);
#endif
		return potatoCount;
	}

	static const int GetPotatoCountThatIncludesLeftovers() {
		constinit static auto count = LookAtPotatoCount();
		count *= 1.5;
		return count;
	}

public:
	static void PrintThePotatoCount() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;
#ifdef __clang__
		std::cout << "only partially implemented" << std::endl;
#endif

		auto number = GetPotatoCountThatIncludesLeftovers();
		std::cout << "The potato count is: " << number << std::endl;
	}
};

#pragma region 7_5
class Chapter7_5_1 {
private:
	static consteval unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_5_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_5_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_5_Average);

		static_assert(potatoCount == 12);
#endif
		return potatoCount;
	}

	static constexpr int GetPotatoCountThatIncludesLeftovers() {
		constexpr auto Increaser = 1.5;
		constexpr auto count = LookAtPotatoCount() * Increaser;
		return count;
	}

	static const int Chapter7_5_1_UpperLimit = 20;
	static constexpr auto BuyBigBagOfPotatoes() {
#if (__GNUC__) && (__cpp_if_constexpr >= 201606L)
		if constexpr (GetPotatoCountThatIncludesLeftovers() < Chapter7_5_1_UpperLimit) {
			return false;
		}
		else {
			// return someUnknownValue;
			// return "wow, that is a lot!";
			return true;
		}
#else
		// Not working yet with compiler
		return true;
#endif
	}

public:
	static void PrintThePotatoDecision() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;
#ifndef __GNUC__
		std::cout << "only partially implemented" << std::endl;
#endif

		auto decision = BuyBigBagOfPotatoes();
		std::cout << "The idea of buying a big bag is: " << std::boolalpha << decision << std::endl;
	}
};

class Chapter7_5_2 {
private:
	// will not compile !
	//template<typename T>
	//static int GetServingSize(const T& value) noexcept {
	//    if (std::is_integral<T>::value) {
	//        return value;
	//    }
	//    else {
	//        return sizeof(T);
	//    }
	//}

public:
	static void GetServingSizeDescription() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;
		std::cout << "does not compile properly" << std::endl;

		int amount = 42;
		std::string servingSize = "lots";
		//std::cout << "Serving size of " << amount << " is " << GetServingSize(amount)
		//    << ", and size of " << servingSize << " is " << GetServingSize(servingSize) << std::endl;
	}
};

class Chapter7_5_3 {
private:
	template<typename T>
	static auto GetServingSize(const T& value) noexcept {
		if constexpr (std::is_integral<T>::value) {
			return value;
		}
		else {
			return value.size();
		}
	}

	template<typename T>
	static auto AnotherGetServingSize(const T& value) noexcept {
		if constexpr (requires(T val) {
			{ val.count() } -> std::convertible_to<int>;
		}) {
			return value.count();
		}
		else if constexpr (requires(T val) { 
			{ val.size() } -> std::convertible_to<int>; }) 
		{
			return value.size();
		}
		else if constexpr (requires(T val) { 
			{ val } -> std::convertible_to<int>; }) 
		{
			return value;
		}
		else {
			return 0;
		}
	}

public:
	static void GetServingSizeDescription() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		int amount = 42;
		std::string servingSize = "lots";
		std::cout << "Serving size of " << amount << " is " << GetServingSize(amount)
			<< ", and size of " << servingSize << " is " << GetServingSize(servingSize) << std::endl;

		std::list<char> biggerServiceSize{ 't', 'h', 'o', 'u', 's', 'a', 'n', 'd', 's' };
		std::string biggerServiceSizeText = std::accumulate(biggerServiceSize.begin(), biggerServiceSize.end(), std::string(""));
		std::cout << "Or serving size of " << amount << " is " << AnotherGetServingSize(amount) << std::endl
			<< ", and size of " << servingSize << " is " << AnotherGetServingSize(servingSize) << std::endl
			<< ", and size of " << biggerServiceSizeText << " is " << AnotherGetServingSize(biggerServiceSize) << std::endl;
	}
};
#pragma endregion 7_5

#pragma region 7_6
class Chapter7_6_1 {
private:
	static consteval unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef __GNUC__
		return std::ceil(num);
#else
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_5_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_5_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_5_Average);

		static_assert(potatoCount == 12);
#endif
		return potatoCount;
	}

public:
	static constexpr int Chapter7_6_1_UpperLimit = 20;
	static constexpr auto BuyBigBagOfPotatoes() {
#ifdef __GNUC__
		if constexpr (LookAtPotatoCount() < Chapter7_6_1_UpperLimit) {
			return false;
		}
		else {
			return true;
		}
#else
		// Not working yet with compiler
		return false;
#endif
	}

	static const int& GetPotatoCountThatIncludesLeftovers() {
		constinit static auto count = LookAtPotatoCount();
		count *= 1.5;
		return count;
	}

	static constexpr auto AskHowManyPotatoesToBuy() {
		if (std::is_constant_evaluated()) {
			auto count = LookAtPotatoCount();
			return count;

		}
		else {
			return 100;
		}
	}

	static int WorkWithPotatoes() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;
#ifndef __GNUC__
		std::cout << "not implemented yet" << std::endl;
#endif

		int result = GetPotatoCountThatIncludesLeftovers();

		constexpr auto count_constexpr = AskHowManyPotatoesToBuy();
		auto count_auto = AskHowManyPotatoesToBuy();
		const auto count_const = AskHowManyPotatoesToBuy();

		std::cout << " count_constexpr=" << count_constexpr <<
			"\n count_auto=" << count_auto <<
			"\n count_const=" << count_const
			<< std::endl;
		return result;
	}
};

class Chapter7_6_2 {
private:
	static consteval unsigned int HowManyPotatoesRequiredForMashed(unsigned int people) {
		return people + (people / 5);
	}

	static constexpr int32_t constexpr_ceil(float num)
	{
#ifdef _MSC_VER
		return (static_cast<float>(static_cast<int32_t>(num)) == num)
			? static_cast<int32_t>(num)
			: static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
#else
		return std::ceil(num);
#endif
	}

	constexpr static int LookAtPotatoCount() {
		const unsigned int guests = 5;
		const unsigned int household = 4;
		const unsigned int unexpected = 2;
		constexpr auto probablyPotatoCount = HowManyPotatoesRequiredForMashed(household + guests);
		constexpr auto maybePotatoCount = HowManyPotatoesRequiredForMashed(household + guests + unexpected);
		constexpr double Chapter7_6_Average = 2.0;
#ifdef __clang__
		constexpr auto potatoCount = (probablyPotatoCount + maybePotatoCount) / Chapter7_6_Average;
#else
		constexpr auto potatoCount = constexpr_ceil((probablyPotatoCount + maybePotatoCount) / Chapter7_6_Average);
		static_assert(potatoCount == 12);
#endif
		return potatoCount;
	}

	static const int Chapter7_6_2_UpperLimit = 20;
	static constexpr int GetLimit() { return 20; }
	static constexpr auto BuyBigBagOfPotatoes() {
#ifdef __GNUC__
		constexpr auto count = LookAtPotatoCount();
		if constexpr (count < GetLimit()) {
			return false;
		}
		else {
			return true;
		}
#else
		// Not working yet with compiler
		return false;
#endif
	}

	static constexpr auto AskHowManyPotatoesToBuy() {
#if __cpp_if_consteval >= 202106L
		if consteval {
			return LookAtPotatoCount();
		}
		else {
			return 100;
		}
#else
		return 100;
#endif
	}

	static const int& GetPotatoCountThatIncludesLeftovers() {
		constinit static auto count = LookAtPotatoCount();
		count *= 1.5;
		return count;
	}

public:
	static int WorkWithPotatoes() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;
#ifndef __GNUC__
		std::cout << "not implemented yet" << std::endl;
#endif

		int result = GetPotatoCountThatIncludesLeftovers();

		constexpr auto count_constexpr = AskHowManyPotatoesToBuy();
		std::cout << "count_constexpr=" << count_constexpr << std::endl;
		auto count_auto = AskHowManyPotatoesToBuy();
		std::cout << "count_auto=" << count_auto << std::endl;
		const auto count_const = AskHowManyPotatoesToBuy();
		std::cout << "count_const=" << count_auto << std::endl;

		return result;
	}
};
#pragma endregion 7_6

class Chapter7_7 {
private:
	class Recipe {
	public:
		std::string Name;
	};

public:
	static void WorkWithRecipe() {
		std::cout << std::endl << std::endl << __FUNCTION__ << ", for " << COMPILER << std::endl;

		Recipe r;
		Recipe* pr = &r;
		const Recipe* otherR = &r;
		//otherR->Name = "something great!"; // cannot change content
		Recipe* const pFixedR = &r;
		Recipe r2;
		//pFixedR = &r2; // cannot change where it is pointing
	}
};

void LookAtChapter7Topics()
{
	// works with compiler?						when tested		    clang	msvc	gcc
	Chapter7_1_1::PrintThePotatoCount();        //  2023.11.11      yes     yes     yes
	Chapter7_1_2::PrintThePotatoCount();        //  2023.11.11      yes     yes     yes
	Chapter7_1_3::PrintThePotatoCount();        //  2023.11.11      yes     yes     yes
	Chapter7_1_4::PrintThePotatoCount();        //  2023.11.11      part    most    yes
	Chapter7_1_5::PrintThePotatoCount();        //  2023.11.11      part    most    yes

	Chapter7_2::PrintThePotatoCount();          //  2023.11.11      no      most    yes

	Chapter7_3_1::PrintThePotatoCount();        //  2023.11.11      most    most    yes
	Chapter7_3_2::PrintThePotatoCount();        //  2023.11.11      part    no      yes

	Chapter7_4::PrintThePotatoCount();          //  2023.11.11      no      most    yes

	Chapter7_5_1::PrintThePotatoDecision();     //  2023.11.11      no      no      yes
	Chapter7_5_2::GetServingSizeDescription();  //  2023.11.11      purposely none
	Chapter7_5_3::GetServingSizeDescription();  //  2023.11.11      yes     yes     yes

	Chapter7_6_1::WorkWithPotatoes();           //  2023.11.11      no      no      yes
	Chapter7_6_2::WorkWithPotatoes();           //  2023.11.11      no      no      yes

	Chapter7_7::WorkWithRecipe();               //  2023.11.11      yes     yes     yes
}

