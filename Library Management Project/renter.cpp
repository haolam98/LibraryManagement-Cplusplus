//#include "pch.h"
#include "renter.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
renter::renter()// constructor should initialize is date_return, isLate, late_fee 
{
	renter_name = "";
	date_rent = "";
	day_rent = 0;
	isLate = false;
	late_fee = 0;
	netID = "";
	
}


renter::~renter()

{

}

void renter::setRenterInfo(string name, string id, int dayRent, string dateRent, vector<string> bookrent) //initialize
{
	renter_name = name;
	date_rent = dateRent;
	day_rent = dayRent;
	isLate = false;
	late_fee = 0;
	netID = id;
	bookRented = bookrent;

}

bool renter::is_Late(int numDayReturn, int&late) // checking late return
{
	if (numDayReturn > day_rent)
	{
		late = numDayReturn - day_rent;
		late_fee = late*1.50;
		return true;
	}
	return false;

}
vector<string> renter::get_bookRented()
{
	return bookRented;
}

string renter::get_renterName()
{
	return renter_name;
}
string renter::get_netID()
{
	return netID;
}
string renter::get_rentDate()
{
	return date_rent;
}
int renter::get_day4rent()
{
	return day_rent;
}

float renter::get_lateFee()
{
	return late_fee;
}
