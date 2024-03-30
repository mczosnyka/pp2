#include <iostream>
using namespace std;

#include "user.h"
#include "linux.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

string Linux::distribution(){
    return distribution_;
}

size_t Linux::open_source_sympathizers(){
    return open_source_sympathizers_;
}

int Linux::add_user(string user_name, string password){
    struct User user_struct;
    user_struct.user_name_ = user_name;
    user_struct.password_ = password;
    users_.push_back(user_struct);
    int id = (users_.size() - 1);
    return id;
}

User Linux::user(int &user_id){
    return users_[user_id];
};

string Linux::user_home_directory(int &user_id) {
    string path = "/home/";
    string username = users_[user_id].user_name_;
    path.append(username);
    path.append("/");
    return path;
}

void Linux::set_graphic_environment(string graphic_environment){
    graphic_environment_ = graphic_environment;
};

std::optional<std::string> Linux::graphic_environment() const{
   return graphic_environment_;
}