#include <iostream>
#include <concepts>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#pragma region Chapter5_Section1
class Restaurant {
public:
	Restaurant() = delete;

	// opening a new restaurant
	Restaurant(const char* name)
	{
		std::cout << "Creating restaurant with arg\n";
		ChangeName(name);
	}

	void ChangeName(const char* name) {
		ClearName();

		_NameSize = strlen(name) + 1;
		_Name = new char[_NameSize];
#ifdef _MSC_VER
		strcpy_s(_Name, _NameSize, name);
#else
		strncpy(_Name, name, _NameSize);
		_Name[_NameSize] = '\0';
#endif
	}

	// creating another chain restaurant
	Restaurant(const Restaurant& other) {
		std::cout << "Creating restaurant via copy\n";
		_NameSize = other._NameSize;
		_Name = new char[_NameSize];
#ifdef _MSC_VER
		strcpy_s(_Name, _NameSize, other._Name);
#else
		strncpy(_Name, other._Name, _NameSize);
		_Name[_NameSize] = '\0';
#endif
	}

	// changing ownership via move ctor
	Restaurant(Restaurant&& other) noexcept {
		std::cout << "Creating restaurant via move\n";
		_NameSize = other._NameSize;
		_Name = other._Name;
		other.ClearName();
	}

	// changing ownership via move assignment
	Restaurant& operator=(Restaurant&& other) noexcept {
		if (this == &other) {
			std::cout << "assignment op, but for same entity, no-op\n";
		}
		else {
			std::cout << "assignment op for restaurant via move\n";
			this->ClearName(true);
			_NameSize = other._NameSize;
			_Name = other._Name;
			other.ClearName();
		}
		return *this;
	}

	~Restaurant() {
		if (_Name != nullptr) {
			std::cout << "Destroying restaurant w delete\n";
			ClearName(true);
		}
		else {
			std::cout << "Destroying restaurant with no name\n";
		}
	}
private:
	char* _Name;
	uint32_t _NameSize;

	void ClearName(bool freeStorage = false) {
		if (freeStorage) {
			delete[] _Name;
		}
		_NameSize = 0;
		_Name = nullptr;
	}
};

class RestaurantOwner {
public:
	RestaurantOwner(const Restaurant& other) : _restaurant(other) {
	}

	// move ctor
	RestaurantOwner(Restaurant&& other) :
		// _restaurant(other)  // would still copy
		// _restaurant((Restaurant&&)other) // works but messy cast
		_restaurant(std::move(other)) {
	}
private:
	Restaurant _restaurant;
};

class Chapter5_1 {
public:
	static void ReviewRules() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::movable<Restaurant>);
		RestaurantOwner owner("Name of my restaurant");

		Restaurant place = "Hello World";
		// Restaurant dest = place; // but will copy
		// Restaurant dest = (Restaurant&&)place; // works with move ctr, but messy
		// Restaurant dest((Restaurant&&)place); // works with move ctr, but messy also
		Restaurant dest(std::move(place));
		Restaurant anotherPlace = "Hello Galaxy";
		// Restaurant dest2  = std::move(place);
		// even though using assignment operator, it knows it is the ctor and will call it
		Restaurant dest2 = std::move(anotherPlace);
		dest2 = std::move(dest2);
	}
};
#pragma endregion Chapter5_Section1

class Chapter5_2 {
public:

	class Coffee {
	public:
		Coffee() = delete;
		Coffee(std::string name) {}

		// if no copy-ctor, then failures Problem1, Problem2, Problem5
		// RichCoffee(const RichCoffee& other) = delete;
		Coffee(const Coffee& other) {}
		//RichCoffee(const RichCoffee& other) = default;

		// if no copy=, then failures Problem2, Problem3, Problem4, Problem5
		//RichCoffee& operator=(RichCoffee& other) noexcept = delete;
		//RichCoffee& operator=(RichCoffee& other) noexcept {}
		Coffee& operator=(Coffee& other) noexcept = default;

		// if no copy =const, then failures Problem2, Problem4, Problem5
		//RichCoffee& operator=(const RichCoffee& other) noexcept = delete;
		//RichCoffee& operator=(const RichCoffee& other) noexcept {}
		Coffee& operator=(const Coffee& other) noexcept = default;

		// if no move ctor, then failures Problem1, Problem2, Problem5
		//RichCoffee(RichCoffee&& other) noexcept = delete;
		//RichCoffee(RichCoffee&& other) noexcept {}
		Coffee(Coffee&& other) noexcept = default;

		// if no move =, then failures Problem1, Problem2, Problem3, Problem4, Problem5
		//RichCoffee& operator=(RichCoffee&& other) noexcept = delete;
		//RichCoffee& operator=(RichCoffee&& other) noexcept {}
		Coffee& operator=(Coffee&& other) noexcept = default;
	};

	static void GetSomeCoffees() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::copy_constructible<Coffee>, "Problem1.copy_constructible");
		static_assert(std::movable<Coffee>, "Problem2.movable");
		static_assert(std::assignable_from<Coffee&, Coffee&>, "Problem3.assignable_from");
		static_assert(std::assignable_from<Coffee&, const Coffee&>, "Problem4.assignable_from const");
		static_assert(std::copyable<Coffee>, "Problem5.copyable");
	}
};

class Chapter5_3_1 {
public:
	class EnrichedCoffee : public Chapter5_2::Coffee {
	public:
		EnrichedCoffee() = default;
		~EnrichedCoffee() = default;
		EnrichedCoffee(const EnrichedCoffee& other) = default;
		EnrichedCoffee& operator=(EnrichedCoffee& other) noexcept = default;
		EnrichedCoffee& operator=(const EnrichedCoffee& other) noexcept = default;
		EnrichedCoffee(EnrichedCoffee&& other) noexcept = default;
		EnrichedCoffee& operator=(EnrichedCoffee&& other) noexcept = default;
	};

	static void GetSomeCoffees() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		// compiler error, although we knew regular Coffee would not work
		// static_assert(std::semiregular<Coffee>);
		static_assert(std::copyable<EnrichedCoffee>);

		// compiler error, due to no default constructor for Coffee
		// static_assert(std::semiregular<EnrichedCoffee>);
	}
};

class Chapter5_3_2 {
public:
	class EnrichedCoffee : public Chapter5_2::Coffee {
	public:
		EnrichedCoffee() : Coffee("delicious") {}
		~EnrichedCoffee() = default;
		EnrichedCoffee(const EnrichedCoffee& other) = default;
		EnrichedCoffee& operator=(EnrichedCoffee& other) noexcept = default;
		EnrichedCoffee& operator=(const EnrichedCoffee& other) noexcept = default;
		EnrichedCoffee(EnrichedCoffee&& other) noexcept = default;
		EnrichedCoffee& operator=(EnrichedCoffee&& other) noexcept = default;
	};

	static void GetSomeCoffees() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		// compiler error, although we knew regular Coffee would not work
		// static_assert(std::semiregular<Coffee>);
		static_assert(std::copyable<EnrichedCoffee>);
		static_assert(std::semiregular<EnrichedCoffee>);
	}
};

class Chapter5_4 {
public:

	class BavarianRoastedCoffee : public Chapter5_3_2::EnrichedCoffee {
	public:
		BavarianRoastedCoffee() = default;
		~BavarianRoastedCoffee() = default;
		BavarianRoastedCoffee(const BavarianRoastedCoffee& other) = default;
		BavarianRoastedCoffee& operator=(BavarianRoastedCoffee& other) noexcept = default;
		BavarianRoastedCoffee& operator=(const BavarianRoastedCoffee& other) noexcept = default;
		BavarianRoastedCoffee(BavarianRoastedCoffee&& other) noexcept = default;
		BavarianRoastedCoffee& operator=(BavarianRoastedCoffee&& other) noexcept = default;
		bool operator==(const BavarianRoastedCoffee& other) const { return true; }
	};

	static void GetSomeCoffees() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		static_assert(std::copy_constructible<Chapter5_2::Coffee>, "Problem1.copy_constructible");
		static_assert(std::movable<Chapter5_2::Coffee>, "Problem2.movable");
		static_assert(std::assignable_from<Chapter5_2::Coffee&, Chapter5_2::Coffee&>, "Problem3.assignable_from");
		static_assert(std::assignable_from<Chapter5_2::Coffee&, const Chapter5_2::Coffee&>, "Problem4.assignable_from const");
		static_assert(std::copyable<Chapter5_2::Coffee>, "Problem5.copyable");

		// compiler error, although we knew regular Coffee would not work
		// static_assert(std::semiregular<Coffee>);
		static_assert(std::copyable<Chapter5_3_2::EnrichedCoffee>);
		static_assert(std::semiregular<Chapter5_3_2::EnrichedCoffee>);

		static_assert(std::semiregular<BavarianRoastedCoffee>);
		static_assert(std::regular<BavarianRoastedCoffee>);
		static_assert(std::equality_comparable<BavarianRoastedCoffee>);
	}
};

void LookAtChapter5Topics() {
	// works with compiler?				when tested		clang	msvc	gcc
	Chapter5_1::ReviewRules();		//  2023.12.09		yes		yes		yes
	Chapter5_2::GetSomeCoffees();	//  2023.12.09		yes		yes		yes
	Chapter5_3_1::GetSomeCoffees();	//  2023.12.09		yes		yes		yes
	Chapter5_3_2::GetSomeCoffees();	//  2023.12.09		yes		yes		yes
	Chapter5_4::GetSomeCoffees();	//  2023.12.09		yes		yes		yes
}
