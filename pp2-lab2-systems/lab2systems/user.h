#ifndef USER_H
#define USER_H

#include <string>

struct User
{
    std::string user_name_;
    std::string password_;
    bool admin_ = false;
};

bool operator==(const User& lhs, const User& rhs);

#endif // USER_H
