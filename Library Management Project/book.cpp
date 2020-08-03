//#include "pch.h"
#include "book.h"
#include <string>
#include <vector>
using namespace std;
book::book()
{
}

void book::setBook(string name, string code, vector<string> info, bool status)
{
	book_name = name;
	book_code = code;
	for (int i = 0; i < info.size(); i++)
	{
		//pushing line by line
		book_info.push_back(info.at(i));
	}
	is_Rent = status;
}
void book::setRent(bool status)
{
	is_Rent = status;
}
string book::getcode()
{
	return book_code;
}
string book::getname()
{
	return book_name;
}
vector<string> book::getinfo()
{
	return book_info;
}
bool book::isRent()
{
	return is_Rent;
}
book::~book()
{
}
