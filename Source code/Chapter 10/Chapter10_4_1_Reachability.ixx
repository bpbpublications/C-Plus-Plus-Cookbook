export module Chapter10_Reachability;

struct NonExportedStruct {
	int MyValue;

	int AddOne() const {
		return MyValue + 1;
	}
private:
	void MySecretFunction() {}
};

export NonExportedStruct CreateMyStruct(int input) {
	NonExportedStruct result;
	result.MyValue = input;
	return result;
}
