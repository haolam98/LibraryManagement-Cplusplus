#pragma once
#include<vector>
#include <string>

using namespace std;
class renter
{
public:
	renter(); // constructor should initialize is date_return, isLate, late_fee 
	~renter();
	void setRenterInfo(string name, string id, int dayRent, string dateRent, vector<string> bookrent); //initialize
	string get_renterName();
	string get_netID();
	string get_rentDate();
	vector<string> get_bookRented(); // return the rented book list
	int get_day4rent(); // how many day renter will rent the  book
	bool is_Late(int numDayReturn, int &late); // checking late return, calculate late_date+ lateFee
	float get_lateFee();	//fee need to pay for late return 


private:
	string renter_name;
	string date_rent; 	//the date rent the book; should in form xx/xx/xx can easy to 
							//keep track for late fee
	int day_rent;		// will rent the book for how many day
	bool isLate; 		//late return flag
	float late_fee;		//late fee
	string netID;
	vector<string> bookRented; //name of rented books
};