#include <iostream>
#include <random>
#include <typeinfo>
#include <type_traits>
#include <cstring>
#include <cctype>
#include "stringObject.h"
using namespace std;

// TODO:

StringObject::StringObject(std::string new_text): text(new_text){};
bool StringObject::operator==(const Object& obj) const
{
    if (const StringObject* other = dynamic_cast<const StringObject*>(&obj))
    {
        return text == other->text;
    }
    return false;
}
