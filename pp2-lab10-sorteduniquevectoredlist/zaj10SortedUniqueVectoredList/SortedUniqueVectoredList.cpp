#include <stdexcept> // std::out_of_range
#include <utility>   // std::exchange
#include <array>
#include <limits>
#include <algorithm>
#include <string>
#include <vector>
#include "SortedUniqueVectoredList.h"
using namespace std;


/** class SortedUniqueVectoredList::Bucket
 * @param size ilosc elementow w kubelku, tworzac pusty ma byc 0
 * @param values elementy kubelka, jako tablica statyczna
 * @param BUCKET_SIZE ilosc elementow w statycznej tablicy
 * @param bucketCount_ ilosc kubelkow
 * @param next wskaznik na nastepny @ref Bucket, a jesli takiego nie ma na nullptr
 * @param previous wskaznik na poprzedni @ref Bucket, a jesli takiego nie ma na nullptr
 * @note jest to klasa zrobiona przy pomocy [idiomu PIMPL](https://en.cppreference.com/w/cpp/language/pimpl),
 *       ktory polega na tym, ze w klasie zewnetrznej jest jedynie deklaracja klasy wewnetrznej, ktora jest zaimplementowana w pliku zrodlowym **/
struct SortedUniqueVectoredList::Bucket
{
    constexpr static size_t BUCKET_SIZE = 10;

    std::array<std::string, BUCKET_SIZE> values;
    size_t size{};

    Bucket* next;
    Bucket* previous;
};


void SortedUniqueVectoredList::sorting() {
    std::vector<std::string> temp;
    Bucket *current = head;
    Bucket *iteration = head;
    int j = 0;
    for (int i = 0; i < size_; ++i) {
        temp.push_back(iteration->values[j]);
        j++;
        if (j == Bucket::BUCKET_SIZE) {
            iteration = iteration->next;
            j = 0;
        }

    }
    std::sort(temp.begin(), temp.end());
    j = 0;
    for (int i = 0; i < size_; ++i) {
        current->values[j] = temp[i];
        j++;
        if (j == Bucket::BUCKET_SIZE) {
            current = current->next;
            j = 0;
        }
    }
}

SortedUniqueVectoredList::SortedUniqueVectoredList(const SortedUniqueVectoredList &source): bucketCount_(source.bucketCount_), size_(source.size_), capacity_(source.capacity_)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    free();
    head = nullptr;
    tail = head;
    Bucket* current = nullptr;
    Bucket* otherBucket = source.head;
    Bucket* previous = current;
    size_ = source.size_;
    while (otherBucket != nullptr) {
        if (head == nullptr) {
            head = new Bucket;
            current = head;
            head->next = nullptr;
            head->previous = nullptr;
        } else {
            previous = current;
            current->next = new Bucket;
            current = current->next;
        }
        tail = current;
        current->previous = previous;
        current->values = otherBucket->values;
        current->next = nullptr;
        otherBucket = otherBucket->next;
    }
}


SortedUniqueVectoredList::SortedUniqueVectoredList(SortedUniqueVectoredList &&another)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    head = another.head;
    tail = another.tail;
    bucketCount_ = another.bucketCount_;
    size_ = another.size_;
    capacity_ = another.capacity_;
    another.head = nullptr;
    another.tail = nullptr;
    another.bucketCount_ = 0;
    another.size_ = 0;
    another.capacity_ = 0;
}

SortedUniqueVectoredList::~SortedUniqueVectoredList()
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    free();
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(SortedUniqueVectoredList &&another)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if (this != &another)
    {
        head = another.head;
        tail = another.tail;
        bucketCount_ = another.bucketCount_;
        size_ = another.size_;
        capacity_ = another.capacity_;
        another.head = nullptr;
        another.tail = nullptr;
        another.bucketCount_ = 0;
        another.size_ = 0;
        another.capacity_ = 0;
    }
    return *this;
}

void SortedUniqueVectoredList::insert(const string &value)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if(head == nullptr){
        Bucket* newBucket = new Bucket;
        head = newBucket;
         head->previous = nullptr;
         head->next = nullptr;
         tail = head;
        capacity_ += Bucket::BUCKET_SIZE;
        bucketCount_++;
    }
    bool insertion_complete = false;
    if (contains(value) == false && head!=nullptr){
        for(int i=0; i<std::size(tail->values); i++){
            if(tail->values[i].empty()){
                tail->values[i] = value;
                size_ ++;
                tail->size ++;
                insertion_complete = true;
            }
            if(insertion_complete == true){
            break;
            }
        }
        if(insertion_complete == false && head!=nullptr){
            allocate_new_bucket();
            tail->values[0] = value;
            size_ ++;
            tail->size ++;
        }
    }
    // std::sort(tail->values.begin(), tail->values.end(), compareStrings);
    sorting();

}

void SortedUniqueVectoredList::erase(const string &value)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym (opcjonalne zadanie)

}

SortedUniqueVectoredList::operator std::string() const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    std::vector<std::string> temp;
    Bucket *iteration = head;
    int j = 0;
    for (int i = 0; i < size_; ++i) {
        temp.push_back(iteration->values[j]);
        j++;
        if (j == Bucket::BUCKET_SIZE) {
            iteration = iteration->next;
            j = 0;
        }

    }
    std::string result;
    for(int i=0; i < temp.size(); i++){
        result += temp[i];
    }
    return result;
}

void SortedUniqueVectoredList::allocate_new_bucket()
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if(tail->next == nullptr){
        Bucket *allocated = new Bucket;
        allocated->previous = tail;
        allocated->next = nullptr;
        tail->next = allocated;
        tail = allocated;
        capacity_ += Bucket::BUCKET_SIZE;
        bucketCount_++;
    }




}

void SortedUniqueVectoredList::free()
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    Bucket *current;
    for(auto bucket=head; bucket!= nullptr;) {
        current = bucket;
        bucket=bucket->next;
        delete current;
    }
}


void SortedUniqueVectoredList::move(SortedUniqueVectoredList &&another)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym

}

void SortedUniqueVectoredList::copy(const SortedUniqueVectoredList &other)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowymM
}

bool SortedUniqueVectoredList::contains(const string &value) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    Bucket* current = head;
    if(head == nullptr){
        return false;
    }
    do{
        for(int i = 0; i < tail->BUCKET_SIZE; i++) {
            if (current->values[i] == value) {
                return true;
            }
        }
        current = current->next;
    }
    while(current != nullptr);
    return false;
    }


SortedUniqueVectoredList SortedUniqueVectoredList::operator-(const SortedUniqueVectoredList &another) const {
    SortedUniqueVectoredList ret;
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    Bucket *iteration = head;
    int j = 0;
    for (int i = 0; i < size_; ++i) {
        string buffer = iteration->values[j];
        if(another.contains(buffer) == false){
            ret.insert(buffer);
        }
        j++;
        if (j == Bucket::BUCKET_SIZE) {
            iteration = iteration->next;
            j = 0;
        }

    }
    return ret;
}
SortedUniqueVectoredList &SortedUniqueVectoredList::operator*=(const size_t howManyTimesMultiply)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    int j = 0;
    Bucket* iteration = head;
    for (int i = 0; i < size_; ++i) {
        std::string buffer = iteration->values[j];
        for(int k=1;k < howManyTimesMultiply; k++){
            iteration->values[j] += buffer;
        }

        j++;
        if (j == Bucket::BUCKET_SIZE) {
            iteration = iteration->next;
            j = 0;
        }

    }
    return *this;
}

string &SortedUniqueVectoredList::operator[](size_t index)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if (index >= size_)
    {
        throw std::out_of_range("");
    }
    Bucket* current = head;
    int bucket_number = index / Bucket::BUCKET_SIZE;
    int bucket_index = index % Bucket::BUCKET_SIZE;
    for(int i = 0; i<bucket_number; ++i){
        current=current->next;
    }
    return current->values[bucket_index];
}

const string& SortedUniqueVectoredList::operator[](size_t index) const
{
        /// @todo zaimplementuj, szczegoly w pliku naglowkowym!
        if (index >= size_)
        {
            throw std::out_of_range("");
        }
        Bucket* current = head;
        int bucket_number = index / Bucket::BUCKET_SIZE;
        int bucket_index = index % Bucket::BUCKET_SIZE;
        for(int i = 0; i<bucket_number; ++i){
            current=current->next;
        }
        return current->values[bucket_index];
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(const SortedUniqueVectoredList &another)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    if(this != nullptr) {
        SortedUniqueVectoredList temp(another);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
        std::swap(bucketCount_, temp.bucketCount_);
    }
    return *this;
}

