#ifndef ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H
#define ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H
#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <string>
#include <array>
#include <ostream>
#include <istream>
#include <set>
#include <map>
#include <vector>
#include <random>
#include <functional>
using namespace std;

class MyString {
    static constexpr size_t SIZE = 20;
    std::array<char, SIZE+1> data_;
    size_t capacity_;
    size_t size_;
    string dynamicData_;


public:
    class iterator{
    private:
        MyString* myString_;
        size_t position_;
    public:
        explicit iterator(MyString* myString, size_t position);
        bool operator!=(iterator anotherIt);
        bool operator==(iterator anotherIt);
        iterator operator+(size_t pos);
        iterator& operator++();
        iterator& operator--();
        size_t operator-(iterator anotherIt);
        char& operator*();
    };
    class const_iterator{
    private:
        const MyString* myString_;
        size_t position_;
    public:
        explicit const_iterator(const MyString* myString, size_t position);
        bool operator!=(const_iterator anotherIt) const;
        bool operator==(const_iterator anotherIt) const;
        const_iterator operator+(size_t pos) const;
        const_iterator& operator++();
        const_iterator& operator--();
        size_t operator-(const_iterator anotherIt) const;
        char operator*() const;
    };
    MyString& operator=(const MyString& another);
    MyString& operator+=(const char character);
    std::set<MyString> getUniqueWords() const;
    bool operator<(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator>=(const MyString& other) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    MyString();
    MyString(const char *text);
    MyString(const MyString& another);
    ~MyString();
    static const size_t initialBufferSize_ = 20;
    auto capacity() const{
        return capacity_;
    }
    auto size() const{
        return size_;
    };
    bool empty() const;
    void clear();
    friend ostream& operator<<(ostream& os, const MyString& string);
    friend istream& operator>>(std::istream& is, MyString& string);
    char operator[](size_t i) const;
    MyString& trim();
    map<MyString,size_t> countWordsUsageIgnoringCases() const;
    MyString& toLower();
    static MyString generateRandomWord(size_t length);
    bool startsWith(const char *text) const;
    bool endsWith(const char *text) const;
    MyString join(const std::vector<MyString> &texts) const;
    bool all_of(std::function<bool(char)> predicate) const;
};


#endif //ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H
