//#include "pch.h"
#include "library.h"
#include <string>
#include <iostream>
using namespace std;
library::library()
{
	bookList = NULL;
	renterList = NULL;
}


library::~library()
{
}
bool library::isAvalable_4rent(string book_code)
{
	if (bookList == NULL)
	{
		return false;
	}
	NodeType*temp = bookList;

	while (temp != NULL)
	{
		if (book_code == temp->info.getcode())
		{
			return true;
		}
		else
		{
			temp = temp->next;
		}
	}
	return false;
}
string library::returnBookName(string id)
{
	if (bookList == NULL)
		return "";
	else
	{
		NodeType* temp = bookList;
		while (temp != NULL)
		{
			if (temp->info.getcode() == id)
			{
				return temp->info.getname();
			}
			temp = temp->next;
		}
	}
}
bool library::isHere(string book_name)
{
	//check if book exist in the library or not
	if (bookList == NULL)
		return false;
	NodeType* location = bookList;
	string currBook;
	while (location != NULL)
	{
		currBook = location->info.getname();
		if (currBook == book_name)
		{
			return true;
		}
		else
		{
			location = location->next;
		}
	}
	return false;
}

void library::insert_Book(book item) // base on category_code + name to order books
{
	//Case 0: First book in the list
	NodeType* newBook;
	newBook = new NodeType;
	newBook->info = item;
	newBook->next = NULL;
	if (bookList == NULL)
	{
		bookList= newBook;
	}
	else
	{
		NodeType * curr = bookList;
		string currentBook = curr->info.getcode();
		int compare = item.getcode().compare(currentBook);

		//Case 1: insert book as a head
		if (compare < 0)
		{
			newBook->next = curr;
			bookList == newBook;
		}

		//Case 2: insert in the middle
		else
		{
			NodeType *prev = bookList;
			curr = curr->next;
			while (curr!=NULL)
			{
				compare = item.getcode().compare(currentBook);
				currentBook = curr->info.getcode();
				compare = item.getcode().compare(currentBook);
				if (compare == 0) //two book are same, do nothing
				{
					return;
				}
				else if (compare < 0)
				{
					prev->next = newBook;
					newBook->next = curr;
					return;
				}
				prev = curr;
				curr = curr->next;
			}

		//Case 3: Insert last
			//after loop, prev is last node
			prev->next = newBook;
		}

	}
}
void library::delete_book(string id)
{
	if (bookList == NULL)
		return;
	// 1st book is the one
	if (bookList->info.getcode() == id)
	{
		NodeType* temp = bookList;
		bookList = bookList->next;
		delete temp;
	}
	else
	{
		NodeType* prev = bookList;
		NodeType* location = bookList->next;
		string currBook;

		while (location != NULL)
		{
			currBook = location->info.getcode();
			if (currBook == id)
			{
				prev->next = location->next;
				delete location;
				return;
			}
			else
			{
				prev = location;
				location = location->next;
			}
		}
	}
}
void library::printBook_info(string name)
{
	if (bookList == NULL)
		return;
	if (name == "")
		return;
	NodeType* temp = bookList;
	vector<string> bookinfo;
	while (temp != NULL)
	{
		if (temp->info.getname() == name)
		{
			cout << "-------- " << name << " ---------" << endl;
			cout << temp->info.getcode() << endl;
			bookinfo= temp->info.getinfo();
			for (int i = 0; i < bookinfo.size(); i++)
			{
				cout<< bookinfo.at(i) << endl;
			}
			cout << "------------------------------------------------------------" << endl << endl;
			return;
		}
		else
		{
			temp = temp->next;
		}
	}
	cout << "\n>>>Cannot Dectect The Book! " << endl;
}

void library::markRentStatus(string book_name, bool isRent)
{ // mark the book as rented or not base on isRent
	if (bookList == NULL)
		return;
	NodeType* location = bookList;
	string currBook;
	while (location != NULL)
	{
		currBook = location->info.getname();
		if (currBook == book_name)
		{
			location->info.setRent(isRent);
		}
		else
		{
			location = location->next;
		}
	}
}
void library::add_renter(renter item)
{
	NodeType2* newRenter = new NodeType2;
	newRenter->info = item;
	newRenter->next = NULL;
	if (renterList == NULL)
	{
		renterList = newRenter;
	}
	else
	{
		NodeType2* curr = renterList;
		string currRenter = curr->info.get_netID();
		int compare = item.get_renterName().compare(currRenter);
		if (compare < 0)
		{
			newRenter->next = curr;
			renterList == newRenter;
		}

		//Case 2: insert in the middle
		else
		{
			NodeType2 *prev = renterList;
			curr = curr->next;
			while (curr != NULL)
			{
				currRenter = curr->info.get_netID();
				compare = item.get_netID().compare(currRenter);
				if (compare == 0)
				{
					return;
				}
				else if (compare < 0)
				{
					prev->next = newRenter;
					newRenter->next = curr;
					return;
				}
				prev = curr;
				curr = curr->next;
			}

			//Case 3: Insert last
				//after loop, prev is last node
			prev->next = newRenter;
		}
	}

}
void library::delete_renter(string id) 
{// delete renter base from id , since name could be the same
	if (renterList == NULL)
		return;

	// 1st renter is the one
	if (renterList->info.get_netID()== id)
	{
		NodeType2* temp = renterList;
		renterList = renterList->next;
		delete temp;
	}
	else
	{
		NodeType2* prev = renterList;
		NodeType2* location = renterList->next;
		string currRenter;

		while (location != NULL)
		{
			currRenter = location->info.get_netID();
			if (currRenter == id)
			{
				prev->next = location->next;
				delete location;
				return;
			}
			else
			{
				prev = location;
				location = location->next;
				
			}
		}
	}
}
bool library::find_renter(string id, renter &item)
{
	//+ return true/false for renter exist in the system or not
	//+ pass by reference renter's info if found. 
	if (renterList == NULL)
	{
		return false;
	}
	else
	{
		NodeType2* temp = renterList;
		while (temp!=NULL)
		{
			
			if (temp->info.get_netID() == id)
			{
				item = temp->info;
				return true;
			}
			temp = temp->next;
		}
	}
	return false;

}
void library::printBook_byCatg(string catg) //Print all book follow by the category
{
	if (bookList == NULL)
	{
		return;
	}
	else
	{
	
		NodeType *temp = bookList;
		string code;
		while (temp!=NULL)
		{
			code = temp->info.getcode().substr(0, 4);
			if (code == catg)
			{
				//print the book_info
				printBook_info(temp->info.getname());
			}
			temp = temp->next;
			

		}
	}
}
