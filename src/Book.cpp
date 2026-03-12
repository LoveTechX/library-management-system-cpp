#include "Book.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

Book::Book() : id(0), title(""), author(""), issued(false) {}

Book::Book(int id, const string &title, const string &author, bool issued)
    : id(id), title(title), author(author), issued(issued) {}

void Book::inputBook()
{
    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    issued = false;
}

void Book::inputBookWithoutId()
{
    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    issued = false;
}

void Book::displayBook() const
{
    cout << left << setw(8) << id
         << setw(30) << title
         << setw(25) << author
         << setw(12) << (issued ? "Issued" : "Available") << '\n';
}

int Book::getId() const { return id; }

string Book::getTitle() const { return title; }

string Book::getAuthor() const { return author; }

bool Book::isIssued() const { return issued; }

void Book::setId(int newId) { id = newId; }

void Book::setIssued(bool status) { issued = status; }

string Book::toFileString() const
{
    ostringstream out;
    out << id << '|' << title << '|' << author << '|' << issued;
    return out.str();
}
