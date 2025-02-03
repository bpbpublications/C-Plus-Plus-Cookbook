// about to talk about our module
// and its components
module;

// \/ \/ \/ \/ \/ \/ \/ \/
// 
// global module fragment
//

#define CanHaveDefineThatIsSeenOnlyInThisModule 123

#include <cassert>
//
// /\ /\ /\ /\ /\ /\ /\ /\.

export module MyOveriewModuleName;

// \/ \/ \/ \/ \/ \/ \/ \/
// 
// module preamble
//
import <iostream>;
import <string>;
export import Module10_3_1;
//
// /\ /\ /\ /\ /\ /\ /\ /\.

// \/ \/ \/ \/ \/ \/ \/ \/
// 
// module purview
//
export namespace MyModuleNS {
	class MyClass {
	public:
		int MyFunction() const { return 42; }
	};
}

export void MyFunctionWithHiddenImplementation();

//
// /\ /\ /\ /\ /\ /\ /\ /\.

// \/ \/ \/ \/ \/ \/ \/ \/
// 
// private module fragment
//
// /\ /\ /\ /\ /\ /\ /\ /\.
module: private;
struct secretImplementation {
	// ...
};

void MyFunctionWithHiddenImpementation() {
	std::cout << "C++23 is great!";
}
