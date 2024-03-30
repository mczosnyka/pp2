#include <iostream>
#include <algorithm> // std::sort, std::find, std::copy
#include <iterator> // std::distance, std::advance, std::back_inserter
#include <limits>   // std::numeric_limits<size_t>::max()
#include <numeric>  // std::accumulate()

using namespace std;

#include "containerWrapper.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
using namespace std;

IContainerWrapper::~IContainerWrapper() = default;

VectorWrapper::VectorWrapper(const value_type elements[], std::size_t size): impl_(elements, elements+size){}

void VectorWrapper::push_back(const value_type& element) {
    impl_.push_back(element);
};
void VectorWrapper::push_front(const value_type& element) {
    impl_.insert(impl_.begin(), element);
};


void VectorWrapper::insert(const value_type& element, std::size_t position){
    impl_.insert((impl_.begin()+position), element);
}

size_t VectorWrapper::size() const{
    return impl_.size();
}

VectorWrapper::value_type& VectorWrapper::at(std::size_t position){
    return impl_.at(position);
}

void VectorWrapper::sort(){
    std::sort(impl_.begin(), impl_.end());
}

void VectorWrapper::erase(std::size_t position) {
    impl_.erase(impl_.begin()+position);
}

VectorWrapper::value_type VectorWrapper::count() const {
    value_type counter = 0;
    for(int i = 0; i<impl_.size(); i++){
        counter+=impl_[i];
    }
    return counter;
}



std::size_t VectorWrapper::find(const value_type& needle) const {
    auto result = std::find(impl_.begin(), impl_.end(), needle);
    if (result != impl_.end()){
        return (result-impl_.begin());
    }
    else{
        return SIZE_MAX;
    }

}


VectorWrapper::value_type VectorWrapper::pop_front(){
    value_type first_element = impl_.front();
    impl_.erase(impl_.begin());
    return first_element;
}
VectorWrapper::value_type VectorWrapper::pop_back() {
    value_type last_element = impl_.back();
    impl_.pop_back();
    return last_element;
}


