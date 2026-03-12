#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

#include "Book.h"
#include "Member.h"

class Library
{
private:
    std::vector<Book> books;
    std::vector<Member> members;

    const std::string booksFile = "books.txt";
    const std::string membersFile = "members.txt";

    void loadBooks();
    void saveBooks() const;
    void loadMembers();
    void saveMembers() const;

    bool isBookIdExists(int id) const;
    bool isMemberIdExists(int id) const;

public:
    Library();

    void addBook();
    void displayBooks() const;
    void searchBook() const;
    void deleteBook();
    void addMember();
    void displayMembers() const;
    void issueBook();
    void returnBook();
};

#endif
