export module Module10_3_3;

import <iostream>;
import Module10_3_1;
import Module10_1_3;

class Chapter10_3_3_Helper {
public:
	static void CallingManyImportedFunctions() {
		std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
#ifndef _MSC_VER
		PlainNothing();
#endif
		Class10_1_3a c10_1_3a;
		c10_1_3a.Nothing();
		NameSpace1::Class10_1_3d c10_1_3d;
		c10_1_3d.Nothing();
		NameSpace2::Class10_1_3e c10_1_3e;
		c10_1_3e.Nothing();
#ifndef _MSC_VER
		VeryPlainNothing();
#endif
		// cannot call things that are not exported
		// NameSpace2::NotExported bad1;
		// AlsoPlainButNotExported();
	}
};

export namespace WelcomeNS {
	class Chapter10_3_3 : public WelcomeNS::Chapter10_3_1 {
	protected:
		void SaySomethingNice() override {
			std::cout << std::endl << __FILE__ << " : " << std::endl << __FUNCTION__ << std::endl;
			std::cout << "It is interesting to see how calling functions is similar,\nyet it is different to include them\n";
			Chapter10_3_3_Helper::CallingManyImportedFunctions();
		}
	private:
	};
}
