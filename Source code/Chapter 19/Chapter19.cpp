#include <concepts>
#include <iostream>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <cstddef>
#include <vector>
#include <map>
#include <deque>
#include <array>
#include <unordered_map>
#include <memory>
#include <utility>
#include <string>
#include <optional>
#include <functional>
#include <algorithm>
#include <cmath> // for bit manipulation
#include <format>
#include <ostream>
#include <fstream> 
#include <bit>
#include <bitset>
#include <cstdint>
#include <spanstream>
#include <stdexcept>
#include <cassert>
#include <iomanip>
#include <expected>
#include <string_view>
#include <typeinfo>

class Chapter19_1 {
public:
	static void LookAtTemplateLambdas() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		auto Cpp14AutoLambda = [](auto&& x, auto&& y) {
			UseMyTypes(std::forward<decltype(x)>(x), std::forward<decltype(y)>(y));
			};

		auto Cpp20TemplatedLambda = [] <class X, class Y>(X && x, Y && y) {
			UseMyTypes(std::forward<X>(x), std::forward<Y>(y));
		};
	}
};

class Chapter19_2 {
	template<std::integral TIntegral, std::integral... TRest>
	static constexpr TIntegral Lcm(const TIntegral& first, const TIntegral& second, const TRest& ... rest) {
		const TIntegral result = std::lcm(first, second);
		if constexpr (sizeof...(rest) > 0) {
			return Lcm(result, rest...);
		}

		return result;
	}

	template<std::integral... Rest>
	static auto LcmWithLambda(Rest... rest) {
		auto lcmFn = [&, rest...] {
			return Lcm(rest...);
			};
		auto res = lcmFn();
		return res;
	}

public:
	static void LookAtTemplateExpansion() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::cout << "result1=" << Lcm(1, 2, 3, 4) << std::endl;
		std::cout << "result2=" << Lcm(11, 13) << std::endl;
		std::cout << std::endl;
	}

	static void LookAtLambdaExpansion() {
		LookAtTemplateExpansion();

		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		std::cout << "result from calling lambda=" << LcmWithLambda(1, 2, 3, 4) << std::endl << std::endl;
	}
};

#pragma region Chapter19_Section3
template<typename T, std::size_t N>
struct SizedThing
{
	T data[N];

	const std::size_t Count() {
		return N; // sizeof(data) / sizeof(*data);
	}
};

struct PreAllocation {
	const bool HasNumber{ false };
	const int Number{};
	
	constexpr PreAllocation() {};
	constexpr PreAllocation(const int& number) : HasNumber(true), Number(number) {};
};

template<typename T, PreAllocation maybe>
class AnotherSizedThing
{
public:
	std::vector<T> data{};
	AnotherSizedThing() {
		if constexpr((maybe.HasNumber)) {
			data.reserve(maybe.Number);
		}
	}
};

class Chapter19_3 {
public:
	static void LookAtNonTypeParameters() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		SizedThing<int, 5> myNumbers;
		std::cout << "Number of values in sized thing = " << myNumbers.Count() << std::endl;

		AnotherSizedThing<long, PreAllocation{} > maybeSomeValues;
		std::cout << "Capacity in non-preallocated other thing = " << maybeSomeValues.data.capacity() << std::endl;
		constexpr PreAllocation pa{ 10 };
		AnotherSizedThing<long, pa > someValues;
		std::cout << "Capacity in preallocated other thing = " << someValues.data.capacity() << std::endl;
	}
};
#pragma endregion Chapter19_Section3

#pragma region Chapter19_Section4
#ifdef __cpp_multidimensional_subscript
template <typename T, std::size_t MaxX, std::size_t MaxY>
struct MDContainer {
	T const & operator[](std::size_t x, std::size_t y) const {
		return data[y * MaxX + x];
	}
	T& operator[](std::size_t x, std::size_t y) {
		return data[y * MaxX + x];
	}

	std::array<T, MaxX * MaxY> data;
};

template <typename T, T NotFoundValue, std::size_t MaxX, std::size_t MaxY>
struct ContainerWithDefaults {
	T& operator[](std::size_t x, std::size_t y) {
		return data[x][y]; // map will create an entry
	}
	T operator[](std::size_t x, std::size_t y, int64_t z) const {
		auto xi = data.find(x);
		if (xi == data.end()) return NotFoundValue;
		auto yi = xi->second.find(y);
		if (yi == xi->second.end()) return NotFoundValue;
		return yi->second;
	}

	std::unordered_map<std::size_t,
		std::unordered_map<std::size_t, T>> data;
};
#endif

class Chapter19_4 {
public:
	static void LookAtMultidimensional() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_multidimensional_subscript
		MDContainer<int, 10, 20> data;
		// would give an out of bounds exception
		// data[30, 30] = -1;
		data[3, 7] = 42;
		std::cout << "value @ [3,7] = " << data[3, 7] << std::endl;

		const char NotFound = '_';
		ContainerWithDefaults<char, NotFound, 10, 20> cdata;
		cdata[3, 7] = 'S';
		auto res = cdata[9, 9];
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};
#pragma endregion Chapter19_Section4

#pragma region Chapter19_Section5
struct SomeValue {
	int x;
};

class Chapter19_5 {
public:
	static void LookAtMakeShared() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		auto arrMS = std::make_shared<int[100]>();
		arrMS[37] = 42;
		std::cout << "value1[37] = " << arrMS[37] << std::endl;
		std::cout << "value1[99] = " << arrMS[99] << std::endl;

		auto arrMS2 = std::make_shared<SomeValue[100]>();
		arrMS2[37].x = 42;
		std::cout << "value2[37] = " << arrMS2[37].x << std::endl;

		auto arrMS3 = std::make_shared<int[]>(100);
		arrMS3[42] = 99;
		std::cout << "value3[42] = " << arrMS3[42] << std::endl;

		auto arrMU = std::make_unique<SomeValue[]>(100);
		arrMU[37].x = 42;
		// does not compile
		// auto arrMU2 = std::make_unique<SomeValue[100]>();
	}
};
#pragma endregion Chapter19_Section5

#pragma region Chapter19_Section6
template <typename T1, typename T2>
struct MyPair {
	T1 first{};
	T2 second{};

	auto operator<=>(const MyPair&) const = default;
};
// deduction guide was needed in C++17, but no longer
//template <typename T1, typename T2>
//MyPair(T1,T2) -> MyPair<T1, T2>;

class  Chapter19_6 {
public:
	static void LookAtCTAD() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		{
			std::pair<int, float> pr1{ 1, 2.3f };
			std::pair pr2{ 1, 2.3f };
			if (pr1 == pr2) {
				std::cout << "pair1 {" << pr1.first << "," << pr1.second << "} =="
					<< " pair2 {" << pr2.first << "," << pr2.second << "}\n";
			}
			else {
				std::cout << "pair1 {" << pr1.first << "," << pr1.second << "} !="
					<< " pair2 {" << pr2.first << "," << pr2.second << "}\n";
			}
			std::cout << std::endl;
		}

		{
			MyPair<int, float> mpr1{ 1, 2.3f };
			MyPair mpr2{ 1, 2.3f };
			if (mpr1 == mpr2) {
				std::cout << "mypair1 {" << mpr1.first << "," << mpr1.second << "} =="
					<< " mypair2 {" << mpr2.first << "," << mpr2.second << "}\n";
			}
			else {
				std::cout << "mypair1 {" << mpr1.first << "," << mpr1.second << "} !="
					<< " mypair2 {" << mpr2.first << "," << mpr2.second << "}\n";
			}
		}
	}
};
#pragma endregion Chapter19_Section6

#pragma region Chapter19_Section7
#if (__cpp_explicit_this_parameter) || (_MSC_VER)
struct Base {
	auto func1(this const Base& self) {
		std::cout << "calling" << typeid(self).name() << "::func1" << std::endl;
	}

	template<typename Self>
	auto func2(this Self&& self) {
		std::cout << "calling" << typeid(self).name() << "::func2" << std::endl;
	}
};
struct Derived : Base {};

template <typename ContainerValueType, std::size_t MaxX, std::size_t MaxY>
struct Container2D {
	template<typename Self>
	auto& at(this Self&& self, std::size_t x, std::size_t y) {
		return std::forward<Self>(self).data.at(y * MaxX + x);
	}

	std::array<ContainerValueType, MaxX* MaxY> data;
};

struct LessThanFn { // passing this by value
	template<typename T1, typename T2>
	bool operator()(this LessThanFn, const T1& lhs, const T2& rhs) {
		return lhs < rhs;
	}
};
#endif

class Chapter19_7 {
public:
	static void LookAtDeducingSelf()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if (__cpp_explicit_this_parameter) || (_MSC_VER)
		{
			Base b1{};
			b1.func1();
			b1.func2();
			Derived d1{};
			d1.func1();
			d1.func2();
		}

		{
			Container2D<int, 5, 5> data;
			data.at(2, 3) = 15;
			std::cout << "retrieved value =" << data.at(2, 3) << std::endl << std::endl;
		}

		{
			std::cout << "4 < 5 = " << std::boolalpha << LessThanFn()(4, 5) << std::endl;
		}
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};
#pragma endregion Chapter19_Section7

class Chapter19_8 {
public:
	static void SampleFn(int n) {
		std::cout << typeid(n).name() << " value=" << n << std::endl;
	}
	static void LookAtAuto() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		double d{ 1.2 };

		// SampleFn(d); // compiles, but gives warning
		SampleFn(int(d)); // create new integer
		SampleFn((int)d); // C-style cast
#ifndef _MSC_VER
		SampleFn(auto(d));
		SampleFn(auto{ d });
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

class Chapter19_9 {
public:
	static void LookAt_Char8() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_char8_t
		char8_t c8 = 255;
		const char8_t* u8str = u8"Hello C++23!";
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
		const char16_t* u16str = u"Hello C++23!";
		const char32_t* u32str = U"Hello C++23!";
		const wchar_t* widestr = L"Hello C++23!";

		std::u8string u8str2{ u8str };
	}
};

class Chapter19_10 {
public:
	static void LookAt_sizet() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_size_t_suffix
		auto szUnsigned = 20uz; // or UZ, or Uz, or uZ, or ...
		auto szSigned = 20z; // or Z
		static_assert(std::is_same_v<decltype(szUnsigned), std::size_t>);
		static_assert(std::is_same_v<decltype(szSigned), long>);
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

class Chapter19_11 {
public:
	static void LookAtNamedEscapes() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if __cpp_named_character_escapes >= 202207L	
		std::cout << "\N{OHM SIGN},\N{LATIN CAPITAL LETTER A},"
			<< "\N{LATIN CAPITAL LETTER A WITH MACRON}" << std::endl;
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

#pragma region Chapter19_Section12
struct S {
	S(const S&) = delete;
	S(S&&) = delete;
	S() = default;
};
struct EasyS {
	EasyS() {}
	EasyS(int x) : X{ x } {}
	int X{};
};
class Chapter19_12_1 {
private:
	static void PrintMessage(std::string part1,
		std::optional<std::string> part2 = {}, std::string part3 = "!") {
		std::cout << part1 << " " << part2.value_or("Awesome") << " " << part3 << std::endl;
	}

public:
	static void LookAtOptional_Recap() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		{
			std::optional<S> o;

			// compiler error
			// o = S{}; // cannot do assignment

			// can create a default new S inside of optional, since cannot move or copy
			o.emplace();

			auto es2 = EasyS{};
			auto o2 = std::make_optional(es2);
			auto o3 = std::make_optional<EasyS>(std::move(es2));
			std::optional<EasyS> es3 = std::make_optional<EasyS>(42);
			std::optional<EasyS> es4{ std::in_place, 37 };
			std::cout << "es3=" << es3.value().X << ", es4=" << (*es4).X << std::endl << std::endl;
		}
		{
			PrintMessage("Hello", "C++", "23");
			PrintMessage("Hello", "C++23");
			PrintMessage("Hello");
			PrintMessage("Hello", {}, "C++23");
		}
		std::cout << std::endl;
	}
};

enum class Ingredient {
	Dough,
	Pasta,
	Lettuce,
	Tomato,
	Onion,
	Cheese,
	Sausage,
	Sauce,
	Garlic,
	Mushroom,
};
struct Dinner { std::string name; };

class DinnerMaker {
public:
	DinnerMaker(const std::vector<Ingredient>& ingredients) :
		MyIngredients(ingredients) {
	}

	std::optional<Dinner> MakePizza() {
		using enum Ingredient;
		std::optional<Dinner> result;
		if (std::ranges::contains(MyIngredients, Dough) &&
			std::ranges::contains(MyIngredients, Sauce) &&
			std::ranges::contains(MyIngredients, Cheese)) {
			result = Dinner{ "Pizza" };
			AddOtherIngredients(result);
		}
		else {
			result = std::nullopt;
		}
		return result;
	};
	std::optional<Dinner> MakePasta() {
		using enum Ingredient;
		std::optional<Dinner> result;
		if (std::ranges::contains(MyIngredients, Pasta) &&
			std::ranges::contains(MyIngredients, Sauce)) {

			result = Dinner{ "Pasta" };
			AddOtherIngredients(result);
		}
		else {
			result = std::nullopt;
		}
		return result;
	};
	std::optional<Dinner> MakeSalad() {
		using enum Ingredient;
		std::optional<Dinner> result;
		if (std::ranges::contains(MyIngredients, Lettuce)) {
			result = Dinner{ "Salad" };
			AddOtherIngredients(result);
		}
		else {
			result = std::nullopt;
		}
		return result;
	};
	Dinner OrderDinner() { return Dinner{ "takeout" }; };

	Dinner MakeSomething() {
		std::optional<Dinner> dinnerInProgress = MakePizza();
		if (dinnerInProgress.has_value() == false) {
			dinnerInProgress = MakePasta();
		}
		if (dinnerInProgress.has_value() == false) {
			dinnerInProgress = MakeSalad();
		}
		return dinnerInProgress ? dinnerInProgress.value() : OrderDinner();
	}
	Dinner AnotherWayToMakeDinner() {
		return MakePizza().value_or(MakePasta().value_or(MakeSalad().value_or(OrderDinner())));
	}

private:
	const std::vector<Ingredient> MyIngredients;

	void AddOtherIngredients(std::optional<Dinner>& odinner) {
		Dinner& dinner = odinner.value();
		std::string toppings;
		using enum Ingredient;
		for (auto i : MyIngredients) {
			switch (i) {
			case Dough:
			case Pasta:
			case Lettuce:
				break;
			case Tomato: toppings += "tomato, "; break;
			case Onion: toppings += "onion, "; break;
			case Cheese: toppings += "cheese, "; break;
			case Sausage: toppings += "sausage, "; break;
			case Sauce: toppings += "sauce, "; break;
			case Garlic: toppings += "garlic, "; break;
			case Mushroom: toppings += "mushroom, "; break;
			}
		}
		dinner.name += (toppings.empty() ? " : plain" : ", with: " + toppings);
	}
};

class Chapter19_12_2 {
public:
	static void LookAtOptional() {
		Chapter19_12_1::LookAtOptional_Recap();
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

#ifdef __cpp_lib_optional
		std::map<std::string, DinnerMaker> dinners{
			{ "1.tonight", DinnerMaker({Ingredient::Lettuce,
			Ingredient::Mushroom, Ingredient::Tomato }) },
			{ "2.tomorrow", DinnerMaker({Ingredient::Dough, Ingredient::Cheese,
			Ingredient::Mushroom, Ingredient::Tomato, Ingredient::Sauce }) },
			{ "3.Friday", DinnerMaker({Ingredient::Pasta, Ingredient::Sauce,
			Ingredient::Mushroom, Ingredient::Tomato }) },
			{ "4.Saturday", DinnerMaker({Ingredient::Sauce,
			Ingredient::Mushroom, Ingredient::Tomato }) },
		};
		for (std::pair<std::string, DinnerMaker> dinnerPair : dinners) {
			auto d1 = dinnerPair.second.MakePizza();
			std::cout << "From trying to make pizza " << dinnerPair.first << " we have : "
				<< (d1.has_value() ? d1.value().name : "nothing") << std::endl;
			auto d2 = dinnerPair.second.MakePasta();
			std::cout << "From trying to make pasta " << dinnerPair.first << " we have: "
				<< (d2 ? d2.value().name : "nothing") << std::endl;
			auto d3 = dinnerPair.second.MakeSalad();
			std::cout << "From trying to make pasta " << dinnerPair.first << " we have: "
				<< (d3 ? (*d3).name : "nothing") << std::endl;
			auto d4 = dinnerPair.second.MakeSomething();
			std::cout << "From trying to make something " << dinnerPair.first << " we have: " << d4.name << std::endl;
			std::cout << std::endl;
		}
		std::cout << std::endl;
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};
#pragma endregion Chapter19_Section12

#pragma region Chapter19_Section13
class Chapter19_13 {
private:
	inline static const std::string BigProblem = "Kitchen is in ashes";

#ifdef __cpp_lib_expected
	static std::expected<Dinner, std::string> MakeDinner() {
		static std::vector<std::string> DinnerOutcomes{
			"", "Missing Ingredient", "Appliance Not Working", "Burnt", BigProblem,
		};
		std::ranges::rotate(DinnerOutcomes, DinnerOutcomes.begin() + 1);

		std::string currentOutcome = *(DinnerOutcomes.begin());
		if (currentOutcome.length() == 0) {
			return Dinner{ "Something delicious" };
		}
		else
		{
			return std::unexpected(currentOutcome);
		}
	}
#endif

public:
	static void LookAtExpected() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifdef __cpp_lib_expected
		for (int i = 0; i < 7; i++) {
			auto dinner = MakeDinner();
			if (dinner.has_value()) {
				std::cout << "Tonight we are eating " << dinner.value().name << std::endl;
			}
			else if (dinner.error() == Chapter19_13::BigProblem) {
				std::cout << "We will not be cooking anything for a while because: " << dinner.error() << std::endl;
			}
			else {
				std::cout << "Dinner will be delayed because: " << dinner.error() << std::endl;
			}
		}
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};
#pragma endregion Chapter19_Section13

#pragma region Chapter19_Section14
#define ThisIsDefined 123

class Chapter19_14 {
public:
	static void LookAtElifdef() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#ifndef ThisIsDefined
		std::cout << "Did not expect to be here!" << std::endl;
#elifdef DefinitelyNotDefined
			std::cout << "Should not have this defined!" << std::endl;
#elifdef AlsoDefinitelyNotDefined
			std::cout << "Should not have this defined either!" << std::endl;
#else
		std::cout << "Expected to be here!" << std::endl;
#endif

#ifdef DefinitelyNotDefined
		std::cout << "Should not have this defined!" << std::endl;
#elifdef AlsoDefinitelyNotDefined
			std::cout << "Should not have this defined either!" << std::endl;
#elifndef ThisIsDefined
std::cout << "Expected to be here!" << std::endl;
#else
		std::cout << "Did not expect to be here!" << std::endl;
#endif
	}
};
#pragma endregion Chapter19_Section14

class Chapter19_15 {
public:
	static void LookAtInvokeR() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		auto PrintSomething = [](auto x) -> void { std::cout << x << std::endl; };
		auto Doubler = [](int x) { return x * 2; };
		auto result = std::invoke_r<double>(Doubler, 42);
		static_assert(std::is_same<decltype(result), double>());
		std::cout << "Value of " << typeid(result).name() << " type = " << result << std::endl;
		std::invoke_r<void>(PrintSomething, 42);
	}
};

class Chapter19_16 {
public:
	static void LookAtSpanStream() {
		std::cout << std::endl;
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		{
			char input[] = "37 42 67";
			std::ispanstream is{ std::span<char>{input} };
			int n1, n2, n3;
			is >> n1;
			assert(n1 == 37);
			is >> n2;
			assert(n2 == 42);
			is >> n3;
			assert(n3 == 67);
			std::cout << "From" << std::quoted(input)
				<< ", n1=" << n1 << ", n2=" << n2 << ", n3=" << n3 << std::endl << std::endl;
		}
		{
			char output[20]{};
			std::ospanstream os{ std::span<char>{output} };
			int n1{ 37 }, n2{ 42 }, n3{ 67 };
			os << n1 << n2 << n3;
			auto const sp = os.span();
			assert(sp.size() == 6);
			assert(std::string(sp.data(), sp.size()) == "374267");
			auto x1 = sp.data();
			auto x2 = static_cast<void*>(output);
			assert(x1 == x1);
			assert(std::string(output) == "374267");
			std::cout << "From n1=" << n1 << ", n2=" << n2 << ", n3=" << n3
				<< ", we have output of: " << std::quoted(output) << std::endl << std::endl;
		}
	}
};

#pragma region Chapter19_Section17
struct BitField
{
		unsigned int bits4 : 4;
		unsigned int : 4; // blocked against usage
		unsigned char bits3 : 3 {2};
		unsigned char : 0; // force to start a new byte 
		unsigned int bits16 : 16 = 7;
};

class Chapter19_17 {
public:
	static void LookAtBitInitialization() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		for (unsigned int i = 2; i <= 256; i *= 2) {
			BitField b1{ i - 2 };
			std::cout << "val=" << int(b1.bits4) << ", bits=" << std::bitset<8>(b1.bits4) << std::endl;
			b1.bits4++;
			std::cout << "val=" << int(b1.bits4) << ", bits=" << std::bitset<8>(b1.bits4) << std::endl;
		}
	}
};
#pragma endregion Chapter19_Section17

class Chapter19_18 {
public:
	static void LookingAtUsingAlias() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		const int numbers[]{ 1,2,3,4,5 };

		// old way of defining a type
		for (typedef int T; T n : numbers) {
		}

		// range-based for loop from C++11
		for (int n : numbers) {
		}

#if __cpp_alias_templates >= 200704L
		using Num = int;
		for (Num n : numbers) {
		}
#else
		std::cout << "Feature not yet implemented for this compiler." << std::endl;
#endif
	}
};

void LookAtChapter19Topics()
{
	// works with compiler?					when tested		clang	gcc		msvc
	Chapter19_1::LookAtTemplateLambdas();	//2023.12.1		yes		yes		yes
	Chapter19_2::LookAtLambdaExpansion();	//2023.12.1		yes		yes		yes
	Chapter19_3::LookAtNonTypeParameters();	//2023.12.1		yes		yes		yes
	Chapter19_4::LookAtMultidimensional();	//2023.12.1		yes		yes		no
	Chapter19_5::LookAtMakeShared();		//2023.12.1		yes		yes		yes
	Chapter19_6::LookAtCTAD();				//2023.12.1		yes		yes		yes
	Chapter19_7::LookAtDeducingSelf();		//2023.12.1		no		no		no
	Chapter19_8::LookAtAuto();				//2023.12.1		yes		yes		no
	Chapter19_9::LookAt_Char8();			//2023.12.1		yes		yes		yes
	Chapter19_10::LookAt_sizet();			//2023.12.1		yes		yes		no
	Chapter19_11::LookAtNamedEscapes();		//2023.12.1		yes		yes		no
	Chapter19_12_2::LookAtOptional();		//2023.12.1		yes		yes		yes
	Chapter19_13::LookAtExpected();			//2023.12.1		no		yes		yes
	Chapter19_14::LookAtElifdef();			//2023.12.1		part	part	no
	Chapter19_15::LookAtInvokeR();			//2023.12.1		yes		yes		yes
	Chapter19_16::LookAtSpanStream();		//2023.12.1		yes		yes		yes
	Chapter19_17::LookAtBitInitialization();//2023.12.1		yes		yes		yes
	Chapter19_18::LookingAtUsingAlias();	//2023.12.1		yes		yes		yes
}
