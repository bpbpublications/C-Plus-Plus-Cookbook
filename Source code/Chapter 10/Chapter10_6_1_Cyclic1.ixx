#ifdef DOES_NOT_COMPILE
export module Chapter10_6_1_BadCyclic1;

import Chapter10_6_1_BadCyclic2;

struct SecondType;
export struct FirstStruct { SecondType* pSecond; };
#endif
