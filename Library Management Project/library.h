#pragma once
#include "book.h"
#include "renter.h"
#include <string>
using namespace std;
struct NodeType
{
	book info;
	NodeType* next;
};
struct NodeType2
{
	renter info;
	NodeType2* next;
};

class library
{
public:
	library();
	~library();
	// For book: 

	bool isAvalable_4rent(string book_code); // check if book is rent or not
	bool isHere(string book_name); //search book, return true/false indicate book exist in library or not
	void markRentStatus(string book_name, bool isRent); //update book status base on "isRent"
	void insert_Book(book item); // base on category_code + name to order books
	void delete_book(string id);
	string returnBookName(string id);
	// For renter: 
	bool find_renter(string id, renter &item);
	//+ return true/false for renter exist in the system or not
	//+ pass by reference renter's info if found. 
	void add_renter(renter item);
	void delete_renter(string id); // delete renter base from id , since name could be the same

	// For book_search
	void printBook_info(string name);
	void printBook_byCatg(string catg); //Print all book follow by the category

private:
	NodeType *bookList; // pointer point the head list of the book
	NodeType2* renterList; //pointer point to the head of renters list
};