#include "RealEstate.cpp"
#include "calculator.cpp"
class User {
public:
	bool hasPrivileges;
	RealEstate possession;

	void PrintAllInfo() {} //! Предупредить
	void GetTax() {}
	User SearchByUserName(string nameToFind) {}
	User SearchByTax(double tax) {}
	User SearchByPasword(int password) {}
	void SortByTax(vector<User> users) {}
	void SortByTaxDescending(vector<User> users) {}
	void SortByPasword(vector<User> users) {}
	void SortByPaswordDescending(vector<User> users) {}
	void Menu(vaector<User> users) {}
}