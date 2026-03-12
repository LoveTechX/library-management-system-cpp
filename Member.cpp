#include "Member.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

Member::Member() : id(0), name("") {}

Member::Member(int id, const string &name) : id(id), name(name) {}

void Member::inputMember()
{
    cout << "Enter Member ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Member Name: ";
    getline(cin, name);
}

void Member::displayMember() const
{
    cout << left << setw(10) << id << setw(30) << name << '\n';
}

int Member::getId() const { return id; }

string Member::getName() const { return name; }

string Member::toFileString() const
{
    ostringstream out;
    out << id << '|' << name;
    return out.str();
}
