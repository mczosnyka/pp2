#include <iostream>
using namespace std;

#include "user.h"
#include "windows.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Funkcje sa do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

string Windows::version(){
    return version_;
}
size_t Windows::activated_systems(){
    return activated_systems_;
}

int Windows::add_user(string user_name, string password){
    struct User user_struct;
    user_struct.user_name_ = user_name;
    user_struct.password_ = password;
    users_.push_back(user_struct);
    int id = (users_.size() - 1);
    return id;
}

User Windows::user(int &user_id){
    return users_[user_id];
}

string Windows::user_home_directory(int &user_id) {
    string path = "C:\\Users\\";
    string username = users_[user_id].user_name_;
    path.append(username);
    return path;
}