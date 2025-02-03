#include <iostream>
#include <concepts>
#include <vector>
#include <algorithm>
#include <array>
#include <compare>
#include <string>

#pragma region Chapter3_Section1
class Rice
{
public:
	bool PrettySmall;

	bool operator==(const Rice& other) const { return PrettySmall == other.PrettySmall; }
};

class BasmatiRice : Rice
{
public:
	bool PrettySmall;
	BasmatiRice() { PrettySmall = true; }
};

class LongGrainRice : public Rice
{
public:
	LongGrainRice() { PrettySmall = false; }
};

class OrzoPasta
{
public:
	bool PrettySmall;
	OrzoPasta() { PrettySmall = true; }
	bool operator==(const Rice& other) const { return true; }
};

class AnotherTypeOfRice
{
public:
	bool PrettySmall;
	AnotherTypeOfRice() { PrettySmall = true; }
	bool operator==(const AnotherTypeOfRice& other) const { return true; }
};

class Chapter3_1 {
private:
	static void CookTheRice(std::equality_comparable auto food)
	{
		// ...
	}

public:
	static void TasteTheRice()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		Rice r;
		BasmatiRice br;
		LongGrainRice lgr;
		AnotherTypeOfRice ator;
		OrzoPasta op;

		CookTheRice(r);

		// does not compile, since it does not meet constraint
		// does not publicly derive from rice, so equality operator not visible
		// CookTheRice(br);

		CookTheRice(lgr);

		// does not compile, since it does not meet constraint
		// does have a public comparer function, but is comparing itself to Rice, not itself.
		// CookTheRice(op);

		CookTheRice(ator);

		//static_assert(std::equality_comparable_with< BoxOfRice, BagOfRice>);
		static_assert(std::equality_comparable_with<std::string::iterator, std::string::const_iterator>);
	}
};
#pragma endregion Chapter3_Section1

#pragma region Chapter3_Section3
class Chapter3_3Food {
public:
	class Pasta {
	public:
		int width;
		std::string name;

		Pasta(const char* nameGiven, int widthInMillimetres) : name(nameGiven), width(widthInMillimetres)
		{
		}

		int GetWidth() const { return width; }
		std::string GetName() const { return name; }

		void ShowInfo() const {
			std::cout << this->GetName() << " is " << this->GetWidth() << "mm wide\n";
		}
	};

	class Lasagna : public Chapter3_3Food::Pasta {
	public:
		Lasagna() : Chapter3_3Food::Pasta("Lucious lasagna", 70) {}
	};

	class Linguine : public Chapter3_3Food::Pasta {
	public:
		Linguine() : Chapter3_3Food::Pasta("Tasty linguine", 4) {}
	};

	class Spaghetti : public Chapter3_3Food::Pasta {
	public:
		Spaghetti() : Chapter3_3Food::Pasta("Succulent spaghetti", 2) { }
	};
};

bool operator == (const Chapter3_3Food::Pasta& lhs, const Chapter3_3Food::Pasta& rhs)
{
	return lhs.GetWidth() == rhs.GetWidth();
}
bool operator <  (const Chapter3_3Food::Pasta& lhs, const Chapter3_3Food::Pasta& rhs)
{
	return lhs.GetWidth() < rhs.GetWidth();
}
bool operator <= (const Chapter3_3Food::Pasta& lhs, const Chapter3_3Food::Pasta& rhs)
{
	return lhs.GetWidth() <= rhs.GetWidth();
}
bool operator >  (const Chapter3_3Food::Pasta& lhs, const Chapter3_3Food::Pasta& rhs)
{
	return lhs.GetWidth() > rhs.GetWidth();
}
bool operator >= (const Chapter3_3Food::Pasta& lhs, const Chapter3_3Food::Pasta& rhs)
{
	return lhs.GetWidth() >= rhs.GetWidth();
}

class Chapter3_3 {
public:
	static void TasteThePasta() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::equality_comparable<Chapter3_3Food::Pasta>);
		static_assert(std::totally_ordered<Chapter3_3Food::Pasta>);

		constexpr size_t pastaCount = 3;
		std::array<Chapter3_3Food::Pasta, pastaCount> pastas
		{ Chapter3_3Food::Linguine{}, Chapter3_3Food::Lasagna{}, Chapter3_3Food::Spaghetti{} };
		std::sort(pastas.begin(), pastas.end());
		for (const auto& p : pastas) {
			p.ShowInfo();
		}
		std::cout << "\n";
	}
};
#pragma endregion Chapter3_Section3

class Chapter3_5_1 {
public:
	static void CompareTemperatures() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		constexpr int warmOven = 200;
		constexpr int hotOven = 450;
		static_assert((warmOven <=> hotOven) < 0);
	}
};

class Chapter3_5_2 {
public:
	static void CompareTemperatures() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		constexpr int warmOven = 200;
		constexpr int hotOven = 450;
		static_assert((warmOven <=> hotOven) < 0);

		static_assert(std::is_lt(warmOven <=> hotOven));
		auto comparisonResult = (warmOven <=> hotOven);
		if (std::is_eq(comparisonResult)) {
			std::cout << "values are equal\n";
		}
		//
		if (std::is_neq(comparisonResult)) {
			std::cout << "values are not equal\n";
		}
		//
		if (std::is_lt(comparisonResult)) {
			std::cout << "first value is less than the second\n";
		}
		//
		if (std::is_lteq(comparisonResult)) {
			std::cout << "first value is less than or equal to the second\n";
		}
		//
		if (std::is_gt(comparisonResult)) {
			std::cout << "first value is greater than the second\n";
		}
		//
		if (std::is_gteq(comparisonResult)) {
			std::cout << "first value is greater  than or equal to the second\n";
		}
	}
};

class Chapter3_6_1Food {
public:
	class Pasta {
	public:
		int width;
		std::string name;
		Pasta(const char* nameGiven, int widthInMillimetres) : name(nameGiven), width(widthInMillimetres)
		{
		}

		int GetWidth() const { return width; }
		std::string GetName() const { return name; }

		void ShowInfo() const {
			std::cout << this->GetName() << " is " << this->GetWidth() << "mm wide\n";
		}

		auto operator<=>(const Pasta& rhs) const {
			return this->GetWidth() <=> rhs.GetWidth();
		}
		bool operator == (const Pasta& rhs) const {
			return this->GetWidth() == rhs.GetWidth();
		}
	};

	class Lasagna : public Chapter3_6_1Food::Pasta {
	public:
		Lasagna() : Chapter3_6_1Food::Pasta("Lucious lasagna", 70) {}
	};

	class Linguine : public Chapter3_6_1Food::Pasta {
	public:
		Linguine() : Chapter3_6_1Food::Pasta("Tasty linguine", 4) {}
	};

	class Spaghetti : public Chapter3_6_1Food::Pasta {
	public:
		Spaghetti() : Chapter3_6_1Food::Pasta("Succulent spaghetti", 2) { }
	};
};

class Chapter3_6_1 {
public:
	static void TasteThePasta() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::equality_comparable<Chapter3_6_1Food::Pasta>);
		static_assert(std::totally_ordered<Chapter3_6_1Food::Pasta>);
		static_assert(std::three_way_comparable<Chapter3_6_1Food::Pasta>);

		constexpr size_t pastaCount = 3;
		std::array<Chapter3_6_1Food::Pasta, pastaCount> pastas
		{ Chapter3_6_1Food::Linguine{}, Chapter3_6_1Food::Lasagna{}, Chapter3_6_1Food::Spaghetti{} };
		std::sort(pastas.begin(), pastas.end());
		for (const auto& p : pastas) {
			p.ShowInfo();
		}
		std::cout << "\n";
	}
};

class Chapter3_6_2Food {
public:
	class Spaghetti : public Chapter3_6_1Food::Pasta {
	public:
		Spaghetti() : Chapter3_6_1Food::Pasta("Succulent spaghetti", 2) { }
		bool IsAlDente = false;
	};
};

class Chapter3_6_2 {
public:
	static void TasteThePasta() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::equality_comparable<Chapter3_6_1Food::Pasta>);
		static_assert(std::totally_ordered<Chapter3_6_1Food::Pasta>);

		const size_t pastaCount = 3;
		std::array<Chapter3_6_1Food::Pasta, pastaCount> pastas
		{ Chapter3_6_1Food::Linguine{}, Chapter3_6_1Food::Lasagna{}, Chapter3_6_2Food::Spaghetti{} };
		std::sort(pastas.begin(), pastas.end());
		for (const auto& p : pastas) {
			p.ShowInfo();
		}
		std::cout << "\n";

		Chapter3_6_2Food::Spaghetti cooked5minutes;
		cooked5minutes.IsAlDente = true;
		Chapter3_6_2Food::Spaghetti cooked8minutes;
		if (cooked5minutes == cooked8minutes) {
			std::cout << "spaghetti is the same\n";
		}
		else {
			std::cout << "spaghetti is NOT the same\n";
		}
		std::cout << "\n\n";
	}
};

class Chapter3_6_3Food {
public:
	class Spaghetti : public Chapter3_6_1Food::Pasta {
	public:
		Spaghetti() : Chapter3_6_1Food::Pasta("Succulent spaghetti", 2) { }
		bool IsAlDente = false;
		std::strong_ordering operator<=>(const Spaghetti& other) const {
			return this->IsAlDente <=> other.IsAlDente;
		}
		bool operator == (const Spaghetti& rhs) const {
			return this->IsAlDente == rhs.IsAlDente;
		}
	};
};

class Chapter3_6_3 {
public:
	static void TasteThePasta() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::equality_comparable<Chapter3_6_1Food::Pasta>);
		static_assert(std::totally_ordered<Chapter3_6_1Food::Pasta>);

		const size_t pastaCount = 3;
		std::array<Chapter3_6_1Food::Pasta, pastaCount> pastas
		{ Chapter3_6_1Food::Linguine{}, Chapter3_6_1Food::Lasagna{}, Chapter3_6_3Food::Spaghetti{} };
		std::sort(pastas.begin(), pastas.end());
		for (const auto& p : pastas) {
			p.ShowInfo();
		}
		std::cout << "\n";

		Chapter3_6_3Food::Spaghetti cooked5minutes;
		cooked5minutes.IsAlDente = true;
		Chapter3_6_3Food::Spaghetti cooked8minutes;
		if (cooked5minutes == cooked8minutes) {
			std::cout << "spaghetti is the same\n";
		}
		else {
			std::cout << "spaghetti is NOT the same\n";
		}
		std::cout << "\n\n";
	}
};

class Chapter3_6_4 {
public:
	class CookingInstructions
	{
	public:
		int Temperature;
		int Minutes;

		CookingInstructions(int temp, int time) : Temperature(temp), Minutes(time) { }
		std::strong_ordering operator<=>(const CookingInstructions& other) const = default;
	};

private:
	static void ShowCookingResult(std::string item1, std::strong_ordering result, std::string item2) {
		if (result == std::strong_ordering::less) {
			std::cout << item1 << " is less than " << item2 << "\n";
		}
		else if (result == std::strong_ordering::greater) {
			std::cout << item1 << " is more than " << item2 << "\n";
		}
		else if (result == std::strong_ordering::equivalent) {
			std::cout << item1 << " is the same as " << item2 << "\n";
		}
	}

public:
	static void CheckTheOven()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::equality_comparable<CookingInstructions>);
		static_assert(std::three_way_comparable<CookingInstructions>);
		static_assert(std::totally_ordered<CookingInstructions>);

		CookingInstructions howToCookChicken(250, 60);
		CookingInstructions howToCookGrilledCheese(450, 10);
		CookingInstructions howToCookChicken2(howToCookChicken.Temperature, howToCookChicken.Minutes);

		ShowCookingResult("chicken", howToCookChicken <=> howToCookGrilledCheese, "grilled cheese");
		ShowCookingResult("grilled cheese", howToCookGrilledCheese <=> howToCookChicken2, "chicken");
		ShowCookingResult("chicken", howToCookChicken <=> howToCookChicken2, "other chicken");
	}
};

class Chapter3_6_5 {
public:
	class CookingInstructions
	{
	public:
		int Minutes;	// oops, switched the property order
		int Temperature;

		CookingInstructions(int temp, int time) { Temperature = temp; Minutes = time; }
		std::strong_ordering operator<=>(const CookingInstructions& other) const = default;
	};

private:
	static void ShowCookingResult(std::string item1, std::strong_ordering result, std::string item2) {
		if (result == std::strong_ordering::less) {
			std::cout << item1 << " is less than " << item2 << "\n";
		}
		else if (result == std::strong_ordering::greater) {
			std::cout << item1 << " is more than " << item2 << "\n";
		}
		else if (result == std::strong_ordering::equivalent) {
			std::cout << item1 << " is the same as " << item2 << "\n";
		}
	}

public:
	static void CheckTheOven()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::equality_comparable<CookingInstructions>);
		static_assert(std::three_way_comparable<CookingInstructions>);
		static_assert(std::totally_ordered<CookingInstructions>);

		CookingInstructions howToCookChicken(250, 60);
		CookingInstructions howToCookGrilledCheese(450, 10);
		CookingInstructions howToCookChicken2(howToCookChicken.Temperature, howToCookChicken.Minutes);

		ShowCookingResult("chicken", howToCookChicken <=> howToCookGrilledCheese, "grilled cheese");
		ShowCookingResult("grilled cheese", howToCookGrilledCheese <=> howToCookChicken2, "chicken");
		ShowCookingResult("chicken", howToCookChicken <=> howToCookChicken2, "other chicken");
	}
};

class Chapter3_7 {
public:
	template <typename T, std::totally_ordered_with<T> U>
	static auto Three_way_fallback(const T& lhs, const U& rhs) {
		if constexpr (std::three_way_comparable_with<T, U>) {
			return lhs <=> rhs;
		}
		else {
			if (lhs == rhs) {
				return std::strong_ordering::equal;
			}
			else if (lhs < rhs) {
				return std::strong_ordering::less;
			}
			else {
				return std::strong_ordering::greater;
			}
		}
	}

	struct SomethingExternal {
		std::string value;
	};

	struct OurThing {
		SomethingExternal ExternalValue;
		int Id;

		std::strong_ordering operator<=>(const OurThing& other) const {
			if (std::strong_ordering cmp = Id <=> other.Id; cmp != 0) {
				return cmp;
			}
			return Three_way_fallback(ExternalValue.value, other.ExternalValue.value);
		}

		std::string ToString() {
			return std::to_string(Id) + "+" + ExternalValue.value;
		}
	};

	static void TryToCompare() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		OurThing ot1{ "xyz", 3 };
		OurThing ot2{ "abc", 3 };
		OurThing ot3{ "abc", 5 };

		auto result23 = ot2 <=> ot3;
		if (result23 == std::strong_ordering::equal) {
			std::cout << ot2.ToString() + "==" + ot3.ToString() << std::endl;
		}
		else if (result23 == std::strong_ordering::greater) {
			std::cout << ot2.ToString() + " > " + ot3.ToString() << std::endl;
		}
		else {
			std::cout << ot2.ToString() + " < " + ot3.ToString() << std::endl;
		}

		auto result12 = ot1 <=> ot2;
		if (result12 == std::strong_ordering::equal) {
			std::cout << ot1.ToString() + "==" + ot2.ToString() << std::endl;
		}
		else if (result12 == std::strong_ordering::greater) {
			std::cout << ot1.ToString() + " > " + ot2.ToString() << std::endl;
		}
		else {
			std::cout << ot1.ToString() + " < " + ot2.ToString() << std::endl;
		}
	}
};


void LookAtChapter3Topics() {
	// works with compiler?					when tested	clang	msvc	gcc
	Chapter3_1::TasteTheRice();			// 2023.12.07	yes		yes		yes
	Chapter3_3::TasteThePasta();		// 2023.12.07	yes		yes		yes	
	Chapter3_5_2::CompareTemperatures();// 2023.12.07	yes		yes		yes

	Chapter3_6_1::TasteThePasta();		// 2023.12.07	yes		yes		yes
	Chapter3_6_2::TasteThePasta();		// 2023.12.07	yes		yes		yes
	Chapter3_6_3::TasteThePasta();		// 2023.12.07	yes		yes		yes

	Chapter3_6_4::CheckTheOven();		// 2023.12.07	yes		yes		yes
	Chapter3_6_5::CheckTheOven();		// 2023.12.07	yes		yes		yes

	Chapter3_7::TryToCompare();			// 2023.12.07	yes		yes		yes
};
