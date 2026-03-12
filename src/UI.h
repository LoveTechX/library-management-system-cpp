#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "Book.h"
#include "Member.h"

class UI
{
public:
    // Basic UI functions
    static void clearScreen();
    static void pause();
    static void printHeader(const std::string &title);
    static void printMenu();
    static void printSuccess(const std::string &message);
    static void printError(const std::string &message);
    static void printDivider();

    // Formatted display functions
    static void printBookTable(const std::vector<Book> &books);
    static void printMemberTable(const std::vector<Member> &members);

    // Utility functions
    static void printCentered(const std::string &text);
    static void printBoxed(const std::string &message);
};

#endif
