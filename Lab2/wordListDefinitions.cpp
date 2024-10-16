// 
// Keegan Calkins

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include "WordList.hpp" // class definitions

using std::cout; using std::endl;
using std::string; 

// WordOccurrence Class Definitions
bool WordOccurrence::matchWord(const string& word) {   // returns true if word matches stored
    return word_ == word;
}
// increments number of occurrences
void WordOccurrence::increment() { ++num_; } 
// will prioritize sorting by occurrence, then alphabetically 
bool WordOccurrence::operator<(const WordOccurrence& rhs) {
    if (num_ == rhs.num_) {         // if the same occurence then alphabet
        return word_ < rhs.word_;
    }                               // else sort by occurrence
    return num_ < rhs.num_;
}
string WordOccurrence::getWord() const{ return word_; }    // returns word_
int WordOccurrence::getNum() const{ return num_; }  // returns num_


// WordList Class Definitions
WordList::WordList(const WordList& copy) {    // copy constructor
    size_ = copy.size_;
    wordArray_ = new WordOccurrence[size_];
    for (int i = 0; i < size_; ++i) {
        wordArray_[i] = copy.wordArray_[i];
    }
}
WordList& WordList::operator=(WordList rhs) {    // overloaded assignment operator
    size_ = rhs.size_;
    wordArray_ = new WordOccurrence[size_];

    for (int i = 0; i < size_; ++i){
        wordArray_[i] = rhs.wordArray_[i];
    }
    return *this;
}
bool equal(const WordList& lhs, const WordList& rhs) {  // checks if lhs is equal to rhs
    if (lhs.size_ != rhs.size_) { return false; }   // checks size, if diff return false
    for (int i = 0; i < lhs.size_; ++i) {
        // if either the num of occurrence or word itself is different, return false
        if (lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum() || 
            lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord()) {
            return false;
        }
    }
    return true;    // else
}
void WordList::addWord(const string& word) {    // adds word to list
    for (int i = 0; i < size_; ++i) {
        if (wordArray_[i].matchWord(word)) {    // if already in list, increment that word
            wordArray_[i].increment();
            return;
        }
    }

    WordOccurrence* tempArr = wordArray_;  // need to create tempArr of size+1
    wordArray_ = new WordOccurrence[size_ + 1];
    for (int i = 0; i < size_; ++i) {   // copies original wordArray to tempArr
        wordArray_[i] = tempArr[i];
    }
    wordArray_[size_] = word;
    wordArray_[size_].increment();
    size_++;                            // add new word to end of tempArr
}
void WordList::print() {
    std::sort(wordArray_, wordArray_ + size_);   // algorithm to sort the wordArray from beginning to end
    // print as given solution format
    for (int i = 0; i < size_ - 1; ++i) {
        cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() << endl;
    }
    cout << wordArray_[size_ - 1].getWord() << " " << wordArray_[size_ - 1].getNum();
}