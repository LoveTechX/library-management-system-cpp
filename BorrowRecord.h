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

public:
    BorrowRecord();
    BorrowRecord(int bookId, int memberId, const std::string &issueDate, const std::string &returnDate);

    int getBookId() const;
    int getMemberId() const;
    std::string getIssueDate() const;
    std::string getReturnDate() const;

    void setReturnDate(const std::string &date);
    bool isReturned() const;
    std::string toFileString() const;
};

#endif