// CS301-01: Data Structure & Algorithms
// Project: Library Management
// Group 3: Hao, Ming, Jose
// Library System Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include <time.h>
//#include <ctime>
//#include "pch.h"
#include <iostream>
#include "book.h"
#include "library.h"
#include "renter.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
void book_searchbyCatg(library &list);
void book_searchbyBook(library &list);
void book_search(library &list);
void book_addnew(library &list);
void book_takeout(library &list, bool for_rent,string id,string renter_name);
void book_checkin(library &list, string id);
void adminService(library &list);
void studentService(library &list,string id);
string todayDate;
int main()
{
	// read .txt file → insert books to library
	library list;
	string info, book_name, book_code;
	
	ifstream infile;
	infile.open("booklist.txt");
	cout << "-->OPEN FILE FILE COMPLETED!" << endl;
	cout << "-->Start reading books..." << endl;
	while (!infile.eof())
	{
		//read from file
		vector <string> book_info;
		getline(infile, book_name); //read name
		getline(infile, book_code); // read code
		do							// read info
		{
			getline(infile, info);
			book_info.push_back(info);
		} while (info != "*****");
		book_info.pop_back(); // pop the line "*****"
		//set book
		
		book input;
		input.setBook(book_name,book_code, book_info, false);
		cout << "--> Inserting books..." << endl;
		//add book to library
		list.insert_Book(input);
		cout << input.getcode() << "-->INSERTED" << endl;
	}
	infile.close();//close file
	cout << "-->IN-PUT FILE COMPLETED!" << endl << endl;
	//Add sample renter.
	renter p2;
	vector<string>bookrent;
	string book = "HIST-1111";
	bookrent.push_back(book);
	p2.setRenterInfo("Hao Lam", "ef3628", 5, "05/01/2019", bookrent);
	list.add_renter(p2);
	
	// library services:
	// +Admin: add, delete, search bool
	// +Student:
		// + book renting/ book checkout
		// + book info/ book search
		// + book return/ book check-in
		// +library info: cout min/max day for rent( maybe have this value at 14 day period),
		//late fees( $1.50 a day/per day until book is returned), 
		//max book for rent per renter (this I am assuming would be max times a book can be renewed and maybe we can set this at 3 times)

	cout << endl;
	cout << "/////// LIBRARY SYSTEM ///////" << endl<<endl;
	string id;

		cout << "Enter your ID: " << endl;
		//ID rule: admin-> first 2 char is "ad", else is student
		cout << "-> ";
		getline(cin, id);
		if (id[0] == 'a'&& id[1] == 'd')
		{
			cout << "\n-->ADMIN Log-In---" << endl << endl;
			adminService(list);
		}
		else
		{
			cout << "\n-->STUDENT Log-In---" << endl << endl;
			studentService(list, id);
		}
		
	cout << "___________________EXIT LIBRARY SYSTEM_________________" << endl;
}

void adminService(library &list)
{
	cout << "-------------ADMIN SERVICES-------------" << endl << endl;
	int opt;
	do
	{
		do
		{
			cout << "Options:\n";
			cout << "1. Add Book\n";
			cout << "2. Delete Book\n";
			cout << "3. Book Search:\n";
			cout << "Please choose your option: " << endl;
			cout << "-> ";
			cin >> opt;
		} while (opt < 0 || opt>3);
		if (opt == 1)
		{
			book_addnew(list);
		}
		else if (opt == 2)
		{
			book_takeout(list, false, "", "");
		}
		else
		{
			book_search(list);
		}
		cout<<"Enter 0 for exit, 1 for choose other services: " << endl;
		cout << "-> ";
		cin >> opt;
	} while (opt == 1);

}
void studentService(library &list, string id)
{
	cout << "-------------STUDENT SERVICES-------------" << endl << endl;
	cout << "Enter today date (mm/dd/yy): " << endl;
	cout << "-> ";
	getline(cin, todayDate);
	

	string name;
	cout << "Please enter your name: " << endl;
	cout << "-> ";
	getline(cin, name);
	int opt;
	do
	{
		do
		{
			cout << "\nOptions:\n";
			cout << "1. Rent Books\n";
			cout << "2. Check-in books\n";
			cout << "3. Book Search:\n";
			cout << "Please choose your option: " << endl;
			cout << "-> ";
			cin >> opt;
		} while (opt < 0 || opt>3);
		if (opt == 1)
		{
			book_takeout(list, true, id, name);
		}
		else if (opt == 2)
		{
			book_checkin(list, id);
		}
		else
		{
			book_search(list);
		}
		cout << "Enter 0 for exit, 1 for choose other services: " << endl;
		cout << "-> ";
		cin >> opt;
		cout << "------------------------------------------------------------" << endl;
	} while (opt == 1);


}
void book_takeout(library &list, bool for_rent, string id, string renter_name)
{
	// 2 cases of book taking out:
	/*
		+ Admin delete book -> permenantly delete book out of list
		+ Student rent book -> check status-> fix renting status if needed ;
	*/

	int num = 0;
	do
	{
		cout << "\nHow many book: " << endl;
		cout << "-> ";
		cin >> num;
	} while (num < 0);
	if (num == 0)
	{
		cout << "0 book is required" << endl;
	}
	else
	{
		vector <string> bookcode;
		string idbook;
		cin.ignore();
		cout << "Enter book ID: " << endl;
		for (int i = 0; i < num; i++)
		{
			cout<<"-> "<< i+1<<" : ";
			getline(cin, idbook);
			bookcode.push_back(idbook);
		}
		cout << "\n>>>Searching in the system....\n ";
		//CASE 1: Admin-> delete books
		if (!for_rent)
		{
			for (int i = 0; i < num; i++)
			{
				cout << "\n>>>Find and Deleting..." << bookcode.at(i) << endl;
				list.delete_book(bookcode.at(i));
			}
			cout << "\nCOMPLETE!" << endl;
		}
		//CASE 2: Student-> create renter, book mark "rented" 
		else 
		{
			short dayrent;
			string dateRent;
			do
			{
				cout << "You will rent for how many days? (No longer than 30 days)" << endl;
				cout << "-> ";
				cin >> dayrent;
			} while (dayrent > 30);

			renter p1;
			bool check;
			string name;
			for (int i = 0; i < num; i++)
			{
				//check book is exist in library or not
				name = list.returnBookName(bookcode.at(i));
				check = list.isHere(name);
				if (!check)
				{
					cout << bookcode.at(i) << " IS NOT EXIST!!" << endl;
					bookcode.erase(bookcode.begin() + i);
				}
				//check book's availibility 
				else
				{
					check = list.isAvalable_4rent(bookcode.at(i));
					if (check == true)
					{
						list.markRentStatus(bookcode.at(i), true);
						cout << bookcode.at(i) << "-->RENTED";
					}
					else
						cout << bookcode.at(i) << " currently is not available!" << endl;
				}
			}
			//Finalize renter's info
			p1.setRenterInfo(renter_name, id, dayrent, todayDate, bookcode);
			list.add_renter(p1);
			cout << "\n\n>>>Renter Confirmation:" << endl;
			cout << renter_name << "\nnetID: " << id << endl;
			cout << "Number of day for rent: " << dayrent <<endl;
			cout << "Book Check-out: " << bookcode.size() << endl;
			for (int i = 0; i < bookcode.size(); i++)
			{
				cout << bookcode.at(i) << endl;
			}

		}
		
	}
	cout << "------------------------------------------------------------"<<endl;

}
void book_addnew(library &list)
{
	//Admin add new books
	cout << "\n--------------------ADD NEW BOOK------------------------------" << endl;
	int num = 0;
	do
	{
		cout << "\nHow many books: " << endl;
		cout << "-> ";
		cin >> num;
	} while (num < 0);
	cin.ignore();
	if (num == 0)
	{
		cout << "0 book is required" << endl;
	}
	else
	{
		vector <string> bookname;
		string name;
		string code;
		cout << "Enter book name: " << endl;
		for (int i = 0; i < num; i++)
		{
			cout << "-> " << i+1 << " : ";
			getline(cin, name);
			bookname.push_back(name);
		}

		for (int i = 0; i < num; i++)
		{
			cout << "\n>>>Adding..." << bookname.at(i) << endl;
			cout << "Please add book code: " << endl;
			cout << "->";
			getline(cin, code);
			cout << "Please give the book info (end with '*****'): " << endl;
			cout << "-> ";
			vector<string> book_info;
			string info;
			do
			{
				getline(cin, info);
				book_info.push_back(info);
			} while (info != "*****");
			cout << "\n>>>Book info is added!" << endl;
			// creat new book
			book newbook;
			newbook.setBook(bookname.at(i),code, book_info, false);
			list.insert_Book(newbook);
		}
		cout << "\nCOMPLETE!" << endl;
	}
	cout << "------------------------------------------------------------" << endl;
}
void book_checkin(library &list, string id)
{
	
	/*
		Student check-in book -> fix book mark "for rent" only;

	*/
	cout << ">>>Checking netID..." << endl;
	renter p1;
	bool check;
	check=list.find_renter(id,p1);
	if (!check)
	{
		cout << "...CANNOT find your info in the System!" << endl;
	}
	else
	{
		string answer;
		vector<string> bookReturn = p1.get_bookRented();
		cout << "\n------------------------------------------------------------" << endl;
		cout << ">>>Renter Info:" << endl;
		cout << p1.get_renterName() << "\t" << p1.get_netID() << endl;
		cout << "List of book have rented: " << endl;
		for (int i = 0; i < bookReturn.size(); i++)
		{
			cout <<i+1<<". "<< bookReturn.at(i) << endl;
		}
		cout << "Date rent: " << p1.get_rentDate() << endl;
		cout << "Number of day in rent: " << p1.get_day4rent() << endl;
		cin.ignore();
		cout << "\n------------------------------------------------------------" << endl;
		cout << "\nAre you going to check-in books today? (yes/no)" << endl;
		cout << "-> ";
		getline(cin, answer);
		if (answer == "yes")
		{
			int dayrent = 0;
			int lateday = 0;
			cout << "How many day did you rent? " << endl;
			cout << "-> ";
			cin >> dayrent;
			//Renter return books-->Update book status again...
			cout << "\n------------------------------------------------------------" << endl;
			cout << ">>>System checking-in books..." << endl;
			
			for (int i = 0; i < bookReturn.size(); i++)
			{
				// mark book as False -> available for rent
				list.markRentStatus(bookReturn.at(i), false);
				cout << bookReturn.at(i) << " -->CHECKED-IN" << endl;
			}
			//Check for late days
			
			bool late_check = p1.is_Late(dayrent,lateday);

			if (late_check==false) //not late
			{
				cout << "\n*Thank you for return books on time! No late-fee required." << endl;
			}
			else
			{
				cout << "You are late for " << lateday << " days!" << endl;
				cout << "Unfortunately, you have to pay for the late fee: $" << p1.get_lateFee() << endl;
			}
			list.delete_renter(id);
		}
	}
		
			

	cout << "------------------------------------------------------------" << endl;
}
void book_search(library &list)
{
	//Finding book, printing info, offer renting status
	cout << "------------------------------------------------------------" << endl;
	cin.ignore();
	int opt;
	do
	{
		cout << "You want to search by: ";
		cout << "\n\t#1. By Book Title\n\t#2. By Categories" << endl;
		cout << "(Enter your option (by number 1 or 2)" << endl;
		cout << "-> ";
		cin >> opt;
	} while (opt > 2 || opt < 0);
	switch (opt)
	{
	case 1:
	{
		book_searchbyBook(list);
		break;
	}
	case 2:
	{
		book_searchbyCatg(list);
		break;
	}		
	default:
		break;
	}
	
}
void book_searchbyCatg(library &list)
{
	string answer;
	int opt;
	bool check;
	cout << "------------------------------------------------------------" << endl;
	do
	{
		cout << "There are 3 categories in the system:" << endl;
		cout << "\n1. Mathematics";
		cout << "\n2. English";
		cout << "\n3. Economics";
		cout << "\n4. History" << endl;
		cout << "\nPlease enter your choice: " << endl;
		cout << "-> ";
		cin >> opt;
	}
	while (opt > 4 || opt < 0);
	if (opt == 1)
	{
		answer = "MATH";
		cout << ">>>Book list fall under category Mathematics: " << endl;
		list.printBook_byCatg(answer);
	}
	else if (opt == 2)
	{
		answer = "ENGL";
		cout << ">>>Book list fall under category English: " << endl;
		list.printBook_byCatg(answer);
	}
	else if (opt == 3)
	{
		answer = "ECON";
		cout << ">>>Book list fall under category History: " << endl;
		list.printBook_byCatg(answer);
	}
	else
	{
		answer = "HIST";
		cout << ">>>Book list fall under category History: " << endl;
		list.printBook_byCatg(answer);
	}
	cin.ignore();
	cout << "\nSearch for book details? (enter yes/no)" << endl;
	cout << "-> ";
	getline(cin, answer);
	if (answer == "yes")
	{
		book_searchbyBook(list);
	}
	cout << "------------------------------------------------------------" << endl;
}

void book_searchbyBook(library &list)
{
	string answer;
	bool check;
	cout << "------------------------------------------------------------" << endl;
	cin.ignore();
	do
	{
		cout << "\nEnter name of the book: " << endl;
		cout << "-> ";
		getline(cin, answer);
		if (list.isHere(answer)==true)
		{
			if (list.isAvalable_4rent(answer))
			{
				cout << "\n--->THIS BOOK IS AVAILABLE FOR RENT----" << endl << endl;
				list.printBook_info(answer);
			}
		}
		else
		{
			cout << "Sorry! " << answer << " is not in the library" << endl;
		}
		cout << "Do you want to search for another one? (enter yes/no): " << endl;
		cout << "-> ";
		getline(cin, answer);

	} while (answer == "yes");
	cout << "------------------------------------------------------------" << endl;
}