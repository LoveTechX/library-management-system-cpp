#include <iostream>
#include <limits>

#include "Library.h"
#include "UI.h"

using namespace std;

int main()
{
    Library library;
    int choice;

    UI::printHeader("LIBRARY MANAGEMENT SYSTEM");

    do
    {
        UI::printMenu();

        if (!(cin >> choice))
        {
            UI::printError("Invalid input. Please enter a number from 1 to 11");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << '\n';

        switch (choice)
        {
        case 1:
        {
            UI::clearScreen();
            UI::printHeader("ADD BOOK");
            library.addBook();
            UI::pause();
            break;
        }
        case 2:
        {
            UI::clearScreen();
            UI::printHeader("BOOK LIST");
            library.displayBooks();
            UI::pause();
            break;
        }
        case 3:
        {
            UI::clearScreen();
            UI::printHeader("SEARCH BOOK");
            library.searchBook();
            break;
        }
        case 4:
        {
            UI::clearScreen();
            UI::printHeader("DELETE BOOK");
            library.deleteBook();
            UI::pause();
            break;
        }
        case 5:
        {
            UI::clearScreen();
            UI::printHeader("ADD MEMBER");
            library.addMember();
            UI::pause();
            break;
        }
        case 6:
        {
            UI::clearScreen();
            UI::printHeader("MEMBER LIST");
            library.displayMembers();
            UI::pause();
            break;
        }
        case 7:
        {
            UI::clearScreen();
            UI::printHeader("ISSUE BOOK");
            library.issueBook();
            UI::pause();
            break;
        }
        case 8:
        {
            UI::clearScreen();
            UI::printHeader("RETURN BOOK");
            library.returnBook();
            UI::pause();
            break;
        }
        case 9:
        {
            UI::clearScreen();
            UI::printHeader("ISSUED BOOKS");
            library.displayIssuedBooks();
            UI::pause();
            break;
        }
        case 10:
        {
            UI::clearScreen();
            UI::printHeader("BORROW HISTORY");
            library.displayBorrowHistory();
            UI::pause();
            break;
        }
        case 11:
        {
            UI::clearScreen();
            UI::printBoxed("Thank you for using Library Management System!");
            cout << "\nGoodbye!\n";
            break;
        }
        default:
            UI::printError("Invalid choice. Please select between 1 and 11");
            continue;
        }

        if (choice != 11)
        {
            UI::printHeader("LIBRARY MANAGEMENT SYSTEM");
        }

    } while (choice != 11);

    return 0;
}
