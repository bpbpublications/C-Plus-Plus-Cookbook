#include <iostream>
#include "chapter1.h"
#include <vector>
#include <concepts>

RecipeCount auto AddIntegrals(RecipeCount auto chapter1, RecipeCount auto chapter2) {
	return chapter1 + chapter2;
}

IntegralType auto AddIntegrals(IntegralType auto a, IntegralType auto b) {
	return a + b;
}

template <typename T>
concept PageCount = std::is_unsigned<T>::value;

template <typename T> requires PageCount<T>
auto AddPagesCountsUsingRequiresClause(T a, T b) {
	return a + b;
}

template <typename T>
auto AddPageCountsWithTrailingRequiresClause(T a, T b) requires PageCount<T> {
	return a + b;
}

template <PageCount T>
auto AddPageCountsWithConstrainedTemplate(T a, T b) {
	return a + b;
}

auto AddPageCountsAbbreviatedFunctionTemplate(PageCount auto a, PageCount auto b) {
	return a + b;
}




template <typename T>
concept HasIngredientList = requires (T v) {
	v.IngredientList;
};

template <typename T>
concept SortOfACompleteRecipe = requires (T v) {
	v.IngredientList;
	v.Instructions;
};

template <typename T>
concept CompleteRecipe = HasIngredientList<T> && requires (T v) {
	v.Instructions;
};

void RecipeFunction(HasIngredientList auto x) {}
//void RecipeFunction(SortOfACompleteRecipe auto x) {}
void RecipeFunction(CompleteRecipe auto x) {}


struct ThingWithIngredients {
	int IngredientList;
};

struct ThingWithSomethingElse {
	bool IsHealthy;
};


struct ThingWithIngredientsAndInstructions {
	int IngredientList;
	int Instructions;
};

struct AnotherThingWithIngredients {
	float IngredientList;
};

template <typename T>
concept SimplePageCount = std::is_integral_v<T>;

SimplePageCount auto AddPageCounts(SimplePageCount auto chapter1, SimplePageCount auto chapter2) {
	return chapter1 + chapter2;
}


//PageCount auto AddPageCounts(SimplePageCount* chapters, int numberOfChapters) {
//	// loop and add
//}
//PageCount auto AddPageCounts(std::vector<SimplePageCount> chapters) {
//	// loop and add
//}

static void AddSimplePageCounts() {
	unsigned short int ch1 = 4;
	long long ch2 = 123456;
	auto chapterTotal = AddPageCounts(ch1, ch2);
}

template <typename T>
concept LargePageCount = std::is_integral_v<T> && sizeof(T) > 4;

void PrintPageCount(LargePageCount auto count) {
	std::cout << "That is a big chapter!: " << count << "\n";
}
void PrintPageCount(PageCount auto count) {
	std::cout << "This is a small chapter: " << count << "\n";
}

static void PrintPageCounts() {
	unsigned short int ch1 = 4;
	long long ch2 = 123456;
	PrintPageCount(ch1);
	PrintPageCount(ch2);
}

void chapter1::TestRecipe() {
	//AddSimplePageCounts();

	PrintPageCounts();

	// compiles, since only one method is possible
	//RecipeFunction(ThingWithIngredients{});

	// compiler error, since the parameter doesn't match any functions
	//RecipeFunction(ThingWithSomethingElse{});

	// compiler error, since ambiguous
	//RecipeFunction(ThingWithIngredientsAndInstructions{});

	// also compiles, even though member variable is a different type
	//RecipeFunction(AnotherThingWithIngredients{});
}
