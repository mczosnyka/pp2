#include "user.h"

bool operator==(const User& lhs, const User& rhs)
{
    return lhs.user_name_ == rhs.user_name_ &&
           lhs.password_ == rhs.password_ &&
           lhs.admin_ == rhs.admin_;
}
