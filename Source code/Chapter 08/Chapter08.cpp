#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <chrono>
#include <ctime>  
#include <exception>  
#include <map>  
#include <random>
#include <mutex>
#include <semaphore>
#include <syncstream>
#include <atomic>
#include <latch>
#include <barrier>
#include <time.h>
#include <algorithm>
#include <vector>

class Chapter8 {
public:
	static void outputText(std::string output) {
		std::chrono::system_clock::time_point scNow = std::chrono::system_clock::now();
		std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(scNow.time_since_epoch()) % 1000;

		std::time_t t_t = std::chrono::system_clock::to_time_t(scNow);
		std::tm tmNow;
#ifdef _MSC_VER
		localtime_s(&tmNow, &t_t);
#else
		localtime_r(&t_t, &tmNow);
#endif
		std::ostringstream oss;
		oss << std::put_time(&tmNow, "%H:%M:%S");
		oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
		std::cout << oss.str() << ": " << output << std::endl;
	}

	static void outputTextWithNumber(const std::string& message, int threadNumber) {
		std::ostringstream oss;
		oss << "Thread counter=" << threadNumber;
		oss << ", " << message;
		Chapter8::outputText(oss.str());
	}
};

#pragma region simple thread
class Chapter8_1_1 {
private:
	static void MyLittleFunction() {
		// can do a lot of other work in this spawned thread
	}

public:
	static void CallThread() {
		std::thread myThread(MyLittleFunction);

		// critical not to forget this
		// myThread.join();
	}
};
class Chapter8_1_2 {
private:
	static void MyLittleFunction() {
		// can do a lot of other work in this spawned thread
	}

public:
	static void CallThread() {
		std::jthread myThread(MyLittleFunction);

		// it will not longer crash if you forget this
		// but you should still call it
		// myThread.join();
	}
};
#pragma endregion simple thread

#pragma region thread with output
class Chapter8_1_3 {
private:
	static void cookSomething() {
		Chapter8::outputText("Still cooking ");
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		Chapter8::outputText("Ready to eat!");
	}

public:
	static void makeTheMeal() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::jthread thread(cookSomething);
		std::this_thread::sleep_for(std::chrono::seconds(6));
	}
};
#pragma endregion thread with output

#pragma region promise
class Chapter8_1_4 {
private:
	static void cookTheDishByValue(std::string food) {
		Chapter8::outputText("cooking the " + food);
		food = "delicious " + food;
	}

	static void cookTheDishByReferenceMaybe(std::string& food) {
		Chapter8::outputText("cooking the " + food);
		food = "tasty " + food;
	}

	static void cookTheDishByReference(std::string& food) {
		Chapter8::outputText("cooking the " + food);
		food = "yummy " + food;
	}
	
public:
	static void makeAnotherMeal() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::string foodToCook = "lasagna";

		std::jthread cookingThread1(cookTheDishByValue, foodToCook);
		cookingThread1.join();
		Chapter8::outputText("made the " + foodToCook);

		// will not compile
		// std::jthread cookingThread2(cookTheDishByReferenceMaybe, foodToCook);
		// cookingThread2.join();
		// Chapter8::outputText("made the " + foodToCook);

		std::jthread cookingThread3(cookTheDishByReference, std::ref(foodToCook));
		cookingThread3.join();
		Chapter8::outputText("made the " + foodToCook);
	}
};

class Chapter8_1_4c {
private:
	static void cookTheDishByValue(std::string food) {
		Chapter8::outputText("cooking the " + food);
		food = "delicious " + food;
	}

	static void cookTheDishByReferenceMaybe(std::string& food) {
		Chapter8::outputText("cooking the " + food);
		food = "tasty " + food;
	}

	static void cookTheDishByReference(std::string& food) {
		Chapter8::outputText("cooking the " + food);
		food = "yummy " + food;
	}

public:
	static void makeAnotherMeal() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::string foodToCook = "lasagna";

		std::jthread cookingThread1(cookTheDishByValue, foodToCook);
		// will not compile, since we cannot use copy/assignment operations with threads
		// std::jthread cookingThread1b = cookingThread1;
		std::jthread cookingThread1b = std::move(cookingThread1);
		// cookingThread1.join();
		cookingThread1b.join();

		cookingThread1.join();
		Chapter8::outputText("made the " + foodToCook);

		//std::jthread cookingThread2(cookTheDishByReferenceMaybe, foodToCook);
		//cookingThread2.join();  // no longer using this thread
		//Chapter8::outputText("made the " + foodToCook);

		std::jthread cookingThread3(cookTheDishByReference, std::ref(foodToCook));
		cookingThread3.join();
		Chapter8::outputText("made the " + foodToCook);

		//std::jthread cookingThread4(cookTheDishByReference, std::move(foodToCook));
		//cookingThread4.join();
		// since gave ownership of the variable to the child thread, we can no longer use the variable
		//Chapter8::outputText("made the " + foodToCook)
	}
};

class Chapter8_1_5 {
private:
	static bool cookTheDishByFuture(std::future<std::string>& foodFuture) {
		Chapter8::outputText("Thinking about cooking");
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		auto food = foodFuture.get();
		Chapter8::outputText("Cooking " + food);
		if (food.compare("Filindeu") == 0) {
			throw std::invalid_argument("This is impossible to make!!!");
		}
		Chapter8::outputText("Ready to eat!");
		return true;
	}

	static void cookTheDishByValue(std::string food) {
		Chapter8::outputText("cooking the " + food);
		food = "delicious " + food;
	}

public:
	static void makeMealInTheFuture() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		Chapter8::outputText("old passing by value");
		std::async(std::launch::async, cookTheDishByValue, "lasagna");

		Chapter8::outputText("passing by promise right away");
		std::promise<std::string> prom1;
		std::future<std::string> fut1 = prom1.get_future();
		prom1.set_value("lasagna");
		std::future<bool> result1 = std::async(std::launch::async, cookTheDishByFuture, std::ref(fut1));
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		Chapter8::outputText("Result of cooking was " + std::string(result1.get() ? "good" : "bad"));

		Chapter8::outputText("passing by promise, but making thread wait");
		std::promise<std::string> prom2;
		std::future<std::string> fut2 = prom2.get_future();
		std::future<bool> result2 = std::async(std::launch::async, cookTheDishByFuture, std::ref(fut2));
		std::this_thread::sleep_for(std::chrono::milliseconds(7000));
		prom2.set_value("spaghetti");
		Chapter8::outputText("Result of cooking was " + std::string(result2.get() ? "good" : "bad"));
	}
};

class Chapter8_1_6 {
private:
	static bool cookTheDishByFuture(std::future<std::string>& foodFuture) {
		Chapter8::outputText("Thinking about cooking");
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		auto food = foodFuture.get();
		Chapter8::outputText("Cooking " + food);
		if (food.compare("Filindeu") == 0) {
			throw std::invalid_argument("This is impossible to make!!!");
		}
		Chapter8::outputText("Ready to eat!");
		return true;
	}

public:
	static void problemMeals() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		try {
			std::promise<std::string> prom3;
			std::future<std::string> fut3 = prom3.get_future();
			Chapter8::outputText("passing by promise something extremely difficult to make");
			prom3.set_value("Filindeu");
			std::future<bool> result3 = std::async(std::launch::async, cookTheDishByFuture, std::ref(fut3));
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			Chapter8::outputText("Result of cooking was " + (std::string(result3.get() ? "good" : "bad")));
		}
		catch (const std::exception& ex) {
			Chapter8::outputText("Result of cooking was... really bad");
			Chapter8::outputText(ex.what());
		}

		try {
			Chapter8::outputText("passing by promise, but then breaking it");
			std::promise<std::string> prom5;
			std::future<std::string> fut5 = prom5.get_future();
			std::future<bool> result5 = std::async(std::launch::async, cookTheDishByFuture, std::ref(fut5));
			std::this_thread::sleep_for(std::chrono::milliseconds(7000));
			prom5.set_exception(std::make_exception_ptr(std::invalid_argument("ran out of food to cook")));
			Chapter8::outputText("Result of cooking was " + std::string(result5.get() ? "good" : "bad"));
		}
		catch (const std::exception& ex) {
			Chapter8::outputText("Result of cooking was... really bad");
			Chapter8::outputText(ex.what());
		}
	}
};
#pragma endregion promise

#pragma region stop_token
class Chapter8_2 {
private:
	static std::string getDurationText(std::chrono::time_point<std::chrono::system_clock> start,
		std::chrono::time_point<std::chrono::system_clock> end) {
		std::ostringstream oss;
		std::chrono::duration<double> diff = end - start;
		oss << "duration of " << std::setfill('0') << std::setw(4) << diff.count();
		return oss.str();
	}
	static void cookTheDishButThenStop(std::stop_token stoptk, std::string food) {
		static thread_local auto start = std::chrono::system_clock::now();
		Chapter8::outputText("starting to cook the " + food);
		for (int i = 0; i < 10; i++) {
			if (stoptk.stop_requested()) {
				auto durationText = getDurationText(start, std::chrono::system_clock::now());
				Chapter8::outputText("stopped cooking the " + food + " early, after " + durationText);
				return;
			}
			Chapter8::outputText("still cooking");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		auto durationText = getDurationText(start, std::chrono::system_clock::now());
		Chapter8::outputText("regular time to stop cooking the " + food + ", " + durationText);
	}

public:
	static void stopTheMeal() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		std::jthread cookingThread1(cookTheDishButThenStop, "lasagna");
		cookingThread1.join();

		std::jthread cookingThread2(cookTheDishButThenStop, "pizza");
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		cookingThread2.request_stop();
		cookingThread2.join();

		std::jthread cookingThread3(cookTheDishButThenStop, "soup");
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
};
#pragma endregion stop_token

#pragma region stop_callback
class Chapter8_3 {
private:
	static std::string getDurationText(std::chrono::time_point<std::chrono::system_clock> start,
		std::chrono::time_point<std::chrono::system_clock> end) {
		std::ostringstream oss;
		std::chrono::duration<double> diff = end - start;
		oss << "duration of " << std::setfill('0') << std::setw(4) << diff.count();
		return oss.str();
	}

	static void cookTheDishButThenStop(std::stop_token stoptk, std::string food) {
		static thread_local auto start = std::chrono::system_clock::now();
		Chapter8::outputText("starting to cook the " + food);
		for (int i = 0; i < 10; i++) {
			if (stoptk.stop_requested()) {
				auto durationText = getDurationText(start, std::chrono::system_clock::now());
				Chapter8::outputText("stopped cooking the " + food + " early, after " + durationText);
				return;
			}
			Chapter8::outputText("still cooking");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		auto durationText = getDurationText(start, std::chrono::system_clock::now());
		Chapter8::outputText("regular time to stop cooking the " + food + ", " + durationText);
	}

	static void callbackFn() {
		Chapter8::outputText("in callback fn");
	}

	static void cookTheDishButDoCallbackWhenStopped(std::stop_token stoptk, std::string food) {
		static thread_local auto start = std::chrono::system_clock::now();
		Chapter8::outputText("starting to cook the " + food);

		std::stop_callback cb1{ stoptk, [] {
			Chapter8::outputText("callback to stop");
			} };
		std::stop_callback cb2{ stoptk, callbackFn };

		for (int i = 0; i < 10; i++) {
			if (stoptk.stop_requested()) {
				auto durationText = getDurationText(start, std::chrono::system_clock::now());
				Chapter8::outputText("stopped cooking the " + food + " early, after " + durationText);
				return;
			}
			Chapter8::outputText("still cooking");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		auto durationText = getDurationText(start, std::chrono::system_clock::now());
		Chapter8::outputText("regular time to stop cooking the " + food + ", " + durationText);
	}

public:
	static void stopTheMealWithCallback() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		Chapter8::outputText("creating a thread to cook something");
		std::jthread cookingThread2(cookTheDishButDoCallbackWhenStopped, "pizza");
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		cookingThread2.request_stop();
		cookingThread2.join();
	}
};
#pragma endregion stop_callback

#pragma region stop_source
class Chapter8_4 {
private:
	static std::string getDurationText(std::chrono::time_point<std::chrono::system_clock> start,
		std::chrono::time_point<std::chrono::system_clock> end) {
		std::ostringstream oss;
		std::chrono::duration<double> diff = end - start;
		oss << "duration of " << std::setfill('0') << std::setw(4) << diff.count();
		return oss.str();
	}

	static void callbackFn() {
		Chapter8::outputText("in callback fn");
	}

	static void cookTheDishButThenSourceStopWithCallback(std::string food, std::stop_source stopper) {
		static thread_local auto start = std::chrono::system_clock::now();
		Chapter8::outputText("starting to cook the " + food);

		std::stop_token stoptk = stopper.get_token();
		std::stop_callback cb1{ stoptk, [] {
			Chapter8::outputText("callback to stop");
			} };
		std::stop_callback cb2{ stoptk, callbackFn };

		for (int i = 0; i < 10; i++) {
			if (i == 3 && food == "ravioli") {
				stopper.request_stop();
			}

			if (stoptk.stop_requested()) {
				auto durationText = getDurationText(start, std::chrono::system_clock::now());
				Chapter8::outputText("stopped cooking the " + food + " early, after " + durationText);
				return;
			}
			Chapter8::outputText("still cooking");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		auto durationText = getDurationText(start, std::chrono::system_clock::now());
		Chapter8::outputText("regular time to stop cooking the " + food + ", " + durationText);
	}

public:
	static void stopTheMealWithStopSource() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		Chapter8::outputText("creating a thread to cook something, and then stop it");
		std::stop_source stopper1;
		std::jthread cookingThread1(cookTheDishButThenSourceStopWithCallback, "pizza", stopper1);
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		stopper1.request_stop();
		cookingThread1.join();

		Chapter8::outputText("creating a thread to cook something, and then stop it from inside");
		std::stop_source stopper2;
		std::jthread cookingThread2(cookTheDishButThenSourceStopWithCallback, "ravioli", stopper2);
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		cookingThread2.join();

		Chapter8::outputText("creating multiple threads, and then stop them all with the same stop_source");
		const int thread_count = 3;
		std::jthread threads[thread_count];
		std::stop_source stopper3;
		for (int n = 0; n < thread_count; n++) {
			std::ostringstream oss;
			oss << "dish" << n;
			threads[n] = std::jthread(cookTheDishButThenSourceStopWithCallback, oss.str(), stopper3);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		stopper3.request_stop();
	}
};
#pragma endregion stop_source

#pragma region mutex and semaphores
static std::mutex mapMutex;
static std::vector<std::pair<std::string, int>> recipeAndRating;

class Chapter8_5_1 {
private:

	static void evaluateRecipe(std::string food, int secondsDelay) {
		const int BestRating = 100;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		// thinking about rating	
		std::this_thread::sleep_for(std::chrono::milliseconds(secondsDelay * 1000));
		std::lock_guard<std::mutex> guard(mapMutex);
		std::pair<std::string, int> pair(food, gen() % BestRating);
		recipeAndRating.push_back(pair);
		std::cout << "Recipe=" << pair.first
			<< ", rating=" << pair.second << std::endl;
		// guard goes out of scope, freeing up mutex
	}

public:
	static void lookAtMutexMap() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		static std::random_device rd;
		static std::mt19937 gen (rd());
		const std::string recipes[] = { "lasagna", "broiled chicken", "falafel", "ravioli" };
		std::jthread threads[4];
		int threadCounter = 0;
		std::cout << "Looping through recipes\n";
		for (std::string recipe : recipes) {
			const int MaxSeconds = 5;
			int secondsDelay = (gen() & MaxSeconds) + 1;
			std::cout << "Thinking about rating on " << recipe << " for " << secondsDelay << " seconds\n";
			threads[threadCounter] = std::jthread(evaluateRecipe, recipe, secondsDelay);
			threadCounter++;
		}
		std::cout << "\nLooking at ratings\n";
		while (threadCounter > 0) {
			threads[threadCounter - 1].join();
			threadCounter--;
		}
		//
		std::sort(recipeAndRating.begin(), recipeAndRating.end(),
			[](const std::pair<std::string, int>& l,
				const std::pair<std::string, int>& r) {
					return l.second > r.second; });
		//
		std::cout << "\nLooping through ranked ratings\n";
		for (auto it = recipeAndRating.begin(); it != recipeAndRating.end(); it++) {
			std::cout << "Recipe=" << it->first
				<< ", rating=" << it->second << std::endl;
		}
	}
};

class Chapter8_5_2 {
private:
	static void lookAtResourceIfSemphoreAllows(int threadNumber) {
		static std::counting_semaphore counter{ 2 };
		Chapter8::outputTextWithNumber("Started thread", threadNumber);
		counter.acquire();
		Chapter8::outputTextWithNumber("acquired", threadNumber);
		// use the resource for a brief while
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		counter.release();
	}

public:
	static void lookAtCountingSemaphore() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		const int thread_count = 6;
		std::jthread threads[thread_count];
		for (int n = 0; n < thread_count; n++) {
			threads[n] = std::jthread(lookAtResourceIfSemphoreAllows, n);
		}
	}
};
#pragma endregion mutex and semaphores

#pragma region simple atomic
static std::atomic<float> simpleAtomicNumber;

class Chapter8_6 {
private:
	static void incrementSimpleAtomic() {
		simpleAtomicNumber += 0.42;
	}

public:
	static void lookAtSimpleAtomic() {
		std::cout << std::endl << std::endl << __FUNCTION__ << std::endl;
		simpleAtomicNumber = 0;
		const int thread_count = 100;
		std::jthread threads[thread_count];
		for (int n = 0; n < thread_count; n++) {
			threads[n] = std::jthread(incrementSimpleAtomic);
		}
		for (int n = 0; n < thread_count; n++) {
			threads[n].join();
		}
		std::cout << "Result="
			<< std::fixed << std::setprecision(2) << simpleAtomicNumber;
	}
};
#pragma endregion simple atomic

#pragma region simple ref
struct ValueHolder {
	float value{ 0 };
};

static ValueHolder myValue{};
static std::atomic_ref<float> simpleAtomicRef{ myValue.value };

class Chapter8_10 {
private:
	static void incrementRefAtomic() {
		simpleAtomicRef += 0.42;
	}

public:
	static void lookAtSimpleAtomicRef() {
		const int thread_count = 100;
		std::jthread threads[thread_count];
		for (int n = 0; n < thread_count; n++) {
			threads[n] = std::jthread(incrementRefAtomic);
		}
		for (int n = 0; n < thread_count; n++) {
			threads[n].join();
		}
		std::cout << "Result="
			<< std::fixed << std::setprecision(2) << myValue.value;
	}
};
#pragma endregion simple ref

#pragma region wait and notify
static std::atomic<bool> allRecipesCooked;
static std::atomic<int> recipeCount;
static std::atomic<int> recipesCompleted;

static void cookRecipeAndNotify() {
	const int LongestWait = 1000;
	static std::random_device rd;
	static std::mt19937 gen(rd());

	recipeCount++;
	int recipeId = recipeCount.load();
	Chapter8::outputTextWithNumber("starting to cook for recipe ", recipeId);
	// things take different times to cook
	std::this_thread::sleep_for(std::chrono::milliseconds(gen() % LongestWait));
	Chapter8::outputTextWithNumber("done cooking recipe ", recipeId);
	recipesCompleted++;
	recipeCount--;

	if (recipeCount.load() == 0) {
		allRecipesCooked = true;
		allRecipesCooked.notify_one();
	}
}

static void lookAtSimpleWait() {
	const int thread_count = 10;
	std::jthread threads[thread_count];
	for (int n = 0; n < thread_count; n++) {
		threads[n] = std::jthread(cookRecipeAndNotify);
	}

	allRecipesCooked.wait(false);
	std::cout << "We have cooked " << recipesCompleted.load()
		<< " recipes, time to eat!" << std::endl;
}
#pragma endregion wait and notify

#pragma region latch
static const std::string recipesToCookAndLatch[] = { "lasagna", "broiled chicken", "falafel", "ravioli" };
static std::latch recipesToCook{ std::size(recipesToCookAndLatch) };
class Chapter8_8 {
private:
	static void cookRecipeAndTriggerDecrement(std::string food) {
		const int LongestWait = 5000;
		static std::random_device rd;
		static std::mt19937 gen(rd());

		Chapter8::outputText("starting to cook recipe: " + food);
		// things take different times to cook
		std::this_thread::sleep_for(std::chrono::milliseconds(gen() % LongestWait));
		Chapter8::outputText("done cooking recipe: " + food);
		recipesToCook.count_down();
	}

public:
	static void lookAtSimpleLatch() {
		const size_t thread_count = std::size(recipesToCookAndLatch);
		std::jthread threads[thread_count];
		for (auto n = 0; n < thread_count; n++) {
			threads[n] = std::jthread(cookRecipeAndTriggerDecrement, recipesToCookAndLatch[n]);
		}

		recipesToCook.wait();
		std::cout << "We have cooked " << thread_count << " recipes, time to eat!" << std::endl;
	}
};
#pragma endregion latch

#pragma region barrier
const std::string guestsForDinner[] = { "Allen", "Bob", "Charles", "Doug" };
static void completionForAllGuests() noexcept {
	static auto status = "all arrived";
	Chapter8::outputText(status);
	/* can change the value of the static, 
		and when it is called again the status will have changed */
	status = "all ate";
}

std::barrier barrierForGuests{ std::size(guestsForDinner), completionForAllGuests };

class Chapter8_9 {
private:
	static void waitForGuest(std::string guest) {
		const int LongestWait = 5000;
		static std::random_device rd;
		static std::mt19937 gen(rd());

		Chapter8::outputText("wait for arrival of guest: " + guest);
		// people live at different distances
		std::this_thread::sleep_for(std::chrono::milliseconds(gen() % LongestWait));
		Chapter8::outputText("arrival of guest: " + guest);
		barrierForGuests.arrive_and_wait();
		// people eat at different speeds
		std::this_thread::sleep_for(std::chrono::milliseconds(gen() % LongestWait));
		Chapter8::outputText(guest + " is eating dinner");
		barrierForGuests.arrive_and_wait();
	}

public:
	static void lookAtSimpleBarrier() {
		const size_t thread_count = std::size(guestsForDinner);
		std::jthread threads[thread_count];
		for (auto n = 0; n < thread_count; n++) {
			threads[n] = std::jthread(waitForGuest, guestsForDinner[n]);
		}
		for (auto n = 0; n < thread_count; n++) {
			threads[n].join();
		}

		std::cout << "Hopefully all " << thread_count << " guests enjoyed their meal!" << std::endl;
	}
};
#pragma endregion barrier

void LookAtChapter8Topics() {
	// works with compiler?						when tested		    clang	msvc	gcc
	Chapter8_1_2::CallThread();				//  20231112			yes		yes		yes
	Chapter8_1_3::makeTheMeal();			//  20231112			yes		yes		yes
	Chapter8_1_4::makeAnotherMeal();		//  20231112			yes		yes		yes
	Chapter8_1_5::makeMealInTheFuture();	//  20231112			yes		yes		yes
	Chapter8_1_6::problemMeals();			//  20231112			yes		yes		yes
	Chapter8_2::stopTheMeal();				//  20231112			yes		yes		yes
	Chapter8_3::stopTheMealWithCallback();	//  20231112			yes		yes		yes
	Chapter8_4::stopTheMealWithStopSource();//  20231112			yes		yes		yes
	Chapter8_5_1::lookAtMutexMap();			//  20231112			yes		yes		yes
	Chapter8_5_2::lookAtCountingSemaphore();//  20231112			yes		yes		yes
	Chapter8_6::lookAtSimpleAtomic();		//  20231112			yes		yes		yes
	Chapter8_8::lookAtSimpleLatch();		//  20231112			yes		yes		yes
	Chapter8_9::lookAtSimpleBarrier();		//  20231112			yes		yes		yes
	Chapter8_10::lookAtSimpleAtomicRef();	//  20231112			yes		yes		yes
}
