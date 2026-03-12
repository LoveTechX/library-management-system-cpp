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
    void inputMemberWithoutId();
    void displayMember() const;

    int getId() const;
    std::string getName() const;

    void setId(int newId);
    std::string toFileString() const;
};

#endif
