#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    int id;
    std::string title;
    std::string author;
    bool issued;

public:
    Book();
    Book(int id, const std::string &title, const std::string &author, bool issued);

    void inputBook();
    void inputBookWithoutId();
    void displayBook() const;

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    bool isIssued() const;

    void setId(int newId);
    void setIssued(bool status);
    std::string toFileString() const;
};

#endif
