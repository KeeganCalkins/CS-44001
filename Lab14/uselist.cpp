// Keegan Calkins

#include <iostream>
#include "list.hpp" // list template

using std::cout; using std::endl;

int main(){
   // 
   // integer list manipulation
   // 

   // first node
    shared_ptr<node<int>> head = make_shared<node<int>>();
    head->setData(1);


    shared_ptr<node<int>> currentPtr = make_shared<node<int>>();  // second node
    currentPtr->setData(2);

    head->setNext(currentPtr); // list contains two nodes

    cout << head->getData() << " "; // printing head node

   // deallocating head node
    currentPtr=head;
    head=head->getNext();

   // printing and deallocating the last element
    cout << head->getData() << endl;


   // 
   // character list manipulation
   // 
   
   // allocating head node
    shared_ptr<node<char>> charHead = make_shared<node<char>>();
    shared_ptr<node<char>> current = charHead;
    current->setData('A');

   // creating list
    for(char letter = 'B'; letter <= 'Z'; ++letter){
        shared_ptr<node<char>> const newNode = make_shared<node<char>>();
        newNode->setData(letter);
        current->setNext(newNode);
        current = newNode;
    }


    for(current = charHead;  current != nullptr; current=current->getNext())
        cout << current->getData() << ' ';
    cout << endl;
}