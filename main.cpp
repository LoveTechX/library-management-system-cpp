#include <iostream>
#include <limits>

#include "Library.h"

using namespace std;

void showMenu()
{
    cout << "\n========= LIBRARY MANAGEMENT SYSTEM =========\n";
    cout << "1. Add Book\n";
    cout << "2. Display Books\n";
    cout << "3. Search Book\n";
    cout << "4. Delete Book\n";
    cout << "5. Add Member\n";
    cout << "6. Display Members\n";
    cout << "7. Issue Book\n";
    cout << "8. Return Book\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Library library;
    int choice;

    do
    {
        showMenu();

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number from 1 to 9.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << '\n';

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.displayBooks();
            break;
        case 3:
            library.searchBook();
            break;
        case 4:
            library.deleteBook();
            break;
        case 5:
            library.addMember();
            break;
        case 6:
            library.displayMembers();
            break;
        case 7:
            library.issueBook();
            break;
        case 8:
            library.returnBook();
            break;
        case 9:
            cout << "Exiting program... Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please select between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
