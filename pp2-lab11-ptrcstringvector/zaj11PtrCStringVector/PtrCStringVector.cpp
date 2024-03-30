#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"
using namespace std;


PtrCStringVector::PtrCStringVector() : size_(0), capacity_(0), data_(nullptr)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym

}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector): size_(srcPtrCStringVector.size_), capacity_(srcPtrCStringVector.capacity_), data_(new char*[capacity_]{}) {
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if (this != &srcPtrCStringVector) {
            for (size_t i = 0; i < size_; i++) {
                delete[] data_[i];
            }
            for (std::size_t i = 0; i < size_; i++) {
                data_[i] = new char[strlen(srcPtrCStringVector.data_[i]) + 1];
                strcpy(data_[i], srcPtrCStringVector.data_[i]);
            }
        }
    }

PtrCStringVector::~PtrCStringVector()
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    for (size_t i = 0; i < size_; i++) {
        delete[] data_[i];
    }
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;

}

PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    for (size_t i = 0; i < size_; i++) {
        delete[] data_[i];
    }
    delete[] data_;
    size_ = source.size_;
    capacity_ = source.capacity_;
    data_ = new char*[capacity_]{};

    for (std::size_t i = 0; i < size_; i++) {
        data_[i] = new char[strlen(source.data_[i]) + 1];
        strcpy(data_[i], source.data_[i]);
    }
    return *this;
}

PtrCStringVector& PtrCStringVector::operator=(PtrCStringVector&& source)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if (this != &source) {
        if (data_) {
            for (size_t i = 0; i < size_; i++) {
                delete[] data_[i];
            }
            delete[] data_;
        }
        size_ = std::exchange(source.size_, 0);
        capacity_ = std::exchange(source.capacity_, 0);
        data_ = std::exchange(source.data_, new char*[0]);
    }
    return *this;

}

void PtrCStringVector::push_back(const char *text2Add)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if(size_ == 0){
        reserve(capacity_ += 8);
    }
    else if(size_ == capacity_){
        reserve(capacity_ *= 2);
    }
    data_[size_] = new char[strlen(text2Add)+1];
    strcpy(data_[size_], text2Add);
    size_++;
}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    PtrCStringVector new_container;
    for(size_t i = 0; i<size_; i++){
        new_container.push_back(data_[i]);
    }
    for (size_t i = 0; i < anotherVector.size_; i++) {
        new_container.push_back(anotherVector.data_[i]);
    }
    return new_container;
}

char *PtrCStringVector::operator[](size_t index)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if (index >= size_)
    {
        throw std::out_of_range("");
    }
    return data_[index];
}
const char *PtrCStringVector::operator[](size_t index) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if (index >= size_)
    {
        throw std::out_of_range("");
    }
    return data_[index];
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    PtrCStringVector new_container;
    size_t size = min(size_, rhs.size_);
    for(size_t i = 0; i<size; i++){
        char* summ = new char[strlen(data_[i]) + strlen(rhs.data_[i]) + 1];
        strcpy(summ, data_[i]);
        strcat(summ, rhs.data_[i]);
        new_container.push_back(summ);
        delete[] summ;
    }
    if(size_>size){
        for(size_t i = size; i<size_; i++) {
            new_container.push_back(data_[i]);
        }
    }
    else if(rhs.size_>size){
        for(size_t i = size; i<rhs.size_; i++) {
            new_container.push_back(rhs.data_[i]);
        }
    }
    return new_container;
}

void PtrCStringVector::free()
{
    /// @todo sugeruje zaimplementowac, szczegoly w pliku naglowkowym
}

void PtrCStringVector::reserve(size_t new_capacity) {
    /// @todo sugeruje zaimplementowac, szczegoly w pliku naglowkowym
    char **new_data = new char *[new_capacity];
    if (size_ != 0) {
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
    }
    delete[] data_;
    data_ = new_data;
}
