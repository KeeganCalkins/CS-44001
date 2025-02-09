// Keegan Calkins

#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

using std::shared_ptr; using std::weak_ptr; using std::make_shared;


// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:

    node(): next_(nullptr), prev_(nullptr) {}

    // functions can be inlined
    T getData() const {return data_;}
    void setData(const T& data){data_=data;}

    // or can be defined outside
    shared_ptr<node<T>> getNext() const;
    void setNext(shared_ptr<node<T>> const);
    shared_ptr<node<T>> getPrev() const;
    void setPrev(shared_ptr<node<T>> const);

private:
    T data_;
    shared_ptr<node<T>> next_;
    shared_ptr<node<T>> prev_;
};

//
// member functions for node
//
template <typename T>
shared_ptr<node<T>> node<T>::getNext() const {
    return next_;
}

template<typename T>
void node<T>::setNext(shared_ptr<node<T>> const next){
    next_=next;
}

template <typename T>
shared_ptr<node<T>> node<T>::getPrev() const {
    return prev_;
}

template<typename T>
void node<T>::setPrev(shared_ptr<node<T>> const prev){
    prev_=prev;
}

#endif // LIST_HPP_