// hpp for collection class
// Keegan Calkins

#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include <iostream>
#include "list.hpp"

// forward class declaration
template <typename T>
class Collection;

// forward function declaration
template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
    Collection(): head_(nullptr) {}
    void add(const T data);
    void remove(const T data);
    T last();
    friend bool equal<T>(const Collection&, const Collection&);
    void print();

private:
    node<T>* head_;
};

//
// member functions for Collection
//
template<typename T>
void Collection<T>::add(const T data) {
    node<T> *newNode = new node<T>; // creates new node pointer
    newNode->setData(data);         // sets new pointers data to input data
    newNode->setNext(head_);        // sets new pointers next as the current head
    head_ = newNode;                // sets the head value as the new node
}
template <typename T>
void Collection<T>::remove(const T data) {
    node<T> *currentPtr = head_;
    node<T> *prev = nullptr;

    while (currentPtr != nullptr) {
        if (currentPtr->getData() == data) {    // when the same as remove value
            if (prev == nullptr) {              // if the data to be removed is the head
                node<T> *temp = currentPtr;
                head_ = currentPtr->getNext();  // change head to next node when removing head
                currentPtr = currentPtr->getNext();
                delete temp;                    // deletes head node and sets temp back to nullptr
            } else {                            // when the data to remove is not the head
                node<T> *temp = currentPtr;
                prev->setNext(currentPtr->getNext());
                currentPtr = currentPtr->getNext(); // set current pointer to next value
                delete temp;
            }
        } else {                                // when the current data is not data to remove
            prev = currentPtr;
            currentPtr = currentPtr->getNext();
        }
    }
}
template<typename T>
T Collection<T>::last(){
    return head_->getData();    // use node method to get private data 
}
template<typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
    node<T> *lhsList = lhs.head_;   // create new nodes and assign lhs and rhs 
    node<T> *rhsList = rhs.head_;   // input values at the head
    while (lhsList != nullptr && rhsList != nullptr) {
        // will return false (not equal) when the data of the left list node 
        // and the right list node are not equal
        if (lhsList->getData() != rhsList->getData()) { return false; }
        lhsList = lhsList->getNext();   // traverses the lists
        rhsList = rhsList->getNext();
    }
    // return true if no two nodes satisfy not equal expression
    return true;
}
template<typename T>
void Collection<T>::print() {
    node<T> *currentPtr = head_;    // new node pointer for traversal
    // traverses list and prints the data from current pointer
    while (currentPtr != nullptr) {
        std::cout << currentPtr->getData() << std::endl;
        currentPtr = currentPtr->getNext();
    }
}

#endif // COLLECTION_HPP_