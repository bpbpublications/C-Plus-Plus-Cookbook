#include <iostream>
#include <concepts>
#include <vector>
#include <array>
#include <typeinfo>
#include <tuple>
#include <type_traits>

#pragma region Chapter2_Section1
template <typename T>
concept HasRecipeWithRightIngredient = requires (T r) {
	{ r.HasTheRightIngredient() } -> std::same_as<int>;
};

class Recipe2A {
public:
	int HasTheRightIngredient() {}
};

class Recipe2B {
public:
	int HasTheWrongIngredient() {}
};

class Recipe2C {
public:
	int HasTheRightIngredient;
};

class Recipe2D {
public:
	bool HasTheRightIngredient() {}
};

class Recipe2E {
public:
	long HasTheRightIngredient() {}
};

class Recipe2F : Recipe2A { };

class Recipe2G : public Recipe2A { };

class Chapter2_1 {
private:
	static void PrintRecipeWithRightIngredient(std::string description, HasRecipeWithRightIngredient auto r) {
		std::cout << description << " has the right ingredient!\n";
	}

public:
	static void TestRecipesWithSameAs() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		// found the right ingredient
		PrintRecipeWithRightIngredient(typeid(Recipe2A).name(), Recipe2A{});

		// COMPILER ERROR: has the wrong ingredient
		//PrintRecipeWithRightIngredient(typeid(Recipe2B).name(), Recipe2B{});

		// COMPILER ERROR: has a member variable of that name, but not a function
		//PrintRecipeWithRightIngredient(typeid(Recipe2C).name(), Recipe2C{});

		// COMPILER ERROR: has the correct member function name, but not correct type
		//PrintRecipeWithRightIngredient(typeid(Recipe2D).name(), Recipe2D{});

		// COMPILER ERROR: has the correct member function name, but type doesn't match
		//PrintRecipeWithRightIngredient(typeid(Recipe2E).name(), Recipe2E{});

		// COMPILER ERROR: is derived from class with that function, but not accessible
		//PrintRecipeWithRightIngredient(typeid(Recipe2F).name(), Recipe2F{});

		// is derived from class with that function, and is accessible
		PrintRecipeWithRightIngredient(typeid(Recipe2G).name(), Recipe2G{});
	}
};
#pragma endregion Chapter2_Section1

#pragma region Chapter2_Section2
template <typename T>
concept HasRecipeWithAlmostRightIngredient = requires (T r) {
	{ r.HasTheRightIngredient() } -> std::convertible_to<long>;
};

class Chapter2_2 {
private:
	static void PrintRecipeWithAlmostRightIngredient(std::string description, HasRecipeWithAlmostRightIngredient auto r) {
		std::cout << description << " has the ingredient that is right, or close enough!\n";
	}

public:
	static void TestRecipesWithConvertibleTo() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		// found the right ingredient
		PrintRecipeWithAlmostRightIngredient(typeid(Recipe2A).name(), Recipe2A{});

		// COMPILER ERROR: has the wrong ingredient
		//PrintRecipeWithAlmostRightIngredient(typeid(Recipe2B).name(),Recipe2B{});

		// COMPILER ERROR: has a member variable of that name, but not a function
		//PrintRecipeWithAlmostRightIngredient(typeid(Recipe2C).name(),Recipe2C{});

		// COMPILER ERROR: has the correct member function name, but not correct type
		PrintRecipeWithAlmostRightIngredient(typeid(Recipe2D).name(), Recipe2D{});

		// COMPILER ERROR: has the correct member function name, but type doesn't match
		PrintRecipeWithAlmostRightIngredient(typeid(Recipe2E).name(), Recipe2E{});

		// COMPILER ERROR: is derived from class with that function, but not accessible
		//PrintRecipeWithAlmostRightIngredient(typeid(Recipe2F).name(),Recipe2F{});

		// is derived from class with that function, and is accessible
		PrintRecipeWithAlmostRightIngredient(typeid(Recipe2G).name(), Recipe2G{});
	}
};
#pragma endregion Chapter2_Section2

#pragma region Chapter2_Section3
class BaseSeafoodChowder {};

class CreamySeafoodChowder : public BaseSeafoodChowder {};

class TomatoSeafoodChowder : private BaseSeafoodChowder {};

struct OtherChowderBase {};
struct AnotherChowder : public OtherChowderBase {};

class Chapter2_3 {
private:
	static void CheckIfDerivedorBase(std::string type1Name, std::string type2Name,
		bool is1DerivedFrom2, bool is2DerivedFrom1, bool is1BasePf2, bool is2BaseOf1) {
		std::cout << type1Name << (is1DerivedFrom2 ? " IS " : " is not ")
			<< "derived from (or the same) as " << type2Name << "\n";
		std::cout << type2Name << (is2DerivedFrom1 ? " IS " : " is not ")
			<< "derived from (or the same) as " << type1Name << "\n";
		std::cout << type1Name << (is1BasePf2 ? " IS " : " is not ")
			<< "the base (or the same) as " << type2Name << "\n";
		std::cout << type2Name << (is2BaseOf1 ? " IS " : " is not ")
			<< "the base(or the same) as " << type1Name << "\n";
		std::cout << "\n";
	}

	static void TastingCreamyChowder()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		CheckIfDerivedorBase(typeid(CreamySeafoodChowder).name(), typeid(CreamySeafoodChowder).name(),
			std::derived_from<CreamySeafoodChowder, CreamySeafoodChowder>,
			std::derived_from<CreamySeafoodChowder, CreamySeafoodChowder>,
			std::is_base_of_v<CreamySeafoodChowder, CreamySeafoodChowder>,
			std::is_base_of_v<CreamySeafoodChowder, CreamySeafoodChowder>);

		CheckIfDerivedorBase(typeid(CreamySeafoodChowder).name(), typeid(BaseSeafoodChowder).name(),
			std::derived_from<CreamySeafoodChowder, BaseSeafoodChowder>,
			std::derived_from<BaseSeafoodChowder, CreamySeafoodChowder>,
			std::is_base_of_v<CreamySeafoodChowder, BaseSeafoodChowder>,
			std::is_base_of_v<BaseSeafoodChowder, CreamySeafoodChowder>);
	}

	static void TastingTomatoChowder() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		CheckIfDerivedorBase(typeid(TomatoSeafoodChowder).name(), typeid(BaseSeafoodChowder).name(),
			std::derived_from<TomatoSeafoodChowder, BaseSeafoodChowder>,
			std::derived_from<BaseSeafoodChowder, TomatoSeafoodChowder>,
			std::is_base_of_v<TomatoSeafoodChowder, BaseSeafoodChowder>,
			std::is_base_of_v<BaseSeafoodChowder, TomatoSeafoodChowder>);
	}

	static void TastingAnotherChowder() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		CheckIfDerivedorBase(typeid(AnotherChowder).name(), typeid(AnotherChowder).name(),
			std::derived_from<AnotherChowder, AnotherChowder>,
			std::derived_from<AnotherChowder, AnotherChowder>,
			std::is_base_of_v<AnotherChowder, AnotherChowder>,
			std::is_base_of_v<AnotherChowder, AnotherChowder>);

		CheckIfDerivedorBase(typeid(AnotherChowder).name(), typeid(OtherChowderBase).name(),
			std::derived_from<AnotherChowder, OtherChowderBase>,
			std::derived_from<OtherChowderBase, AnotherChowder>,
			std::is_base_of_v<AnotherChowder, OtherChowderBase>,
			std::is_base_of_v<OtherChowderBase, AnotherChowder>);
	}

	static void CheckingValueTypes() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		CheckIfDerivedorBase(typeid(int).name(), typeid(int).name(),
			std::derived_from<int, int>, std::derived_from<int, int>,
			std::is_base_of_v<int, int>, std::is_base_of_v<int, int>);


		CheckIfDerivedorBase(typeid(long).name(), typeid(int).name(),
			std::derived_from<long, int>, std::derived_from<int, long>,
			std::is_base_of_v<long, int>, std::is_base_of_v<int, long>);
	}
public:
	static void TryingSomeChowderThatIsDerivedFrom() {
		TastingCreamyChowder();
		TastingTomatoChowder();
		TastingAnotherChowder();
		CheckingValueTypes();
	}
};
#pragma endregion Chapter2_Section3

#pragma region Chapter2_Section4
template <typename T>
concept PageCount = std::integral<T>;

template <typename T>
concept PostivePageCount = std::unsigned_integral<T>;

class Chapter2_4 {
private:
	static void TryToPrintNumber(std::string typeName, PostivePageCount auto pg) {
		std::cout << typeName << " is integral\n";
	}

public:
	static void PrintNumbers() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		// does not compile
		//TryToPrintNumber("integer", 'A');

		TryToPrintNumber("integer", 1u);

		// does not compile
		//TryToPrintNumber("negative integer", -1);

		// does not compile
		//TryToPrintNumber("number with decimal", 12.3);
	}
};
#pragma endregion Chapter2_Section4

#pragma region Chapter2_Section5
template <typename T>
concept LitresOfWaterRequired = std::floating_point<T>;

class Chapter2_5 {
private:
	static void TryToPrintFloatingNumber(std::string typeName, LitresOfWaterRequired auto litres) {
		std::cout << typeName << " is floating point\n";
	}

public:
	static void PrintFloats() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		TryToPrintFloatingNumber("double", 1.23);
		TryToPrintFloatingNumber("float", 12.33f);
		TryToPrintFloatingNumber("long double", 1.23L);
		TryToPrintFloatingNumber("exponent", 1.23e4);
		TryToPrintFloatingNumber("number to decimal exponent", 0x3p3);

		// the ones below fail to compile
		//TryToPrintFloatingNumber("negative integer", -1);
		//TryToPrintFloatingNumber("char", 'a');
	}
};
class Chapter2_5_2 {
public:
	static void WorkWithNumber(std::string typeName, std::floating_point auto number) {
		// do some logic specific to integrals  
		std::cout << typeName << " is an floating point\n";
	}
	static void WorkWithNumber(std::string typeName, std::integral auto number) {
		// do some logic specific to floating point values
		std::cout << typeName << " is an integral\n";
	}
};

#pragma endregion Chapter2_Section5

#pragma region Chapter2_Section6
struct RightSide { };

struct LeftSide {
	RightSide rightValue;

	LeftSide(const RightSide& rs) { rightValue = rs; }
};

struct OtherSide { };

template <typename T>
concept AcceptableForLeftSideRightSide = std::assignable_from<LeftSide&, T>;

class Chapter2_6 {
private:
	static void TryToAssign(LeftSide& ls, AcceptableForLeftSideRightSide auto rs) {
		std::cout << typeid(ls).name() << " can be given a " << typeid(rs).name() << std::endl;
	}

public:
	static void AssignSomeSides() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		RightSide rs;
		LeftSide ls { rs };

		TryToAssign(ls, rs);

		OtherSide os {};
		// Compiler fails due to not assignable
		// TryToAssign("test", ls, os);
	}
};
#pragma endregion Chapter2_Section6

#pragma region Chapter2_Section7
#ifdef Just_Reusing_From_Previous_Section
// Reusing From PreviousSection
struct RightSide { };

struct LeftSide {
	RightSide rightValue;

	LeftSide(const RightSide& rs) { rightValue = rs; }
};

struct OtherSide { };
#endif

template <typename T>
concept AcceptableToSwapWithLeftSide = std::swappable_with<LeftSide&, T&>;

class Chapter2_7 {
private:
	static void PerformSwap(LeftSide& ls, AcceptableToSwapWithLeftSide auto& s) {
		std::cout << typeid(ls).name() << " can be swapped with a " << typeid(s).name() << std::endl;
		SwapSides(ls, s);
	}
	
public:
	static void SwapSomeSides() {
		RightSide rs;
		LeftSide ls{ rs };
		OtherSide os{};

		static_assert(std::swappable<int>);
		static_assert(std::swappable<RightSide>);
		static_assert(std::swappable<LeftSide>);
		static_assert(std::swappable<OtherSide>);

		// does not compile, because we cannot swap
		// PerformSwap(ls, rs);

		// does not compile, because we cannot swap, even though both empty
		// SwapSides(rs, os);
	}

	template <class T1, class T2> requires std::swappable_with<T1, T2>
	static void SwapSides(T1&& t1, T2&& t2) {
		auto holder = std::forward<T1>(t1);
		t1 = std::forward<T2>(t2);
		t2 = std::move(holder);
	}
};
#pragma endregion Chapter2_Section7

#pragma region Chapter2_Section8
struct SimpleRecipe_undefined {
};
struct SimpleRecipe_default {
	~SimpleRecipe_default() = default;
};
struct SimpleRecipe_simple {
	~SimpleRecipe_simple() {}
};
struct SimpleRecipe_noexcept {
	~SimpleRecipe_noexcept() noexcept {}
};
struct SimpleRecipe_deleted {
	~SimpleRecipe_deleted() = delete;
};

template <typename T>
concept CannotFailRecipe = std::destructible<T>;

static void CheckIfRecipeCannotFail(std::string typeName, CannotFailRecipe auto recipe) {
	std::cout << "Recipe " << typeName << " cannot be messed up\n";
}
class Chapter2_8 {
public:
	static void PrintCannotFailRecipes()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		CheckIfRecipeCannotFail("undefined", SimpleRecipe_undefined{});
		CheckIfRecipeCannotFail("default", SimpleRecipe_default{});
		CheckIfRecipeCannotFail("simple", SimpleRecipe_simple{});
		CheckIfRecipeCannotFail("noexcept", SimpleRecipe_noexcept{});
		// will not compile since it does not pass the concept's constraint
		// CheckIfRecipeCannotFail("deleted", SimpleRecipe_deleted{});
	}
};
#pragma endregion Chapter2_Section8

#pragma region Chapter2_Section9
struct SimpleRecipe_no_args_undefined {
};
struct SimpleRecipe_no_args_default {
	SimpleRecipe_no_args_default() = default;
};
struct SimpleRecipe_no_args_simple {
	SimpleRecipe_no_args_simple() {}
};
struct SimpleRecipe_no_args_noexcept {
	SimpleRecipe_no_args_noexcept() noexcept {}
};
struct SimpleRecipe_static {
	SimpleRecipe_static() = delete;
	SimpleRecipe_static(SimpleRecipe_static&& other) = delete;
	static SimpleRecipe_static CreateRecipe(std::string arg1) {
		return SimpleRecipe_static(arg1);
	}
private:
	SimpleRecipe_static(std::string) {}
};
struct SimpleRecipe_one_arg_simple {
	SimpleRecipe_one_arg_simple(int arg1) {}
	SimpleRecipe_one_arg_simple(SimpleRecipe_one_arg_simple&& other) = delete;
	SimpleRecipe_one_arg_simple() = delete;
};
struct SimpleRecipe_two_args_simple {
	SimpleRecipe_two_args_simple(int arg1, float arg2) {}
	SimpleRecipe_two_args_simple(SimpleRecipe_two_args_simple&& other) = delete;
	SimpleRecipe_two_args_simple() = delete;
};

template< typename T0>
static void CheckRecipeWithNoArgs(std::constructible_from<T0> auto recipe) { }

class Chapter2_9 {
private:

public:
	static void PrintRecipes()
	{
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		CheckRecipeWithNoArgs<SimpleRecipe_no_args_undefined>(SimpleRecipe_no_args_undefined{});
		CheckRecipeWithNoArgs<SimpleRecipe_no_args_default>(SimpleRecipe_no_args_default{});
		CheckRecipeWithNoArgs<SimpleRecipe_no_args_simple>(SimpleRecipe_no_args_simple{});
		CheckRecipeWithNoArgs<SimpleRecipe_no_args_noexcept>(SimpleRecipe_no_args_noexcept{});

		// ones below fail to compile
		//CheckRecipeWithNoArgs<SimpleRecipe_one_arg_simple>(SimpleRecipe_one_arg_simple(1) );
		//CheckRecipeWithNoArgs<SimpleRecipe_static>(SimpleRecipe_static::CreateRecipe("static"));
		//CheckRecipeWithNoArgs<SimpleRecipe_two_args_simple>(SimpleRecipe_two_args_simple(1, 2.0f));
	}
};
#pragma endregion Chapter2_Section9

#pragma region Chapter2_Section10
struct TypeWith_ImplicitDefaultConstructor {
};
struct TypeWith_DefaultConstructor {
	TypeWith_DefaultConstructor() = default;
};
struct TypeWith_ListInitializing {
	std::vector<std::string> values = { "C++23", "is", "great" };

	TypeWith_ListInitializing(std::initializer_list<std::string> args) { values = args; }
};
struct TypeWith_DefaultInitialization {
	TypeWith_DefaultInitialization() {}
	int value;
};
struct TypeWith_Param{
	TypeWith_Param(int valueGiven) {
		value = valueGiven;
	}
	int value;
};

class Chapter2_10 {
private:
	static void PrintType(std::default_initializable auto& v) {
		std::cout << "Type " << typeid(v).name() << " is default initializable" << std::endl;
	}
	static void PrintType(auto& v) {
		std::cout << "Type " << typeid(v).name() << " is NOT default initializable" << std::endl;
	}

public:
	static void LookAtDefaultInitializables() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		TypeWith_ImplicitDefaultConstructor t1;
		TypeWith_DefaultConstructor t2;
		TypeWith_ListInitializing t3{};
		TypeWith_DefaultInitialization t4;
		TypeWith_Param t5{ 5 };

		PrintType(t1);
		PrintType(t2);
		PrintType(t3);
		PrintType(t4);
		PrintType(t5);
	}
};
#pragma endregion Chapter2_Section10

#pragma region Chapter2_Section11
class RecipeSteps {
private:
	std::vector<std::string>* _steps;

public:
	// primary constructor
	RecipeSteps(std::initializer_list<std::string> steps) {
		std::cout << "in constructor with list of steps\n";
		_steps = new std::vector<std::string>(steps);
	}

	// copy constructor
	RecipeSteps(const RecipeSteps& obj) {	
		std::cout << "in constructor with copy\n";
		_steps = new std::vector<std::string>();
		_steps->insert(_steps->end(), obj._steps->begin(), obj._steps->end());
	}

	~RecipeSteps() {
		std::cout << "in destructor\n";
		delete _steps;
	}

	static void PrintSteps(RecipeSteps& recipe) {
		std::cout << "Steps for recipe\n";
		for (auto step = recipe._steps->begin(); step != recipe._steps->end(); ++step) {
			std::cout << "Step: " << *step << std::endl;
		}
	}

	static void PrintStepsWithTitle(std::string title, RecipeSteps recipe) {
		std::cout << "Name of recipe:  " << title << "\n";
		PrintSteps(recipe);
	}

	void AddStep(std::string step) { _steps->push_back(step); }
	void InsertStep(std::string step) { _steps->insert(_steps->begin(), step); }
	size_t GetNumberOfSteps() { return _steps->size(); }
};

class Chapter2_11_1 {
private:
	static void DoSimple() {
		std::cout << "simple recipe steps\n";
		RecipeSteps simple = RecipeSteps{ "mix", "heat", "eat" };
		RecipeSteps::PrintSteps(simple);
		std::cout << "done simple recipe\n";
	}

	static void DoMoreComplicated() {
		std::cout << "\n\nmore difficult recipe steps\n";
		RecipeSteps simple = RecipeSteps{ "mix", "bake", "eat" };
		RecipeSteps tougher = RecipeSteps(simple);
		tougher.InsertStep("preheat");

		RecipeSteps::PrintStepsWithTitle("More difficult recipe", tougher);
		std::cout << "done more difficult recipe\n";
	}
public:
	static void PrintRecipesForCopy() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

		DoSimple();
		DoMoreComplicated();
	};
};

// part 2
template <typename T>
concept HasListOfStepsTaken = requires (T t, std::string s) {
	t.AddStep(s);
};

template <typename T>
concept NeedToMakeCopy = HasListOfStepsTaken<T> && requires (T v) {
	std::copy_constructible<T>;
};

class Chapter2_11_2 {
private:
	static void DoSimple() {
		std::cout << "simple recipe steps\n";
		RecipeSteps simple = RecipeSteps{ "mix", "heat", "eat" };
		RecipeSteps::PrintSteps(simple);
		std::cout << "done simple recipe\n";
	}

	static void DoMoreComplicated() {
		std::cout << "\n\nmore difficult recipe steps\n";
		RecipeSteps simple = RecipeSteps{ "mix", "bake", "eat" };
		RecipeSteps tougher = RecipeSteps(simple);
		tougher.InsertStep("preheat");

		RecipeSteps::PrintStepsWithTitle("More difficult recipe", tougher);
		std::cout << "done more difficult recipe\n";
	}

	static auto DoSomethingWithCopy(NeedToMakeCopy auto chapter2) {
		chapter2.AddStep("and repeat");
		return chapter2;
	}
public:
	static void EnsureWorkingOnCopy() {
		std::cout << "\n\nEnsuring recipe is copied\n";
		RecipeSteps existingRecipe{ "mix", "heat", "eat" };
		auto trackingRecipe = DoSomethingWithCopy(existingRecipe);
		std::cout << "# Steps taken for recipe given = " << existingRecipe.GetNumberOfSteps() << std::endl;
		std::cout << "# Steps taken for recipe received = " << trackingRecipe.GetNumberOfSteps() << std::endl;
	}
};
#pragma endregion Chapter2_Section11

#pragma region Chapter2_Section12

template<typename T1, typename T2>
void CheckTypes() {
	bool inCommon = std::common_with<T1, T2>;
	std::cout << "Type: " << typeid(T1).name() << (inCommon ? " does" : " does not") << " share a common type with " << typeid(T2).name() << std::endl;
}

static void LookAtCommonWith() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

	CheckTypes<int, char>();
	CheckTypes<bool, long>();
	CheckTypes<bool, std::bad_exception>();
	CheckTypes<std::tuple<int,long>, std::pair<int,long>>();
}

template<typename T1, typename T2>
void CheckReferenceWithTypes() {
	bool inCommon = std::common_reference_with<T1, T2>;
	std::cout << "Type: " << typeid(T1).name() << (inCommon ? " does" : " does not") << " share a common reference type with " << typeid(T2).name() << std::endl;
}

static void LookAtCommonReferenceWith() {
	std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

	CheckReferenceWithTypes<int&, char&>();
	CheckReferenceWithTypes<std::common_reference_t<int&, const int&>, const int&>();
	CheckReferenceWithTypes<std::common_reference_t<int&&, int&&>, int&&>();
	CheckReferenceWithTypes<std::common_reference_t<int&&, int&&>, int>();
	CheckReferenceWithTypes<std::tuple<int, long>&, std::pair<int, long>&>();
	CheckReferenceWithTypes<std::common_reference_t<int&, int>, int&>();
}

class Chapter2_12 {
private:

public:
	static void LookAtConcepts() {
		LookAtCommonWith();
		LookAtCommonReferenceWith();
	}
};

#pragma endregion Chapter2_Section12


void LookAtChapter2Topics()
{
	// works with compiler?								when tested			clang	gcc		msvc
	Chapter2_1::TestRecipesWithSameAs();				// 20231029			yes		yes		yes
	Chapter2_2::TestRecipesWithConvertibleTo();			// 20231029			yes		yes		yes
	Chapter2_3::TryingSomeChowderThatIsDerivedFrom();	// 20231029			yes		yes		yes
	Chapter2_4::PrintNumbers();							// 20231029			yes		yes		yes
	Chapter2_5::PrintFloats();							// 20231029			yes		yes		yes
	Chapter2_6::AssignSomeSides();						// 20231029			yes		yes		yes
	Chapter2_7::SwapSomeSides();						// 20231029			yes		yes		yes
	Chapter2_8::PrintCannotFailRecipes();				// 20231029			yes		yes		yes
	Chapter2_9::PrintRecipes();							// 20231029			yes		yes		yes
	Chapter2_10::LookAtDefaultInitializables();			// 20231029			yes		yes		yes
	Chapter2_11_1::PrintRecipesForCopy();				// 20231029			yes		yes		yes
	Chapter2_11_2::EnsureWorkingOnCopy();				// 20231029			yes		yes		yes
	Chapter2_12::LookAtConcepts();						// 20231029			yes		yes		yes
}
