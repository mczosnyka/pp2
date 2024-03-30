#include "mystring.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <string>
#include <ostream>
#include <istream>
#include <set>
#include <map>
#include <vector>
#include <random>
using namespace std;

MyString::MyString() : data_(), size_(0), capacity_(initialBufferSize_+string().capacity()){};

MyString::MyString(const char *text): size_(strlen(text)), capacity_(strlen(text)){
    int sizer = 0;
    int j = 0;
    if(strlen(text)>(SIZE)){
        sizer = SIZE;
    }
    else if(strlen(text)<=(SIZE)){
        sizer = strlen(text);
    }
    std::copy_n(text, sizer, data_.begin());
    data_[sizer] = '\0';
    if(strlen(text)>(SIZE-1)){
        dynamicData_ = text+20;
    }
};

MyString::MyString(const MyString& another) = default;

MyString& MyString::operator=(const MyString& another){
        data_ = another.data_;
        size_ = another.size_;
        dynamicData_ = another.dynamicData_;
        capacity_ = another.capacity_;
    return *this;
};

MyString::~MyString(){
    clear();
}
MyString::iterator::iterator(MyString* myString, size_t position): myString_(myString), position_(position){};

bool MyString::iterator::operator!=(iterator anotherIt){
    return position_ != anotherIt.position_;
}

bool MyString::iterator::operator==(iterator anotherIt){
    return position_ == anotherIt.position_;
}

MyString::iterator MyString::iterator::operator+(size_t pos){
    return iterator(myString_, position_ + pos);
}

MyString::iterator& MyString::iterator::operator++() {
    ++position_;
    return *this;
}

MyString::iterator& MyString::iterator::operator--() {
    --position_;
    return *this;
}

size_t MyString::iterator::operator-(iterator anotherIt){
    return (position_ - anotherIt.position_);
}
char& MyString::iterator::operator*(){
    if (position_<SIZE && position_>=0){
        return myString_->data_[position_];
    }
    else if(position_>=SIZE){
        return myString_->dynamicData_.at(position_-SIZE);
    }
}
MyString::const_iterator::const_iterator(const MyString* myString, size_t position) : myString_(myString), position_(position) {}

bool MyString::const_iterator::operator!=(const const_iterator anotherIt) const{
    return position_ != anotherIt.position_;
}

bool MyString::const_iterator::operator==(const_iterator anotherIt) const{
    return position_ == anotherIt.position_;
}

char MyString::const_iterator::operator*() const {
    if (position_<SIZE && position_>=0){
        return myString_->data_[position_];
    }
    else if(position_>=SIZE){
        return myString_->dynamicData_.at(position_-SIZE);
    }
}

MyString::const_iterator& MyString::const_iterator::operator++() {
    ++position_;
    return *this;
}

MyString::const_iterator& MyString::const_iterator::operator--() {
    --position_;
    return *this;
}

MyString::const_iterator MyString::const_iterator::operator+(size_t pos) const {
    return const_iterator(myString_, position_ + pos);
}

size_t MyString::const_iterator::operator-(const_iterator anotherIt) const {
    return (position_ - anotherIt.position_);
}

MyString::iterator MyString::begin(){
    return iterator(this, 0);
}

MyString::iterator MyString::end(){
    return iterator(this, size_);
}

MyString::const_iterator MyString::begin() const{
    return const_iterator(this, 0);
}

MyString::const_iterator MyString::end() const{
    return const_iterator(this, size_);
}

bool MyString::empty() const{
    return size_ == 0;
}

void MyString::clear(){
    size_ = 0;
    capacity_ = initialBufferSize_+string().capacity();
    data_.fill({});
    dynamicData_.clear();
}
ostream& operator<<(ostream& os, const MyString& string){
    os << string.data_.data();
    os << string.dynamicData_;
    return os;
};
char MyString::operator[](size_t i) const{
    if (i >= size_) {
        throw std::out_of_range("");
    }
    const_iterator it = begin() + i;
    return *it;
}

istream& operator>>(std::istream& is, MyString& string){
    std::string input;
    std::getline(is, input);
    string.clear();
    const char* str = input.c_str();
    MyString newer(str);
    string = newer;

    return is;
}

MyString& MyString::trim(){
    std::string trimmed(data_.data(), SIZE);
    trimmed.append(dynamicData_);
    auto it = find_if_not(trimmed.begin(),trimmed.end(),::isspace);
    string trimmed2(it, trimmed.end());
    auto it2 = std::find_if_not(trimmed2.rbegin(), trimmed2.rend(), ::isspace);
    string trimmed3(trimmed2.begin(), it2.base());
    const char* trimmedArray = trimmed3.c_str();
    MyString returned(trimmedArray);
    *this = returned;
    return* this;
}

MyString& MyString::operator+=(const char character){
    if (size_>=SIZE){
        dynamicData_.push_back(character);
        size_++;
        capacity_++;
    }
    else if(size_<SIZE){
        for(int i = 0; i<SIZE; i++){
            if(data_[i] == 0){
                data_[i] = character;
                size_++;
                capacity_++;
                break;
            }
        }
    }
    return* this;
}

std::set<MyString> MyString::getUniqueWords() const {
    std::set<MyString> uniqueWords;
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    std::transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    string1.erase(std::remove(string1.begin(), string1.end(), ','), string1.end());
    std::string pattern = "...";
    size_t pos = string1.find(pattern);
    string1.replace(pos, pattern.length(), " ");
    string1.erase(std::remove(string1.begin(), string1.end(), ','), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '.'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '!'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '?'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '-'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), ':'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), ';'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '"'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '\''), string1.end());
    auto it = string1.begin();
    for (int i = 0; i < string1.length(); i++) {
        auto it2 = std::find_if(it, string1.end(), ::isspace);
        string temp2(it, it2);
        const char* stringArray = temp2.c_str();
        if (it2==string1.end() || it2+1==string1.end()){
            break;
        }
        it = it2+1;
        MyString addition(stringArray);
        uniqueWords.insert(addition);
    }
    return uniqueWords;
}

map<MyString,size_t> MyString::countWordsUsageIgnoringCases() const{
    std::map<MyString, size_t> uniqueWords;
    vector<string> wektor;
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    std::transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    string1.erase(std::remove(string1.begin(), string1.end(), ','), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '.'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '!'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '?'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '-'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), ':'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), ';'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '"'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '\''), string1.end());
    auto newEnd = std::unique(string1.begin(), string1.end(), [](char a, char b) {
        return std::isspace(a) && std::isspace(b);
    });
    string1.erase(newEnd, string1.end());
    std::replace(string1.begin(), string1.end(), '\n', ' ');

    auto it = string1.begin();
    for (int i = 0; i < string1.length(); i++) {
        auto it2 = std::find_if(it, string1.end(), ::isspace);
        string temp2(it, it2);
        wektor.push_back(temp2);
        if (it2==string1.end() || it2+1==string1.end()){
            break;
        }
        it = it2+1;

    }
    sort(wektor.begin(), wektor.end(), greater <>());
    int j = 0;
    int counter = 1;
    while(j<wektor.size()-1){
        const char* stringArray = wektor[j].c_str();
        const char* temp = stringArray;
        while(temp==wektor[j+1]){
            counter++;
            j++;
        }
        MyString addition(stringArray);
        uniqueWords.insert(std::make_pair(addition, counter));
        j++;
        counter = 1;
    }
    return uniqueWords;
}

bool MyString::operator<(const MyString& other) const{
    if(size_<=SIZE && other.size_<=SIZE){
        string string1;
        string string2;
        for(int i =0; i<size_;i++){
            string1.push_back(data_[i]);
        }
        for(int i =0; i<other.size_;i++){
            string2.push_back(other.data_[i]);
        }
        return string1 < string2;
    }
    if(size_>SIZE){
        std::string ours(data_.data(), SIZE);
        ours.append(dynamicData_);
        std::string another(other.data_.data(), SIZE);
        another.append(other.dynamicData_);
        return ours < another;
    }
};

bool MyString::operator>(const MyString& other) const{
    if(size_<=SIZE && other.size_<=SIZE){
        string string1;
        string string2;
        for(int i =0; i<size_;i++){
            string1.push_back(data_[i]);
        }
        for(int i =0; i<other.size_;i++){
            string2.push_back(other.data_[i]);
        }
        return string1 > string2;
    }
    if(size_>SIZE){
        std::string ours(data_.data(), SIZE);
        ours.append(dynamicData_);
        std::string another(other.data_.data(), SIZE);
        another.append(other.dynamicData_);
        return ours > another;
    }
};

bool MyString::operator>=(const MyString& other) const{
    if(size_<=SIZE && other.size_<=SIZE){
        string string1;
        string string2;
        for(int i =0; i<size_;i++){
            string1.push_back(data_[i]);
        }
        for(int i =0; i<other.size_;i++){
            string2.push_back(other.data_[i]);
        }
        return string1 >= string2;
    }
    if(size_>SIZE){
        std::string ours(data_.data(), SIZE);
        ours.append(dynamicData_);
        std::string another(other.data_.data(), SIZE);
        another.append(other.dynamicData_);
        return ours >= another;
    }
};

bool MyString::operator<=(const MyString& other) const{
    if(size_<=SIZE && other.size_<=SIZE){
        string string1;
        string string2;
        for(int i =0; i<size_;i++){
            string1.push_back(data_[i]);
        }
        for(int i =0; i<other.size_;i++){
            string2.push_back(other.data_[i]);
        }
        return string1 <= string2;
    }
    if(size_>SIZE){
        std::string ours(data_.data(), SIZE);
        ours.append(dynamicData_);
        std::string another(other.data_.data(), SIZE);
        another.append(other.dynamicData_);
        return ours <= another;
    }
}

bool MyString::operator==(const MyString& other) const{
    if(size_<=SIZE && other.size_<=SIZE){
        string string1;
        string string2;
        for(int i =0; i<size_;i++){
            string1.push_back(data_[i]);
        }
        for(int i =0; i<other.size_;i++){
            string2.push_back(other.data_[i]);
        }
        return string1 == string2;
    }
    if(size_>SIZE){
        std::string ours(data_.data(), SIZE);
        ours.append(dynamicData_);
        std::string another(other.data_.data(), SIZE);
        another.append(other.dynamicData_);
        return ours == another;
    }
}

bool MyString::operator!=(const MyString& other) const{
    if(size_<=SIZE && other.size_<=SIZE){
        string string1;
        string string2;
        for(int i =0; i<size_;i++){
            string1.push_back(data_[i]);
        }
        for(int i =0; i<other.size_;i++){
            string2.push_back(other.data_[i]);
        }
        return string1 != string2;
    }
    if(size_>SIZE){
        std::string ours(data_.data(), SIZE);
        ours.append(dynamicData_);
        std::string another(other.data_.data(), SIZE);
        another.append(other.dynamicData_);
        return ours != another;
    }
}

MyString& MyString::toLower(){
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    std::transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    const char * charArray = string1.c_str();
    MyString newer(charArray);
    *this = newer;
    return *this;
};

char generateRandomLetter() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('a', 'z');
    return static_cast<char>(dis(gen));
}

MyString MyString::generateRandomWord(size_t length){
    std::string randomString;
    randomString.resize(length);
    std::generate_n(randomString.begin(), length, generateRandomLetter);
    const char* randomArray = randomString.c_str();
    MyString returned(randomArray);
    return returned;
};

bool MyString::startsWith(const char *text) const{
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    for(int i=0; i<sizeof(text); i++){
        if(string1.at(i)!=text[i]){
            return false;
        }
    }
    return true;
};

bool MyString::endsWith(const char *text) const{
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    int j =0;
    for(int i=string1.length()-strlen(text); i<string1.length(); i++){
        if(string1.at(i)!=text[j]){
            return false;
        }
        j++;
    }
    return true;
};


MyString MyString::join(const std::vector<MyString> &texts) const{
    MyString joined;
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    for(int i=0; i<texts.size(); i++){
        if(joined.empty() == false){
            for(int j = 0; j<size_; j++){
                joined += string1.at(j);
            }
        }
        for(int j=0; j<texts[i].size(); j++){
            joined += texts[i][j];
        }
    }
    return joined;
};

bool MyString::all_of(std::function<bool(char)> predicate) const{
    string string1;
    if (size_ <= SIZE) {
        string temp;
        for (int i = 0; i < size_; i++) {
            temp.push_back(data_[i]);
        }
        string1.assign(temp);
    } else if (size_ > SIZE) {
        std::string temp(data_.data(), SIZE);
        temp.append(dynamicData_);
        string1.assign(temp);
    }
    bool result = std::all_of(string1.begin(), string1.end(), predicate);
    return result;
}

