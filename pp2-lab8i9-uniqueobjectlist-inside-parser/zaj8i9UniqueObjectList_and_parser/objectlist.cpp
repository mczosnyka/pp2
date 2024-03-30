#include <memory>
#include <stdexcept>
#include <utility>  // std::exchange()
#include "objectlist.h"
#include "object.h"



ObjectList::ObjectList(){
    head = new Node;
    head->value_ = nullptr;
    head->next_ = nullptr;
}
ObjectList::~ObjectList() = default;

ObjectList::ObjectList(const ObjectList& other){
    head = nullptr;
    Node* current = nullptr;
    Node* otherNode = other.head;
    size_ = other.size_;
    while (otherNode != nullptr) {
        if (head == nullptr) {
            head = new Node;
            current = head;
        } else {
            current->next_ = new Node;
            current = current->next_;
        }
        current->value_ = otherNode->value_;
        current->next_ = nullptr;
        otherNode = otherNode->next_;
    }
}


ObjectList::ObjectList(ObjectList&& other) noexcept : size_(std::exchange(other.size_, 0)), head(std::exchange(other.head, nullptr)){
}


ObjectList& ObjectList::operator=(ObjectList&& other) noexcept {
    if (this != &other) {
        clear();
        size_ = std::exchange(other.size_, 0);
        head = std::exchange(other.head, nullptr);
    }

    return *this;
}

ObjectList& ObjectList::operator=(const ObjectList& other) {
    if (this != &other) {
        clear();

        head = nullptr;
        Node* current = nullptr;
        Node* otherNode = other.head;
        size_ = other.size_;
        while (otherNode != nullptr) {
            if (head == nullptr) {
                head = new Node;
                current = head;
            } else {
                current->next_ = new Node;
                current = current->next_;
            }
            current->value_ = otherNode->value_;
            current->next_ = nullptr;
            otherNode = otherNode->next_;
        }

    }
    return *this;
}


std::size_t ObjectList::size() const{
    return size_;
}



bool ObjectList::empty(){
    if(size_ == 0){
        return true;
    }
    else{
        return false;
    }
}


void ObjectList::push_front(value_type* newObject){
    bool no_duplicates = true;
    if(empty()){
        head->value_ = newObject;
        head->next_ = nullptr;
        size_++;
    }
    else{
        Node* current = head;
        for(int i=0; i<size_; i++){
            if(*(current->value_) == *(newObject)){
                no_duplicates = false;
                break;
            }
            current = current->next_;
        }
        if(no_duplicates){
            Node *new_element = new Node;
            new_element->value_ = newObject;
            new_element->next_ = head;
            head = new_element;
            size_++;
        }

    }

}

void ObjectList::pop_front() {
    Node* buffer = head->next_ ;
    delete head;
    head = buffer;
    size_ --;
};

ObjectList::value_type& ObjectList::front(){
    return *head->value_;
}




ObjectList::iterator ObjectList::begin(){
    return iterator(head);
}
ObjectList::iterator ObjectList::end(){
    return iterator(nullptr);
}

void ObjectList::clear(){
    while(size_ > 0){
        Node* current = head;
        head = head->next_;
        delete current;
        size_ --;
    }
}

void ObjectList::reverse() noexcept {
    if (!empty()) {
        Node *previous = nullptr;
        Node *current = head;
        Node *next = nullptr;
        while (current != nullptr) {
            next = current->next_;
            current->next_ = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }
}

void ObjectList::erase_after(iterator position){
    if(!(position.current == nullptr || position.current->next_ == nullptr)){
        Node* removed = position.current->next_;
        position.current->next_ = position.current->next_->next_;
        delete removed;
        size_--;
    }
}






void ObjectList::erase(iterator position){
    if(position.current != nullptr){
        if(position.current == head){
            pop_front();
        }
        else{
        Node* previousNode = head;
        while (previousNode->next_ != position.current)
        {
            previousNode = previousNode->next_;
        }
        Node* removed = position.current;
        previousNode->next_ = position.current->next_;
        delete removed;
        size_--;
        position.current = previousNode->next_;
    }
    }
}