#ifdef DOES_NOT_COMPILE
export module Chapter10_6_1_BadCyclic2;

import Chapter10_6_1_BadCyclic1;

struct FirstType;
export struct SecondType { FirstStruct* pFirst; };
#endif
