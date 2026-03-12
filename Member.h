#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member
{
private:
    int id;
    std::string name;

public:
    Member();
    Member(int id, const std::string &name);

    void inputMember();
    void displayMember() const;

    int getId() const;
    std::string getName() const;

    std::string toFileString() const;
};

#endif
