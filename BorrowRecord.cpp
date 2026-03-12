#include "BorrowRecord.h"

#include <sstream>

using namespace std;

BorrowRecord::BorrowRecord() : bookId(0), memberId(0), issueDate(""), returnDate("") {}

BorrowRecord::BorrowRecord(int bookId, int memberId, const string &issueDate, const string &returnDate)
    : bookId(bookId), memberId(memberId), issueDate(issueDate), returnDate(returnDate) {}

int BorrowRecord::getBookId() const { return bookId; }

int BorrowRecord::getMemberId() const { return memberId; }

string BorrowRecord::getIssueDate() const { return issueDate; }

string BorrowRecord::getReturnDate() const { return returnDate; }

void BorrowRecord::setReturnDate(const string &date) { returnDate = date; }

bool BorrowRecord::isReturned() const { return !returnDate.empty(); }

string BorrowRecord::toFileString() const
{
    ostringstream out;
    out << bookId << '|' << memberId << '|' << issueDate << '|' << returnDate;
    return out.str();
}