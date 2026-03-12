#include "BorrowRecord.h"

#include <sstream>

using namespace std;

BorrowRecord::BorrowRecord() : bookId(0), memberId(0), issueDate(""), returnDate(""), fine(0) {}

BorrowRecord::BorrowRecord(int bookId, int memberId, const string &issueDate, const string &returnDate, int fine)
    : bookId(bookId), memberId(memberId), issueDate(issueDate), returnDate(returnDate), fine(fine) {}

int BorrowRecord::getBookId() const { return bookId; }

int BorrowRecord::getMemberId() const { return memberId; }

string BorrowRecord::getIssueDate() const { return issueDate; }

string BorrowRecord::getReturnDate() const { return returnDate; }

int BorrowRecord::getFine() const { return fine; }

int BorrowRecord::calculateFine(int daysBorrowed) const
{
    const int allowedDays = 7;
    const int finePerDay = 2;

    if (daysBorrowed <= allowedDays)
    {
        return 0;
    }

    return (daysBorrowed - allowedDays) * finePerDay;
}

void BorrowRecord::setReturnDate(const string &date) { returnDate = date; }

void BorrowRecord::setFine(int fineAmount) { fine = fineAmount; }

bool BorrowRecord::isReturned() const { return !returnDate.empty(); }

string BorrowRecord::toFileString() const
{
    ostringstream out;
    out << bookId << '|' << memberId << '|' << issueDate << '|' << returnDate << '|' << fine;
    return out.str();
}