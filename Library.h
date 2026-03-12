#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

#include "BorrowRecord.h"
#include "Book.h"
#include "Member.h"

class Library
{
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<BorrowRecord> borrowRecords;

    const std::string booksFile = "books.txt";
    const std::string membersFile = "members.txt";
    const std::string borrowRecordsFile = "borrow_records.txt";

    void loadBooks();
    void saveBooks() const;
    void loadMembers();
    void saveMembers() const;
    void loadBorrowRecords();
    void saveBorrowRecords() const;

    bool isBookIdExists(int id) const;
    bool isMemberIdExists(int id) const;
    std::string getCurrentDate() const;
    std::string getBookTitleById(int id) const;
    std::string getMemberNameById(int id) const;

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
    void displayIssuedBooks() const;
};

#endif
