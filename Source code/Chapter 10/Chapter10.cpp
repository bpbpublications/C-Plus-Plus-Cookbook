#include <iostream> // only needed if we have output in this file

import Module10_1_1;
import BPBPublishing.CPP23Book.Chapter10_1_2;
import Module10_3_1;
import Module10_3_2;
import Module10_3_3;

static void SimpleImportWelcome() {
	WelcomeNS::Chapter10_3_1 chapter;
	chapter.GiveWelcome();
}

static void DerivedImportWelcome() {
	WelcomeNS::Chapter10_3_2 chapter;
	chapter.GiveWelcome();
}

static void CallingManyImportFunctions() {
	WelcomeNS::Chapter10_3_3 chapter;
	chapter.GiveWelcome();
}

import Chapter10_Reachability;

static void LookAtVisibility() {
	// NonExportedStruct badResult = CreateMyStruct(123);
	auto result = CreateMyStruct(42);
	int resultValue = result.MyValue;

	int resultExtraValue = result.AddOne();
}

import MyOveriewModuleName;

static void LookAtOverview() {
	MyModuleNS::MyClass c1;
	int x = c1.MyFunction();

	// MyFunctionWithHiddenImplementation();

	WelcomeNS::Chapter10_3_1 chapter;
	chapter.GiveWelcome();
}

import Module10_7_1;
import Module10_7_2;

static void LookAtImportingStandardModules() {
	Class10_7_1::UseStd();
	Class10_7_2::UseStdCompat();
}

void LookAtChapter10Topics()
{
	std::cout << "Examples in: " << __FILE__ << std::endl;
	// works with compiler?					when tested	clang	msvc	gcc
	Chapter10_1_1::GiveWelcome();		//	2023.11.25	part?	yes		part?
	Chapter10_1_2b::GiveWelcomeAgain();	//	2023.11.25	part?	yes		part?
	SimpleImportWelcome();				//	2023.11.25	part?	yes		part?
	DerivedImportWelcome();				//	2023.11.25	part?	yes		part?
	CallingManyImportFunctions();		//	2023.11.25	part?	yes		part?
	LookAtVisibility();					//	2023.11.25	part?	yes		part?
	LookAtOverview();					//	2023.11.25	part?	yes		part?
	LookAtImportingStandardModules();	//	2023.11.25	no		part	no
}
