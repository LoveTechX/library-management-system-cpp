#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>

class BorrowRecord
{
private:
    int bookId;
    int memberId;
    std::string issueDate;
    std::string returnDate;
    int fine;

public:
    BorrowRecord();
    BorrowRecord(int bookId, int memberId, const std::string &issueDate, const std::string &returnDate, int fine = 0);

    int getBookId() const;
    int getMemberId() const;
    std::string getIssueDate() const;
    std::string getReturnDate() const;
    int getFine() const;

    int calculateFine(int daysBorrowed) const;

    void setReturnDate(const std::string &date);
    void setFine(int fineAmount);
    bool isReturned() const;
    std::string toFileString() const;
};

#endif