#include "Library.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

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
        string bookIdStr, memberIdStr, issueDate, returnDate;

        getline(ss, bookIdStr, '|');
        getline(ss, memberIdStr, '|');
        getline(ss, issueDate, '|');
        getline(ss, returnDate, '|');

        if (bookIdStr.empty() || memberIdStr.empty() || issueDate.empty())
        {
            continue;
        }

        borrowRecords.push_back(BorrowRecord(stoi(bookIdStr), stoi(memberIdStr), issueDate, returnDate));
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

Library::Library()
{
    loadBooks();
    loadMembers();
    loadBorrowRecords();
}

void Library::addBook()
{
    Book b;
    b.inputBook();

    if (isBookIdExists(b.getId()))
    {
        cout << "Book with this ID already exists.\n";
        return;
    }

    books.push_back(b);
    saveBooks();
    cout << "Book added successfully.\n";
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
    m.inputMember();

    if (isMemberIdExists(m.getId()))
    {
        cout << "Member with this ID already exists.\n";
        return;
    }

    members.push_back(m);
    saveMembers();
    cout << "Member added successfully.\n";
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

            books[i].setIssued(false);
            for (size_t j = borrowRecords.size(); j > 0; --j)
            {
                if (borrowRecords[j - 1].getBookId() == bookId && !borrowRecords[j - 1].isReturned())
                {
                    borrowRecords[j - 1].setReturnDate(getCurrentDate());
                    break;
                }
            }
            saveBooks();
            saveBorrowRecords();
            cout << "Book returned successfully and marked available.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

void Library::displayIssuedBooks() const
{
    bool hasIssuedBooks = false;

    cout << "\n=========================== ISSUED BOOKS ===========================\n";
    cout << left << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(12) << "Member ID"
         << setw(25) << "Member Name"
         << setw(15) << "Issue Date" << '\n';
    cout << string(92, '-') << '\n';

    for (size_t i = 0; i < borrowRecords.size(); ++i)
    {
        if (borrowRecords[i].isReturned())
        {
            continue;
        }

        hasIssuedBooks = true;
        cout << left << setw(10) << borrowRecords[i].getBookId()
             << setw(30) << getBookTitleById(borrowRecords[i].getBookId())
             << setw(12) << borrowRecords[i].getMemberId()
             << setw(25) << getMemberNameById(borrowRecords[i].getMemberId())
             << setw(15) << borrowRecords[i].getIssueDate() << '\n';
    }

    if (!hasIssuedBooks)
    {
        cout << "No books are currently issued.\n";
    }
}
