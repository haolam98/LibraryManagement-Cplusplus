#pragma once
#include <string>
#include <vector>
using namespace std;
class book
{
public:
	book();

	void setBook(string name,string code, vector<string> info, bool status);
	void setRent(bool status);
	string getcode();
	string getname();
	vector<string> getinfo();
	bool isRent();
	~book();
private:
	string book_name;
	string book_code;
	vector<string> book_info;
	bool is_Rent;
};

