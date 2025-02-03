#include <concepts>
#include <iostream>
#ifdef __cpp_lib_print
#include <print>
#endif
#include <iomanip>
#include <ranges>
#include <algorithm>
#include <string>
#include <chrono>
#include <ctime>
#include <time.h>
#include <cassert>
#include <vector>
#include <thread>
#include <limits>
#include <numeric>
#include <numbers>
#include <bit>
#include <cstdint>
#include <bitset>
#include <format>
#include <fstream> 
#include <map> 

#pragma region Chapter18_Section1
struct Helloer {
	std::string name;
	int age;
};

template <>
struct std::formatter<Helloer> : std::formatter<std::string> // to get a default parse function
{
	auto format(const Helloer &h, format_context& ctx) const {
		return h.name.empty() ? 
			format_to(ctx.out(), "I do not have a name.", "ok to have more arguments than you use") :
			format_to(ctx.out(), "Hello, my name is {1}, I am {0}.", h.age, h.name);
	}
};

class Chapter18_1 {
public:
	static void LookAtStringFormatting()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_lib_format
		std::cout << std::format("The answer to everything is {}.\n", 42);
		// compile time error, due to wrong number of parameters
		// std::cout << std::format("The answer to everything is {}, but not {}.\n", 42);
		std::cout << std::format("The C++{1} release is {0}\n", "great!", 23);
		std::cout << std::format("Is this correct? {0}/{0:d} or {1}\n", true, false);
		double num = 0.1867248;
		std::cout << std::format("small number = {0:.02}, or more precisely {0:.05}\n", num);
		std::cout << std::format("or something in between = {:{}.{}f}\n", num, 8, 3, "unused");
		std::cout << std::endl;

		std::cout << std::format("{0:}, {0:+}, {0:-}, {0: }, {0:06d}", 42) << std::endl;
		std::cout << std::format("{0:04x}, {0:04X}, {0:#04x}, {0:b}, {0:#b}", 42) << std::endl;
		std::cout << std::format("{0:}, {0:+}, {0:-}, {0: }, {0:06d}", -42) << std::endl;
		std::cout << std::format("{0:}, {0:+}, {1:}, {1:+}",
			std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()) << std::endl;
		std::cout << std::endl;

		std::string name = "C++ 23";
		std::cout << "pad left numbers" << ", result=" << std::format("{:10}", 23) << std::endl;
		std::cout << "pad right strings" << ", result=" << std::format("{:10}", name) << "." << std::endl;
		std::cout << "pad to the right with character" << ", result=" << std::format("{:!<10}", name) << std::endl;
		std::cout << "pad to the left with character" << ", result=" << std::format("{:!>10}", name) << std::endl;
		std::cout << "centre with character" << ", result=" << std::format("{:!^10}", name) << std::endl;
		std::cout << std::endl;

#ifndef _MSC_VER
		Helloer h1{};
		Helloer h2{ "Bjarne", 73 };
		//std::string personFmt = "{}";
		std::cout << std::format("Person#1 {} \n", h1);
		std::cout << std::format("Person#2 {0} \n", h2);
#else
		std::cout << "Part of feature not yet implemented for this compiler." << std::endl;
#endif

#ifndef _MSC_VER
		std::ofstream outputFile{ "output.txt", std::ofstream::out };
		std::format_to(std::ostream_iterator<char>(outputFile), "The C++{1} release is {0}\n", "great!", 23);
		outputFile.close();
#else
		std::cout << "Part of feature not yet implemented for this compiler." << std::endl;
#endif

#if __cpp_lib_format_ranges > 202207L
		std::vector<int> manyNumbers{ 17, 31, 37, 42, 67 };
		// not working yet :-(
		constexpr std::string_view sv = "many numbers {} \n";
		std::cout << std::format(sv, manyNumbers);
#else
		std::cout << "Part of feature not yet implemented for this compiler." << std::endl;
#endif
#else
		std::cout << "Feature not yet implemented for this compiler at all." << std::endl;
#endif
	}
};
#pragma endregion Chapter18_Section1

class Chapter18_2 {
public:
	static void LookAtPrint() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_lib_print
		std::print("The C++{1} release is {0}\n", "great.", 23);
		std::println("The C++{1} release is {0}", "great!", 23);

		std::ofstream outputFile{ "output.txt", std::ofstream::out };
		std::println(outputFile, "The C++{1} release is {0}", "great!!", 23);
		outputFile.close();
#else
		std::cout << "Feature not yet implemented for this compiler at all." << std::endl;
#endif
	}
};

class Chapter18_3 {
public:
	static bool InSensitiveEndWith(const std::string_view& lhs, const std::string_view& rhs) {
		auto min = std::min(lhs.size(), rhs.size());
#ifdef __cpp_lib_ranges_zip
		// might be cleaner once we have zip/zip_transform
#endif
		auto lPart = std::ranges::reverse_view(lhs) | std::views::take(min);
		auto rPart = std::ranges::reverse_view(rhs) | std::views::take(min);
		auto itL = lPart.begin();
		auto itR = rPart.begin();
		bool result = true;
		for (; itL != lPart.end() && itR != rPart.end(); ) {
			if (std::toupper(*itL) != std::toupper(*itR)) {
				result = false;
				break;
			}
			//
			itL++;
			itR++;
		}

		return result;
	}

	static void LookAtStartsWith() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::string message{ "C++23 is great" };
		std::string startTerm{ "C++" };
		std::string endTerm{ "great" };
		std::string badTerm{ "bad" };
		std::cout << "Message is: " << std::quoted(message) << std::endl;
		std::cout << (message.starts_with(startTerm) ? "Starts with: " : "Does not start with: ") << std::quoted(startTerm) << std::endl;
		std::cout << (message.ends_with(endTerm) ? "Ends with: " : "Does not end with: ") << std::quoted(endTerm) << std::endl;
		std::cout << std::endl;
		std::cout << (message.starts_with(badTerm) ? "Starts with: " : "Does not start with: ") << std::quoted(badTerm) << std::endl;
		std::cout << (message.ends_with(badTerm) ? "Ends with: " : "Does not end with: ") << std::quoted(badTerm) << std::endl;
		std::cout << std::endl;
		std::string upperEndTerm{ "GREAT" };
		std::cout << (message.ends_with(upperEndTerm) ? "Ends with: " : "Does not end with: ") << std::quoted(upperEndTerm) << std::endl;
		std::cout << (InSensitiveEndWith(message, upperEndTerm) ? "Case insensitive Ends with: " : "Case insensitive does not end with: ") << std::quoted(upperEndTerm) << std::endl;
	}
};

class Chapter18_4 {
public:
	static void LookAtRangeEnhancements() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if (__cpp_lib_containers_ranges >=	202202L)
		const auto goodMeals = std::vector<std::string>{ "breakfast", "lunch", "dinner" };
		auto badMeals = std::vector<std::string>{ "cookies", "donuts", "ice-cream" };
		badMeals.assign_range(goodMeals);
		std::cout << "The bad meals are no longer bad:" << std::endl;
		for (auto meal : badMeals) {
			std::cout << meal << std::endl;
		}
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

class Chapter18_5 {
public:
	static void LookAtEnums() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		enum SimpleMeal { breakfast, lunch, dinner };
		enum SimpleCookware { fryPan, pot, wok, roastingPan };

		SimpleMeal sm = breakfast;
		// most compilers will check is assigning to same type
		// sm = wok;
		if (sm == SimpleCookware::fryPan) {
			std::cout << "eating a frying pan" << std::endl;
		}

		enum class BetterMeal { breakfast, lunch, dinner, };
		enum class BetterCookware { fryPan, pot, wok, roastingPan, };
		// does not compile, needs better scope
		// BetterMeal bm = dinner;
		BetterMeal bm = BetterMeal::dinner;
		// does not compile, since needs to specify enum type
		// if (bm == wok) std::cout << "eating a work for dinner" << std::endl;
		//
		{
			using enum BetterMeal;
			// since enum is scoped in this block scope, can specify without being fully specific
			bm = lunch;
		}
		// since the using statement is out of scope, needs to be fully specified
		// bm = breakfast;
		{
			switch (bm) {
				using enum BetterMeal;
			case breakfast: std::cout << "eating breakfast: "; break;
			case lunch: std::cout << "eating lunch: "; break;
			case dinner: std::cout << "eating dinner: "; break;
			}
		}

		enum struct BreakfastDish { eggs, pancakes, waffles, };
		enum struct LunchDish { eggs, sandwich, soup, };
		BreakfastDish bd;
		{
			using enum BreakfastDish;
			// compiler will not allow this enum because it has a conflicting value (eggs in both enums)
			// using enum LunchDish;
			bd = eggs;
		}
		{
			using BreakfastDish::eggs, BreakfastDish::pancakes;
			BreakfastDish todaysBreakfast = BreakfastDish::waffles;
			if (todaysBreakfast == eggs) {
				std::cout << "3 eggs, scrambled";
			}
			else if (todaysBreakfast == pancakes) {
				std::cout << "2 pancakes, with jam";
			}
			else if (todaysBreakfast == BreakfastDish::waffles) {
				std::cout << "2 waffles, with syrup";
			}
		}
	}
};

class Chapter18_6 {
public:
	static void LookAtDates() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		using namespace std::chrono;
		month m(October); // 1-based
		month m2{ 10 };
		assert(m == m2);
		auto result = m + months(3);
		assert(result == January);

		weekday wd(Thursday); // (sort-of) 0-based, starting on Sunday
		weekday wd2(4);
		// assert(wd == m); // knows it cannot compare different types
		assert(wd == wd2);
		wd += days{ 3 };
		wd2 = weekday{ 7 }; // also set to Sunday
		assert(wd == wd2);

		weekday_indexed wdi{ wd,3 };
		wdi = Sunday[3];

		year yrsh{ 2112 };
		year_month_day ymd{ yrsh,December, day{31} };
		month_weekday mwd{ June, wdi };
		mwd = { June, Saturday[2] };

		month_day_last mdlast{ February }; // last day of the month

		year_month_day_last ymdLastLeap{ year{2024}, mdlast };
		year_month_day_last ymdLastNoLeap{ year{2023}, mdlast };
		std::cout << "Day for " << ymdLastLeap << " is " << ymdLastLeap.day() << ", is leap? " << std::boolalpha << ymdLastLeap.year().is_leap()
			<< ",\n but day for " << ymdLastNoLeap << " is " << ymdLastNoLeap.day() << ", is leap? " << std::boolalpha << ymdLastNoLeap.year().is_leap() << std::endl;

		year_month_day ymd1{ June / 4d / 1976y };
		year_month_day ymd2{ 1976y / June / 4d }; // cannot do 6m, since could be confused with minutes
		year_month_day ymd3{ year{1976} / month{6} / day{4} };
		year_month_day ymd4{ 4d / June / 1976y };
		year_month_day_last ymdLast{ 2024y / (January + months(1)) / last };
		month_day md{ September / 25 };
		md = { September / 25d };
		month_weekday mwd2{ April / Monday[2] };
		month_weekday_last mwdL{ October, weekday_last{Tuesday} };
		mwdL = { December, Tuesday[last] };
		auto ymwdL{ year{2023} / mwdL };

		auto ymdOver = std::vector<year_month_day>{
			{ February / 28d / 2024y },
			{ February / 28d / 2023y },
			{ December / 28d / 2024y },
			{ year{2024} / mwdL},
			{ ymwdL },
		};
		auto Add4Days = [](const year_month_day& ymd) -> sys_days { return sys_days(ymd) + days(4); };
		auto datesOver = std::vector<sys_days>{};
		std::ranges::copy(std::views::transform(ymdOver, Add4Days), std::back_inserter(datesOver));

		auto ymdOverAgain = std::vector<year_month_day>{};
		for (auto d : datesOver) {
			ymdOverAgain.push_back(d);
		}
		for (auto i = 0; i < ymdOver.size(); i++) {
			std::cout << ymdOver[i] << " +4= " << datesOver[i] << ", same as " <<
				std::format("{:%A, %B %d, %Y}", ymdOverAgain[i]) << std::endl;
		}

		auto now = system_clock::now();
		year_month_day ymdNow{ floor<days>(now) };
		std::cout << "Today: day=" << ymdNow.day() << ", month=" << ymdNow.month() << ", year=" << ymdNow.year() << std::endl;
		std::cout << std::endl;
	}
};

class Chapter18_7 {
public:
	static void LookAtTimes() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		using namespace std::chrono;

		auto now = system_clock::now();
		auto nowHere = current_zone()->to_local(now);
		std::cout << "Now is " << now << " in UTC, or " << std::format("{:%X}", nowHere) << " for local" << std::endl;

		auto durLocal = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
		auto daysTodayFloor = floor<days>(durLocal);
		hh_mm_ss hmsNow{ floor<milliseconds>(durLocal - daysTodayFloor) };
		std::cout << "Now is also " << hmsNow.hours() << ": " << hmsNow.minutes() << ": " << hmsNow.seconds() << std::endl;
		std::cout << std::endl;

		auto later = nowHere + 1h;
		std::cout << "An hour later will be " << std::format("{:%X, or %r}", later) << std::endl;
		std::cout << std::endl;

		auto oneSecond = 1000ms;
		auto timerStart = high_resolution_clock::now();
		std::this_thread::sleep_for(oneSecond);
		auto timerEnd = high_resolution_clock::now();
		duration delta = timerEnd - timerStart;
		std::cout << "Took " << delta.count() << " ticks to sleep 1000ms" << std::endl;
		auto deltaMs = delta / 1ms;
		std::cout << "Or took " << duration_cast<milliseconds>(delta).count() << " milliseconds to sleep 1000ms"
			<< ", which should be same as " << deltaMs << std::endl;
		hh_mm_ss hms{ delta };
		std::cout << "And should be the same as: " << hms << std::endl << std::endl;
		std::cout << std::endl;

		auto listHours = { 0h, 1h, 13h, 23h };
		for (auto itH : listHours) {
			bool itPm = is_pm(itH);
			std::cout << "hour= " << itH << ", count=" << itH.count() << ", is AM? " << std::boolalpha << is_am(itH) << ", is PM? " << itPm << std::endl;
			hours h12 = make12(itH);
			hours h24 = make24(h12, itPm);
			std::cout << "after make12: " << h12 << ", after make24: " << h24 << std::endl;
			auto halfDayLater = itH + 12h;
			std::cout << "12 hours later: " << halfDayLater << std::boolalpha << ", is AM? " << is_am(halfDayLater) << ", is PM? " << is_pm(halfDayLater) << std::endl;
			std::cout << std::endl;
		}
	}
};

class Chapter18_8 {
public:
	static void LookAtTimezone() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		auto now = std::chrono::system_clock::now();
		auto myZone = std::chrono::current_zone();
		auto myMins = std::chrono::minutes(myZone->get_info(now).offset / std::chrono::seconds(60));
		std::vector<std::string_view> othersInSameTz{};
		for (auto itDb = std::chrono::get_tzdb_list().begin(); itDb != std::chrono::get_tzdb_list().end(); itDb++) {
			std::cout << "zone=" << itDb->version << std::endl;
			for (auto it = itDb->zones.begin(); it != itDb->zones.end(); it++) {
				if (myZone->name() == it->name()) {
					std::cout << "Here I am: " << it->name() << "   !!!!!!!!!! "
						<< myMins << " from UTC" << std::endl;
				}
				else {
					auto thereMins = std::chrono::minutes(it->get_info(now).offset / std::chrono::seconds(60));
					if (myMins == thereMins) {
						othersInSameTz.push_back(it->name());
					}
				}
			}
			auto joinedCharacters = std::ranges::join_with_view(othersInSameTz, ", ");
			std::cout << "Others in same timezone: ";
			for (auto c : joinedCharacters) std::cout << c;
			std::cout << std::endl << std::endl;

			std::cout << "Local time:" << std::chrono::zoned_time{ myZone->name(), now } << ", offset=" << myMins << '\n';
			try
			{
				const std::chrono::time_zone* tzIST = std::chrono::locate_zone("IST");
				std::cout << std::chrono::zoned_time{ tzIST, now } << " for " << tzIST->name() << std::endl;

				auto offsetIST = std::chrono::minutes(tzIST->get_info(now).offset / std::chrono::seconds(60));
				auto tzDelta = offsetIST - myMins;
				std::chrono::hh_mm_ss tzDeltaHms{ tzDelta };
				std::cout << "Difference between local time and IST=" << tzDelta << ", " << tzDeltaHms << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << "Problem checking timezone. " << ex.what() << std::endl;
			}
		}
	}
};

class Chapter18_9 {
public:
	static void LookAtMidpoint() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<std::pair<int, int>> bunchesOfInts{ {-42, 42}, {1,2}, {0, 100}, {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}
		, {std::numeric_limits<int>::max(), std::numeric_limits<int>::max() - 2} };
		std::vector<std::pair<long long, long long>> bunchesOfLongLongs{ {-42, 42}, {0, 100}, {std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()}
		, {std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max() - 2} };
		std::vector<std::pair<double, double>> bunchesOfDoubles{ {-42.0, 42.0}, {222.222222, 444.444444}, {std::numeric_limits<double>::min(), std::numeric_limits<double>::max()} };

		for (auto pair : bunchesOfInts) {
			std::cout << "Mid point of " << pair.first << ", and " << pair.second << " = " << std::midpoint(pair.first, pair.second) << std::endl;
		}
		std::cout << std::endl;
		for (auto pair : bunchesOfLongLongs) {
			std::cout << "Mid point of " << pair.first << ", and " << pair.second << " = " << std::midpoint(pair.first, pair.second) << std::endl;
		}
		std::cout << std::endl;
		for (auto pair : bunchesOfDoubles) {
			std::cout << "Mid point of " << pair.first << ", and " << pair.second << " = " << std::midpoint(pair.first, pair.second) << std::endl;
		}
	}
};

#pragma region Chapter18_Section10
template <typename T>
T DiameterFn(T r, T pi) { return 2.0 * r; }
template <typename T>
T CircumferenceFn(T r, T pi) { return 2.0 * r * pi; }
template <typename T>
T AreaFn(T r, T pi) { return r * r * pi; }

class Chapter18_10 {
public:
	static void LookAtNumbers() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::cout
			<< std::setprecision(std::numeric_limits<float>::max_digits10)
			<< "float:       " << std::numbers::pi_v<float> << std::endl
			<< std::setprecision(std::numeric_limits<double>::max_digits10)
			<< "double:      " << std::numbers::pi_v<double> << std::endl
			<< std::setprecision(std::numeric_limits<long double>::max_digits10)
			<< "long double: " << std::numbers::pi_v<long double>
			<< std::endl << std::endl;

#ifdef _MSC_VER
		std::vector<double> radii{ 1.0, 2.0, 3.0, std::sqrt(std::numbers::inv_pi_v<double>) };
		for (auto r : radii) {
			std::cout
				<< std::setprecision(std::numeric_limits<double>::digits10)
				<< "r=" << r
				<< ", diameter=" << DiameterFn(r, std::numbers::pi)
				<< ", circumference=" << CircumferenceFn(r, std::numbers::pi)
				<< ", area=" << AreaFn(r, std::numbers::pi) << std::endl;
		}
#endif
	}
};
#pragma endregion Chapter18_Section10

#pragma region Chapter18_Section11
template <std::integral T>
void DumpBytes(T n, bool endLine) {
	std::cout << std::hex << std::uppercase << std::setfill('0')
		<< std::setw(sizeof(T) * 2) << n << " ( ";
	for (std::size_t i{}; i != sizeof(T); ++i, n >>= 8) {
		std::cout << std::setw(2) << static_cast<unsigned>(T(0xFF) & n) << ' ';
	}
	std::cout << ")" << std::dec << (endLine ? "\n" : "");
}
template <std::integral T>
void DumpAndReverse(std::string title, T n) {
	std::cout << title << " : ";
	DumpBytes(n, true);
	std::cout << "byteswap: ";
	DumpBytes(std::byteswap(n), true);
	std::cout << std::endl;
}

class Chapter18_11 {
public:
	static void LookAtBits_byteswap() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		DumpAndReverse("16 bits", std::uint16_t(0x0123));
		DumpAndReverse("32 bits", std::uint32_t(0x01234567));
		DumpAndReverse("64 bits", std::uint64_t(0x0123456789ABCDEF));
		std::cout << std::endl;
	}

	static void LookAtBits_has_single_bit() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<unsigned int> numbers{ 0, 1, 2, 3, 4, 7, 8, 16, 31, 32, };
		for (auto n : numbers) {
			std::cout << n << ": has_single_bit( " << std::bitset<8>(n) << " )= "
				<< std::boolalpha << std::has_single_bit(n) << std::endl;
		}
		std::cout << std::endl;
	}

	static void LookAtBits_bit_ceil_bit_floor() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<unsigned int> numbers{ 0, 1, 2, 3, 4, 7, 8, 16, 31, 32, };
		for (auto n : numbers) {
			auto n2c = std::bit_ceil(n);
			auto n2f = std::bit_floor(n);
			std::cout << "for " << n << ": bit_ceil( " << std::bitset<8>(n) << " ) = "
				<< std::boolalpha << n2c << " or " << std::bitset<8>(n2c)
				<< ", bit_floor = "
				<< std::boolalpha << n2f << " or " << std::bitset<8>(n2f)
				<< std::endl;
		}
		std::cout << std::endl;
	}

	static void LookAtBits_bit_width() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<unsigned int> numbers{ 0, 1, 2, 3, 4, 7, 8, 16, 31, 32, 255 };
		for (auto n : numbers) {
			std::cout << "for " << n << ": bit_width( " << std::bitset<8>(n) << " ) = "
				<< std::bit_width(n) << std::endl;
		}
		std::cout << std::endl;
	}

	static void LookAtBits_rotl_rotr() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::uint8_t n = 0b01101001;
		std::cout << "n       = " << std::bitset<8>(n)
			<< ", n        = " << std::bitset<8>(n)
			<< ", n        = " << std::bitset<8>(n)
			<< ", n       = " << std::bitset<8>(n) << std::endl;
		std::vector<int> numbers{ 1, 2, 4, 9, };
		for (auto shift : numbers) {
			auto shiftedL = std::rotl(n, shift);
			auto shiftednR = std::rotr(n, -shift);
			auto shiftednL = std::rotl(n, -shift);
			auto shiftedR = std::rotr(n, shift);
			std::cout << "rotl(n," << shift << ")=" << std::bitset<8>(shiftedL)
				<< ", rotr(n," << -shift << ")=" << std::bitset<8>(shiftednR)
				<< ", rotl(n," << -shift << ")=" << std::bitset<8>(shiftednL)
				<< ", rotr(n," << shift << ")=" << std::bitset<8>(shiftedR)
				<< std::endl;
		}
		std::cout << std::endl;
	}

	static void LookAtBits_countl_countr() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<std::uint8_t> numbers{ 0, 0b00010100, 0b11101011, 0b11111111 };
		for (auto n : numbers) {
			int iN = n;
			std::cout << iN << " or 0b" << std::bitset<8>(n) << ": "
				<< "countl_zero=" << std::countl_zero(n)
				<< ", countl_one=" << std::countl_one(n)
				<< ", countr_zero=" << std::countr_zero(n)
				<< ", countr_one=" << std::countr_one(n) << std::endl;
		}
		std::cout << std::endl;
	}

	static void LookAtBits_popcount() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<std::uint8_t> numbers{ 0, 0b00010100, 0b11101011, 0b11111111 };
		for (auto n : numbers) {
			std::cout << "popcount( " << std::bitset<8>(n) << " )= "
				<< std::popcount(n) << std::endl;
		}
		std::cout << std::endl;
	}

	static void LookAtBits_endian() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		if (std::endian::native == std::endian::big) {
			std::cout << "current system is using Big-endian";
		}
		else if (std::endian::native == std::endian::little) {
			std::cout << "current system is Little-endian";
		}
		else {
			std::cout << "current system is mixed-endian";
		}
		std::cout << std::endl << std::endl;
	}

	static void LookAtBits_bit_cast() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		double f64v = 10501430590.0;
		auto u64v = std::bit_cast<std::uint64_t>(f64v);
		auto f64vAgain = std::bit_cast<double>(u64v);
		std::cout
			<< "std::bit_cast<std::uint64_t>(" << std::fixed << f64v << ") == 0x"
			<< std::hex << u64v
			<< ", back to f64=" << std::fixed << f64vAgain << '\n';
		std::cout << std::endl;
	}

	static void LookAtBits() {
		LookAtBits_byteswap();
		LookAtBits_has_single_bit();
		LookAtBits_bit_ceil_bit_floor();
		LookAtBits_bit_width();
		LookAtBits_rotl_rotr();
		LookAtBits_countl_countr();
		LookAtBits_popcount();
		LookAtBits_endian();
		LookAtBits_bit_cast();
	}
};
#pragma endregion Chapter18_Section11

#pragma region Chapter18_Section12
struct strictDI {
	std::vector<int> numbers1;
	std::vector<int> numbers2;
};
struct strictDI2 {
	std::vector<int> numbers3;
	std::string message;
	std::vector<int> numbers4;
	strictDI innerDI;
};

class Chapter18_12 {
public:
	static void LookAtDesignatedInitializer() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::vector<int> numbers1 = { 1,2,3 };
		std::vector<int> numbers2{ 4,5,6 };

		strictDI2 s3{
			// member variables cannot be initialized out of order
			// .message = "Hello C++",
			.numbers3 { 1,2,3 },
			.message = "Hello C++",
			.numbers4 = { 4,5,6 },
			.innerDI {
				.numbers1 { 7,8},
				.numbers2 { 9, 0},
			},
		};
		std::cout << "s3= " << s3.message << std::endl;

		strictDI2 s4{
			{1,2}, "Hello C++23", {3,4}, {{5,6}, {7,8}}
		};
		std::cout << "s4= " << s4.message << std::endl;
	}
};
#pragma endregion Chapter18_Section12

void LookAtChapter18Topics()
{
	// works with compiler?						when tested			clang	gcc		msvc
	Chapter18_1::LookAtStringFormatting();	//  2023.12.03			most	most	part
	Chapter18_2::LookAtPrint();				//  2023.12.03			no		no		yes
	Chapter18_3::LookAtStartsWith();		//  2023.12.03			yes		yes		yes
	Chapter18_4::LookAtRangeEnhancements();	//  2023.12.03			no		no		yes	
	Chapter18_5::LookAtEnums();				//  2023.12.03			yes		yes		yes
	Chapter18_6::LookAtDates();				//  2023.12.03			yes		yes		yes
	Chapter18_7::LookAtTimes();				//  2023.12.03			yes		yes		yes
	Chapter18_8::LookAtTimezone();			//  2023.12.03			yes		yes		yes
	Chapter18_9::LookAtMidpoint();			//  2023.12.03			yes		yes		yes
	Chapter18_10::LookAtNumbers();			//  2023.12.03			yes		yes		yes
	Chapter18_11::LookAtBits();				//  2023.12.03			yes		yes		yes
	Chapter18_12::LookAtDesignatedInitializer();// 2023.12.03		yes		yes		yes
}
