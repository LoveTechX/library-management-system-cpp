#include "Library.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

namespace
{
    int calculateDaysBetween(const string &startDate, const string &endDate)
    {
        tm startTime = {};
        tm endTime = {};

        istringstream startStream(startDate);
        istringstream endStream(endDate);

        startStream >> get_time(&startTime, "%Y-%m-%d");
        endStream >> get_time(&endTime, "%Y-%m-%d");

        if (startStream.fail() || endStream.fail())
        {
            return 0;
        }

        // Use noon to avoid daylight saving edge cases when converting to time_t.
        startTime.tm_hour = 12;
        endTime.tm_hour = 12;

        time_t start = mktime(&startTime);
        time_t end = mktime(&endTime);

        if (start == -1 || end == -1)
        {
            return 0;
        }

        double seconds = difftime(end, start);
        if (seconds < 0)
        {
            return 0;
        }

        return static_cast<int>(seconds / (60 * 60 * 24));
    }
}

void Library::loadBooks()
{
    ifstream fin(booksFile);
    if (!fin)
    {
        return;
    }

    books.clear();
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string idStr, title, author, issuedStr;

        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, issuedStr, '|');

        if (idStr.empty() || title.empty() || author.empty() || issuedStr.empty())
        {
            continue;
        }

        int id = stoi(idStr);
        bool issued = (issuedStr == "1" || issuedStr == "true");
        books.push_back(Book(id, title, author, issued));
    }
}

void Library::saveBooks() const
{
    ofstream fout(booksFile);
    for (size_t i = 0; i < books.size(); ++i)
    {
        fout << books[i].toFileString() << '\n';
    }
}

void Library::loadMembers()
{
    ifstream fin(membersFile);
    if (!fin)
    {
        return;
    }

    members.clear();
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string idStr, name;

        getline(ss, idStr, '|');
        getline(ss, name, '|');

        if (idStr.empty() || name.empty())
        {
            continue;
        }

        int id = stoi(idStr);
        members.push_back(Member(id, name));
    }
}

void Library::saveMembers() const
{
    ofstream fout(membersFile);
    for (size_t i = 0; i < members.size(); ++i)
    {
        fout << members[i].toFileString() << '\n';
    }
}

void Library::loadBorrowRecords()
{
    ifstream fin(borrowRecordsFile);
    if (!fin)
    {
        return;
    }

    borrowRecords.clear();
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string bookIdStr, memberIdStr, issueDate, returnDate, fineStr;

        getline(ss, bookIdStr, '|');
        getline(ss, memberIdStr, '|');
        getline(ss, issueDate, '|');
        getline(ss, returnDate, '|');
        getline(ss, fineStr, '|');

        if (bookIdStr.empty() || memberIdStr.empty() || issueDate.empty())
        {
            continue;
        }

        int fine = 0;
        if (!fineStr.empty())
        {
            fine = stoi(fineStr);
        }

        borrowRecords.push_back(BorrowRecord(stoi(bookIdStr), stoi(memberIdStr), issueDate, returnDate, fine));
    }
}

void Library::saveBorrowRecords() const
{
    ofstream fout(borrowRecordsFile);
    for (size_t i = 0; i < borrowRecords.size(); ++i)
    {
        fout << borrowRecords[i].toFileString() << '\n';
    }
}

bool Library::isBookIdExists(int id) const
{
    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

bool Library::isMemberIdExists(int id) const
{
    for (size_t i = 0; i < members.size(); ++i)
    {
        if (members[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

string Library::getCurrentDate() const
{
    time_t now = time(nullptr);
    tm timeInfo{};
    localtime_s(&timeInfo, &now);

    ostringstream out;
    out << put_time(&timeInfo, "%Y-%m-%d");
    return out.str();
}

string Library::getBookTitleById(int id) const
{
    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getId() == id)
        {
            return books[i].getTitle();
        }
    }

    return "Unknown Book";
}

string Library::getMemberNameById(int id) const
{
    for (size_t i = 0; i < members.size(); ++i)
    {
        if (members[i].getId() == id)
        {
            return members[i].getName();
        }
    }

    return "Unknown Member";
}

string Library::generateBookId()
{
    ostringstream oss;
    oss << "B" << nextBookId;
    nextBookId++;
    return oss.str();
}

string Library::generateMemberId()
{
    ostringstream oss;
    oss << "M" << nextMemberId;
    nextMemberId++;
    return oss.str();
}

Library::Library()
{
    nextBookId = 1001;
    nextMemberId = 2001;

    loadBooks();
    loadMembers();
    loadBorrowRecords();

    // Update nextBookId based on existing books
    for (size_t i = 0; i < books.size(); ++i)
    {
        int bookNumId = books[i].getId();
        // Extract numeric part from ID if it's numeric
        if (bookNumId >= 1001)
        {
            if (bookNumId >= nextBookId)
            {
                nextBookId = bookNumId + 1;
            }
        }
    }

    // Update nextMemberId based on existing members
    for (size_t i = 0; i < members.size(); ++i)
    {
        int memberNumId = members[i].getId();
        // Extract numeric part from ID if it's numeric
        if (memberNumId >= 2001)
        {
            if (memberNumId >= nextMemberId)
            {
                nextMemberId = memberNumId + 1;
            }
        }
    }
}

void Library::addBook()
{
    Book b;
    string bookId = generateBookId();

    // Extract numeric part for storage
    int numericId = stoi(bookId.substr(1));
    b.setId(numericId);

    b.inputBookWithoutId();

    books.push_back(b);
    saveBooks();
    cout << "Book added successfully\n";
    cout << "Book ID: " << bookId << "\n";
}

void Library::displayBooks() const
{
    if (books.empty())
    {
        cout << "No books found.\n";
        return;
    }

    cout << "\n==================== BOOK LIST ====================\n";
    cout << left << setw(8) << "ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(12) << "Status" << '\n';
    cout << string(75, '-') << '\n';

    for (size_t i = 0; i < books.size(); ++i)
    {
        books[i].displayBook();
    }
}

void Library::searchBook() const
{
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;

    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getId() == id)
        {
            cout << "\nBook found:\n";
            cout << left << setw(8) << "ID"
                 << setw(30) << "Title"
                 << setw(25) << "Author"
                 << setw(12) << "Status" << '\n';
            cout << string(75, '-') << '\n';
            books[i].displayBook();
            return;
        }
    }

    cout << "Book not found.\n";
}

void Library::deleteBook()
{
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getId() == id)
        {
            books.erase(books.begin() + static_cast<long long>(i));
            saveBooks();
            cout << "Book deleted successfully.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

void Library::addMember()
{
    Member m;
    string memberId = generateMemberId();

    // Extract numeric part for storage
    int numericId = stoi(memberId.substr(1));
    m.setId(numericId);

    m.inputMemberWithoutId();

    members.push_back(m);
    saveMembers();
    cout << "Member added successfully\n";
    cout << "Member ID: " << memberId << "\n";
}

void Library::displayMembers() const
{
    if (members.empty())
    {
        cout << "No members found.\n";
        return;
    }

    cout << "\n=========== MEMBER LIST ===========\n";
    cout << left << setw(10) << "ID" << setw(30) << "Name" << '\n';
    cout << string(40, '-') << '\n';

    for (size_t i = 0; i < members.size(); ++i)
    {
        members[i].displayMember();
    }
}

void Library::issueBook()
{
    int memberId;
    int bookId;

    cout << "Enter Member ID: ";
    cin >> memberId;
    if (!isMemberIdExists(memberId))
    {
        cout << "Member not found. Add member first.\n";
        return;
    }

    cout << "Enter Book ID to issue: ";
    cin >> bookId;

    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getId() == bookId)
        {
            if (books[i].isIssued())
            {
                cout << "This book is already issued.\n";
                return;
            }

            books[i].setIssued(true);
            borrowRecords.push_back(BorrowRecord(bookId, memberId, getCurrentDate(), ""));
            saveBooks();
            saveBorrowRecords();
            cout << "Book issued successfully.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

void Library::returnBook()
{
    int bookId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;

    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getId() == bookId)
        {
            if (!books[i].isIssued())
            {
                cout << "This book is already available in library.\n";
                return;
            }

            BorrowRecord *activeRecord = nullptr;
            for (size_t j = borrowRecords.size(); j > 0; --j)
            {
                if (borrowRecords[j - 1].getBookId() == bookId && !borrowRecords[j - 1].isReturned())
                {
                    activeRecord = &borrowRecords[j - 1];
                    break;
                }
            }

            if (activeRecord == nullptr)
            {
                cout << "No active borrow record found for this book.\n";
                return;
            }

            string returnDate = getCurrentDate();
            int daysBorrowed = calculateDaysBetween(activeRecord->getIssueDate(), returnDate);
            int fine = activeRecord->calculateFine(daysBorrowed);
            int lateDays = 0;

            if (daysBorrowed > 7)
            {
                lateDays = daysBorrowed - 7;
            }

            books[i].setIssued(false);
            activeRecord->setReturnDate(returnDate);
            activeRecord->setFine(fine);

            saveBooks();
            saveBorrowRecords();
            cout << "Book returned successfully\n";
            cout << "Late by " << lateDays << " days\n";
            cout << "Fine to pay: ₹" << fine << '\n';
            return;
        }
    }

    cout << "Book not found.\n";
}

void Library::displayIssuedBooks() const
{
    bool hasIssuedBooks = false;

    cout << "\n=============== ISSUED BOOKS ===============\n";
    cout << left << setw(10) << "Book ID"
         << setw(12) << "Member ID"
         << setw(15) << "Issue Date" << '\n';
    cout << string(37, '-') << '\n';

    for (size_t i = 0; i < borrowRecords.size(); ++i)
    {
        if (borrowRecords[i].isReturned())
        {
            continue;
        }

        hasIssuedBooks = true;
        cout << left << setw(10) << borrowRecords[i].getBookId()
             << setw(12) << borrowRecords[i].getMemberId()
             << setw(15) << borrowRecords[i].getIssueDate() << '\n';
    }

    if (!hasIssuedBooks)
    {
        cout << "No books are currently issued.\n";
    }
}

void Library::displayBorrowHistory()
{
    if (borrowRecords.empty())
    {
        cout << "No borrow history found.\n";
        return;
    }

    cout << "\n========================== BORROW HISTORY ==========================\n";
    cout << left << setw(10) << "Book ID"
         << setw(12) << "Member ID"
         << setw(15) << "Issue Date"
         << setw(15) << "Return Date"
         << setw(8) << "Fine" << '\n';
    cout << string(60, '-') << '\n';

    for (size_t i = 0; i < borrowRecords.size(); ++i)
    {
        string returnDate = borrowRecords[i].getReturnDate();
        if (returnDate.empty())
        {
            returnDate = "Not Returned";
        }

        cout << left << setw(10) << borrowRecords[i].getBookId()
             << setw(12) << borrowRecords[i].getMemberId()
             << setw(15) << borrowRecords[i].getIssueDate()
             << setw(15) << returnDate
             << setw(8) << borrowRecords[i].getFine() << '\n';
    }
}
