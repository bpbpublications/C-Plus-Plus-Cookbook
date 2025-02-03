export module Chapter10_6_2_CyclicSolution;

struct FirstStruct;
export struct SecondType { FirstStruct* pFirst; };
export struct FirstStruct { SecondType* pSecond; };
