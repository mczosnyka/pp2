#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cstring>// std::exchange
using namespace std;

#include "simpleString.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif



SimpleString::SimpleString() : data_(new char[1]{}), size_(0), capacity_(0){
    instances_++;

};

SimpleString::SimpleString(const char* text) : data_(new char[strlen(text)+1]), size_(strlen(text)), capacity_(strlen(text)){
    instances_++;
    strcpy(data_, text);
};

SimpleString::SimpleString(const SimpleString& text): data_(new char[text.size_+1]), size_(text.size_), capacity_(text.capacity_){
    instances_++;
    strcpy(data_, text.data_);
};

SimpleString::SimpleString(SimpleString&& string1) : data_(exchange(string1.data_, new char[string1.capacity_]{})), size_(exchange(string1.size_, 0)), capacity_(exchange(string1.capacity_, 0)){

};


SimpleString::~SimpleString(){
    delete[] data_;
    instances_ -= 1;
};


size_t SimpleString::size() const{
    return size_;
// mozliwe ze musze size_-1 napisac i wtedy w konstruktorze bezargumentowym size 1
};
size_t SimpleString::capacity() const{
    return capacity_;
};
char* SimpleString::data() const{
        return data_;
};

char* SimpleString::c_str() const{
        return data_;
};

size_t SimpleString::instances(){
    return instances_;
};

void SimpleString::assign(const char* new_text){
    size_ = strlen(new_text);
    capacity_ = strlen(new_text);
    delete[] data_;
    instances_ --;
    data_ = new char[strlen(new_text)+1];
    strcpy(data_, new_text);
    instances_ ++;
};

bool SimpleString::equal_to(SimpleString new_string, bool case_sensitive) const{
    char* second_string = new_string.c_str();
    if (case_sensitive == true){
        if(strcmp(second_string, data_)==0)
            return true;
        else
            return false;
    }
    if (case_sensitive == false){
        int i;
        for (i = 0; data_[i] && second_string[i]; ++i)
        {
            if (data_[i] == second_string[i] || (data_[i] ^ 32) == second_string[i])
                continue;
            else
                break;
        }
        if (data_[i] == second_string[i])
            return true;
        else
            return false;
    }
delete[] second_string;

};

void SimpleString::append(SimpleString new_string){
    this->size_ += (new_string.size_);
    this->capacity_ += (new_string.capacity_);
    int len = (this->size_) + (new_string.size_) + 1;
    char* appended = new char[len];
    strcpy(appended, this->data_);
    strcat(appended, new_string.data_);
    delete[] this->data_;
    this->data_ = new char[len];
    strcpy(this->data_, appended);
    delete[] appended;
};

int SimpleString::compare(SimpleString newstring, bool case_sensitive) const{
    char* second_string = newstring.c_str();
    if (case_sensitive == true){
        int returned_value = (strcmp(data_, second_string));
            return returned_value;
    }
    if (case_sensitive == false){
        int i;
        for (i = 0; data_[i] && second_string[i]; ++i)
        {
            if (data_[i] == second_string[i] || (data_[i] ^ 32) == second_string[i])
                continue;
            else
                break;
        }
        if (data_[i] == second_string[i])
            return 0;
        if ((data_[i] | 32) < (second_string[i] | 32))
            return -1;
        return 1;
    }
    delete[] second_string;
}

SimpleString SimpleString::substr(size_t pos, size_t count)const{
    int text_size = 0;
    if(pos>=0 && pos<= size_ && count < size_){
        text_size = count;
    }
    if (count < 0 || count > size_){
        text_size = (size_ - pos);
    }
    SimpleString new_text;
    char* buffer = new char[text_size+1]{};
    new_text.capacity_ = text_size;
    new_text.size_ = text_size;
    for(int i=0; i<text_size; i++){
        buffer[i] = data_[pos];
        pos++;
    }
    delete[] new_text.data_;
    new_text.data_ = new char[text_size+1];
    strcpy(new_text.data_, buffer);
    delete[] buffer;
    return new_text;


    
};
