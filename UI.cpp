#include "UI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void UI::clearScreen()
{
    // Use system command appropriate for Windows
    system("cls");
}

void UI::pause()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

void UI::printDivider()
{
    cout << "====================================\n";
}

void UI::printHeader(const std::string &title)
{
    clearScreen();
    printDivider();
    printCentered(title);
    printDivider();
    cout << "\n";
}

void UI::printMenu()
{
    cout << "   1. Add Book\n";
    cout << "   2. Display Books\n";
    cout << "   3. Search Book by Title\n";
    cout << "   4. Search Book by Author\n";
    cout << "   5. Delete Book\n";
    cout << "   6. Add Member\n";
    cout << "   7. Display Members\n";
    cout << "   8. Search Member\n";
    cout << "   9. Issue Book\n";
    cout << "   10. Return Book\n";
    cout << "   11. Display Issued Books\n";
    cout << "   12. View Borrow History\n";
    cout << "   13. Exit\n";
    cout << "\n   Enter your choice: ";
}

void UI::printSuccess(const std::string &message)
{
    cout << "\n";
    printDivider();
    cout << "   ✓ " << message << "\n";
    printDivider();
    pause();
}

void UI::printError(const std::string &message)
{
    cout << "\n";
    printDivider();
    cout << "   ✗ " << message << "\n";
    printDivider();
    pause();
}

void UI::printCentered(const std::string &text)
{
    int padding = (36 - text.length()) / 2;
    cout << string(padding, ' ') << text << "\n";
}

void UI::printBoxed(const std::string &message)
{
    cout << "\n+----------------------------------+\n";
    cout << "| " << message << "\n";
    cout << "+----------------------------------+\n";
}

void UI::printBookTable(const std::vector<Book> &books)
{
    if (books.empty())
    {
        printError("No books found");
        return;
    }

    cout << "\n";
    printDivider();
    cout << left << setw(6) << " ID" << setw(30) << "Title" << setw(20) << "Author" << setw(12) << "Status" << "\n";
    printDivider();

    for (const auto &book : books)
    {
        cout << left << setw(6) << (" " + to_string(book.getId()))
             << setw(30) << (" " + book.getTitle())
             << setw(20) << (" " + book.getAuthor())
             << setw(12) << (book.isIssued() ? " Issued" : " Available") << "\n";
    }

    printDivider();
    pause();
}

void UI::printMemberTable(const std::vector<Member> &members)
{
    if (members.empty())
    {
        printError("No members found");
        return;
    }

    cout << "\n";
    printDivider();
    cout << left << setw(10) << " ID" << setw(40) << "Name" << "\n";
    printDivider();

    for (const auto &member : members)
    {
        cout << left << setw(10) << (" " + to_string(member.getId()))
             << setw(40) << (" " + member.getName()) << "\n";
    }

    printDivider();
    pause();
}
