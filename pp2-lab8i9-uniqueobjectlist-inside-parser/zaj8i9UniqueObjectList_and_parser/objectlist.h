#pragma once

#include <cinttypes>  // std::size_t
#include <memory>  // std::unique_ptr (dla chętnych)
#include <set>


// #define UNIMPLEMENTED_OBJECT_LIST_CONSTRUCTOR_SIZE_EMPTY_METHODS
// #define UNIMPLEMENTED_PUSH_FRONT
// #define UNIMPLEMENTED_POP_FRONT
// #define UNIMPLEMENTED_FRONT
// #define UNIMPLEMENTED_CLEAR
//#define UNIMPLEMENTED_REVERSE // rozmowa kwalifikacyjna
//#define UNIMPLEMENTED_ITERATOR_METHODS_AT_LEAST_EMPTY
//#define UNIMPLEMENTED_ITERATORS
//#define UNIMPLEMENTED_ERASE_AFTER
//#define UNIMPLEMENTED_ERASE


class Object;


class ObjectList
{
    struct Node
    {
        Object *value_;
        Node* next_;
    };

    std::size_t size_ = 0;
    Node *head = nullptr;
public:
    using value_type = Object;
    ObjectList();
    ~ObjectList();
    ObjectList(ObjectList&& other) noexcept;
    ObjectList(const ObjectList& other);
    ObjectList& operator=(ObjectList&& other) noexcept;
    ObjectList& operator=(const ObjectList& other);
    std::size_t size() const;

    bool empty();

    void clear();


    void reverse() noexcept;

    value_type& front();


    struct iterator{
        Node* current;
        iterator(Node *node): current(node){};
        Object& operator*() const{
            return *(current->value_);
        }

        iterator operator++(){
            if (current!= nullptr){
                current = current->next_;
            }
            return *this;
        }

        bool operator==(const iterator& other) const{
            return current == other.current;
        }

        bool operator!=(const iterator& other) const{
            return current != other.current;
        }

    };

    iterator begin();
    iterator end();

    /**
     * @brief push_front
     * @param newObject
     * Wpierw sprawdzamy czy obiekt już jest w liście
     */
    void push_front(value_type* newObject);

    void pop_front();

    void erase_after(iterator position);

    /// tego std::forward_list nie ma
    void erase(iterator position);

    /// dla chętnych, tego testy nie sprawdzają:
    ObjectList reverse_copy() const;

    /// dla chętnych, tego testy nie sprawdzają:
    void sort() noexcept;

protected:
    // TODO:
};
