// 
// Keegan Calkins
#ifndef WORDLIST_HPP_
#define WORDLIST_HPP_

#include <iostream>
#include <string>
#include <cassert>

using std::cout; using std::endl;
using std::string; 

class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0) : word_(word), num_(num) {} // default constructor
    bool matchWord(const string&); // returns true if word matches stored
    void increment(); // increments number of occurrences 
    bool operator<(const WordOccurrence&);
    
    string getWord() const;
    int getNum() const;
private:
    string word_;
    int num_;
};

class WordList {
public:
    // add copy constructor, destructor, overloaded assignment
    WordList() { size_ = 0; wordArray_ = new WordOccurrence[size_]; } // default constructor
    WordList(const WordList&);                // copy constructor
    ~WordList() { delete[] wordArray_; }    // destructor
    WordList& operator=(WordList);          // overloaded assignment

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);
    
    void addWord(const string&);
    void print();

    // Only use for testing purposes
    WordOccurrence * getWords() const {return wordArray_;};
    int getSize() const {return size_;};
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};
#endif