#include <concepts>

template <class T>
concept IntegralType = std::is_integral_v<T>;

template<class T>
concept RecipeCount = std::is_integral_v<T>;



bool IsEvenNumber(IntegralType auto n) {
	return (n % 2 == 0);
}

template<class T>
concept UnsignedIntegralNumber = std::is_unsigned<T>::value;

template<class T>
concept UnsignedEvenIntegralNumber = UnsignedIntegralNumber<T> && IsEvenNumber<T>;

template<typename T>
concept SignedIntegralType = IntegralType<T> && requires(T) {
	requires !UnsignedIntegralNumber<T>;
};

template<typename T> requires IntegralType<T>
T AddIntegrals(T a, T b) {
	return a + b;
}

template<typename T>
	requires IntegralType<T>
T DoubleTheInteger(T n) {
	return (n * 2);
}

template<typename T>
concept IsAddable = requires (T a, T b) {
	a + b;
};

template<typename T>
	requires requires (T x) { x + x; }
auto AddEntities(T a, T b) {
	return a + b;
}

template<typename T>
concept AreNumbersAddable = requires (T a, T b) {
	a + b;
	std::is_integral_v<T>;
};

template<typename T>
concept HasDoubleIt = requires (T t) {
	{ t.Double() } -> std::convertible_to<int>;
};

template<typename T>
concept DoesMagicalThings = requires(T t)
{
	{ t.Magical() } -> std::same_as<void>;
};




class chapter1
{
public:
	static void TestRecipe();
};
