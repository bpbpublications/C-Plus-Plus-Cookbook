module;
import <iostream>;

export module Module10_3_1;

export namespace WelcomeNS {
	class Chapter10_3_1 {
	public:
		void GiveWelcome() {
			std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;

			std::cout << "Welcome to C++23\n";
			SaySomethingNice();
		}
	protected:
		virtual void SaySomethingNice() {
			std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;

			std::cout << "Hope you are having a good day!\n";
		}
	};
}
