export module Module10_3_2;

import <iostream>;
import Module10_3_1;

export namespace WelcomeNS {
	class Chapter10_3_2 : public WelcomeNS::Chapter10_3_1 {
	protected:
		void SaySomethingNice() override {
			std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
			std::cout << "Looking forward to seeing you again!\n";
		}
	};
}
