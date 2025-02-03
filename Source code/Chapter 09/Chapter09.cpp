#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>
#include <variant>
#include <type_traits>
#include <tuple>
#include "cassert"
#include <algorithm>
#include <vector>
#include <utility>

#pragma region Chapter9_Section2
struct promise_type {
    auto get_return_object();
    auto initial_suspend() { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_never{}; }
    void unhandled_exception() { std::terminate(); }
    // if a task; not returning a value
    // void return_void();

    // if a generator, returning a value
    void return_value();
};

struct CoroutineAwaitable {
    constexpr bool await_ready() const noexcept { return false; }
    std::coroutine_handle<>* handle;
    void await_suspend(std::coroutine_handle<> h) { *handle = h; }
    constexpr void await_resume() const noexcept {}
};
#pragma endregion Chapter9_Section2

#pragma region Chapter9_Section3_1
template<typename T>
struct Generator9_3_1 {
    struct promise_type {
        auto get_return_object() noexcept {
            return Generator9_3_1{ *this };
        }
        std::suspend_always initial_suspend() const noexcept { return {}; }
        std::suspend_always final_suspend() const noexcept { return {}; }
        void unhandled_exception() noexcept {
            std::terminate();
        }
        std::suspend_always yield_value(const T& value) noexcept {
            result = value;
            return {};
        }
        T& getValue() {
            return result;
        };
        void return_void() const noexcept {}
 private:
        T result;
    };

    ~Generator9_3_1() {
        if (coroHandle) coroHandle.destroy();
    }
    auto& operator()() const {
        if (coroHandle.done() == false)
        {
            coroHandle.resume();
            return coroHandle.promise().getValue();
        }
    }
private:
    explicit Generator9_3_1(Generator9_3_1::promise_type& promise) noexcept :
        coroHandle{ std::coroutine_handle<Generator9_3_1::promise_type>::from_promise(promise) }
    {
    }
    std::coroutine_handle<Generator9_3_1::promise_type> coroHandle;
};

class Chapter9_3_1 {
private:
    static Generator9_3_1<int> MakeIntGenerator() {
        for (int i = 1; i < 5; i++) {
            co_yield i;
        }
    }
public:
    static void RunSimpleGeneratorWithoutKnowingLimits() {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        const auto gen = MakeIntGenerator();
        for (int x = 1; x < 3; x++) {
            std::cout << gen() << ' ';
        }
        std::cout << std::endl;
    }
};
#pragma endregion Chapter9_Section3_1

#pragma region Chapter9_Section3_2
template<typename T>
struct Generator9_3_2 {
    struct promise_type {
        auto get_return_object() noexcept {
            return Generator9_3_2{ *this };
        }
        std::suspend_always initial_suspend() const noexcept { return {}; }
        std::suspend_always final_suspend() const noexcept { return {}; }
        void unhandled_exception() noexcept(std::is_nothrow_copy_constructible_v<std::exception_ptr>) {
            std::terminate();
        }
        std::suspend_always yield_value(const T& value) noexcept(std::is_nothrow_copy_constructible_v<T>) {
            result = value;
            isInitialized = true;
            return {};
        }
        // precondition for getValue: either have value or exception
        T& getValue() noexcept {
            return result;
        }
        void return_void() const noexcept {}

        bool isValueInitialized() const noexcept {
            return isInitialized;
        }
    private:
        T result;
        bool isInitialized = false;
    };

    struct Iterator {
        Iterator() noexcept = default;
        explicit Iterator(const std::coroutine_handle<Generator9_3_2::promise_type>& coroGiven) noexcept :
            coro{ &coroGiven }
        {
        }
        friend bool operator==(const Iterator&, const Iterator&) noexcept = default;

        Iterator& operator++() {
            assert(coro != nullptr);
            assert(!coro->done());

            coro->resume();
            if (coro->done()) {
                auto coroHandle = std::exchange(coro, nullptr);
            }
            return *this;
        }
        auto& operator*() const noexcept {
            assert(coro != nullptr);
            assert(!coro->done());
            return coro->promise().getValue();
        }
    private:
        const std::coroutine_handle<Generator9_3_2::promise_type>* coro = nullptr;
    };

    ~Generator9_3_2() {
        if (coroHandle) coroHandle.destroy();
    }
    Iterator begin() const {
        if (coroHandle.done()) return end();
        auto it = Iterator{ coroHandle };
        if (!coroHandle.promise().isValueInitialized()) {
            ++it;
        }
        return it;
    }
    Iterator end() const noexcept {
        return {};
    }
    auto& operator()() const {
        if (coroHandle.done() == false) {
            coroHandle.resume();
            return coroHandle.promise().getValue();
        }
    }
    bool canResume() const {
        return not coroHandle.done();
    }

private:
    explicit Generator9_3_2(Generator9_3_2::promise_type& promise) noexcept :
        coroHandle{ std::coroutine_handle<Generator9_3_2::promise_type>::from_promise(promise) }
    {
    }
    std::coroutine_handle<Generator9_3_2::promise_type> coroHandle;
};

class Chapter9_3_2 {
private:
    static Generator9_3_2<int> MakeIntGenerator() {
        for (int i = 1; i < 5; i++) {
            co_yield i;
        }
    }
public:
    static void RunIntGeneratorWithIterator() {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        const auto anotherGen = MakeIntGenerator();
        for (int i = 1; i < 5 && anotherGen.canResume(); i++) {
            std::cout << anotherGen() << std::endl;
        }
        std::cout << std::endl << "Another pass, with iterator" << std::endl;
        const auto gen = MakeIntGenerator();
        for (auto it = gen.begin(); it != gen.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << std::endl;
    }
};

class Chapter9_3_2b {
private:
    static Generator9_3_2<std::string> MakeMenuGenerator() {
        const std::string menuItemsFromDatabase[] = { "Spaghetti", "Lasagna", "Shrimp Linguine", "Fresh Salad" };
        const std::string itemRetrievedFromYesterdaysMenu = "Turkey";

        co_yield itemRetrievedFromYesterdaysMenu + " sandwich, and fries";
        for (std::string menuItem : menuItemsFromDatabase) {
            co_yield menuItem;
        }
    }
public:
    static void RunMenuGenerator() {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        std::cout << "Today's menu:" << std::endl;
        const auto gen = MakeMenuGenerator();
        try {
            auto it2 = gen.begin();
            auto it = gen.begin();
            for (; it != gen.end(); ++it) {
                std::cout << *it << std::endl;
            }
            std::cout << "\n" << "it is " << (it == gen.end() ? "Done" : "not done") << std::endl;
            std::cout << "it2 is " << (it2 == gen.end() ? "Done" : "not done") << std::endl;

            for (auto it = gen.begin(); it != gen.end(); ++it) {
                std::cout << "second pass" << *it << ' ';
            }
        }
        catch (const std::exception& ex) {
            std::cout << "caught " << typeid(ex).name() << ": " << ex.what() << std::endl;
        }
        
        std::cout << std::endl << "Today's menu again:" << std::endl;
        const auto gen2 = MakeMenuGenerator();
        try {
            for (auto item : gen2) {
                std::cout << item << std::endl;
            }
        }
        catch (const std::exception& ex) {
            std::cout << "caught " << typeid(ex).name() << ": " << ex.what() << std::endl;
        }
        
        std::cout << std::endl << "Old way of looking at the menu:" << std::endl;
        const auto gen3 = MakeMenuGenerator();
        for (int i = 1; i < 15 && gen3.canResume(); i++) {
            std::cout << gen3() << std::endl;
        }
    }
};
#pragma endregion Chapter9_Section3_2

#pragma region Chapter9_Section3_3
template<typename T>
struct Generator9_3_3 {
    struct promise_type {
        auto get_return_object() noexcept {
            return Generator9_3_3{ *this };
        }
        std::suspend_always initial_suspend() const noexcept { return {}; }
        std::suspend_always final_suspend() const noexcept { return {}; }
        std::suspend_never yield_value(const T & value) noexcept {
            result = value;
            isInitialized = true;
            return {};
        }
        void unhandled_exception() noexcept {
            std::terminate();
        }
        T& getValue() noexcept {
            return result;
        }
        void return_void() const noexcept {}

        bool isValueInitialized() const noexcept {
            return isInitialized;
        }
    private:
        T result;
        bool isInitialized = false;
    };

    struct Iterator {
        Iterator() noexcept = default;
        explicit Iterator(const std::coroutine_handle<Generator9_3_3::promise_type>& coroGiven) noexcept :
            coro{ &coroGiven }
        {
        }
        friend bool operator==(const Iterator&, const Iterator&) noexcept = default;

        Iterator& operator++() {
            assert(coro != nullptr);
            assert(!coro->done());

            coro->resume();
            if (coro->done()) {
                auto coroHandle = std::exchange(coro, nullptr);
            }
            return *this;
        }
        auto& operator*() const noexcept {
            assert(coro != nullptr);
            assert(!coro->done());
            return coro->promise().getValue();
        }
    private:
        const std::coroutine_handle<Generator9_3_3::promise_type>* coro = nullptr;
    };

    ~Generator9_3_3() {
        if (coroHandle) coroHandle.destroy();
    }

    Iterator begin() const {
        if (coroHandle.done()) return end();
        auto it = Iterator{ coroHandle };
        if (!coroHandle.promise().isValueInitialized()) {
            ++it;
        }
        return it;
    }
    Iterator end() const noexcept {
        return {};
    }
    auto& operator()() const {
        if (coroHandle.done() == false) {
            coroHandle.resume();
            return coroHandle.promise().getValue();
        }
    }
    bool canResume() const {
        return not coroHandle.done();
    }

private:
    explicit Generator9_3_3(Generator9_3_3::promise_type& promise) noexcept :
        coroHandle{ std::coroutine_handle<Generator9_3_3::promise_type>::from_promise(promise) }
    {
    }
    std::coroutine_handle<Generator9_3_3::promise_type> coroHandle;
};

class Chapter9_3_3 {
private:
    static Generator9_3_3<std::string> MakeGeneratorThatDoesNotSuspend() {
        const std::string menuItemsFromDatabase[] = { "Spaghetti", "Lasagna", "Shrimp Linguine", "Fresh Salad" };

        for (std::string menuItem : menuItemsFromDatabase) {
            co_yield menuItem;
        }
    }
public:
    // does not generate anything
    static void RunGenerator() {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        std::cout << "Today's menu:" << std::endl;
        const auto gen = MakeGeneratorThatDoesNotSuspend();
        try {
            for (auto item : gen) {
                std::cout << item << std::endl;
            }
        }
        catch (const std::exception& ex) {
            std::cout << "caught " << typeid(ex).name() << ": " << ex.what() << std::endl;
        }
    }
};
#pragma endregion Chapter9_Section3_3

#pragma region Chapter9_Section4
struct Generator9_4 {
private:
    struct renamed_promise;

public:
    struct MyCoroutine : std::coroutine_handle<Generator9_4::renamed_promise>
    {
        using promise_type = Generator9_4::renamed_promise;
    };

private:
    struct renamed_promise
    {
        MyCoroutine get_return_object() { return { MyCoroutine::from_promise(*this) }; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

class Chapter9_4 {
public:
    static void CallRenamedGen() {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        Generator9_4::MyCoroutine gen = [](int i) -> Generator9_4::MyCoroutine {
            std::cout << i;
            co_return;
            }(42);
            gen.resume();
            gen.destroy();
    }
};
#pragma endregion Chapter9_Section4

#pragma region Chapter9_Section5
class Chapter9_5_1 {
private:
    static int generateToFill()
    {
        static int i = 1;
        return i++;
    }

public:
    static void FillWithGenerate() {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        std::vector<int> col(10);
        std::generate(col.begin(), col.end(), generateToFill);
        for (auto it = col.begin(); it != col.end(); ++it) {
            std::cout << "Number=" << *it << std::endl;
        }
    }
};

class Chapter9_5_2 {
private:
    static int generateToFill()
    {
        static int i = 1;
        return i++;
    }

    class SimpleNumberGenerator {
    public:
        SimpleNumberGenerator(int initialValue = 0) : value{ initialValue } {}
        int operator() () {
            return value++;
        }
    private:
        int value;
    };

public:
    static void FillWithGenerateUsingGenerator()
    {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;

        std::vector<int> col(5);
        std::generate(col.begin(), col.end(), generateToFill);
        for (auto it = col.begin(); it != col.end(); ++it) {
            std::cout << "Number=" << *it << std::endl;
        }
        //
        std::vector<int> col2(5);
        std::generate(col2.begin(), col2.end(), SimpleNumberGenerator(6));
        for (auto it = col2.begin(); it != col2.end(); ++it) {
            std::cout << "Number=" << *it << std::endl;
        }
    }
};

class Chapter9_5_3 {
private:
#if __cpp_lib_generator	>= 202207L
    std::generator<int> CreateNumbers(int first)
    {
        for (;; co_yield first++);
    }
#endif

public:
    static void RunNumberGenerator()
    {
        std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
#if __cpp_lib_generator	>= 202207L
        for (const int num : CreateNumbers(42) | std::views::take())
            std::cout << num << ' ';
        std::cout << '\n';
#else
        std::cout << "Feature not yet implemented." << std::endl;
#endif
    }
};
#pragma endregion Chapter9_Section5

void LookAtChapter9Topics() {
    // works with compiler?						              when tested	clang	msvc	gcc
    Chapter9_3_1::RunSimpleGeneratorWithoutKnowingLimits(); // 2023.11.20   yes     yes     yes
    Chapter9_3_2::RunIntGeneratorWithIterator();            // 2023.11.20   yes     yes     yes 
    Chapter9_3_2b::RunMenuGenerator();                      // 2023.11.20   yes     yes     yes 
    Chapter9_3_3::RunGenerator();                           // 2023.11.20   no output expected
    Chapter9_4::CallRenamedGen();                           // 2023.11.20   yes     yes     yes 
    Chapter9_5_1::FillWithGenerate();                       // 2023.11.20   yes     yes     yes 
    Chapter9_5_2::FillWithGenerateUsingGenerator();         // 2023.11.20   yes     yes     yes 
    Chapter9_5_3::RunNumberGenerator();                     // 2023.11.20    no      no      no
}
