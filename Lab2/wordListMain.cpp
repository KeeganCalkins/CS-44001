//
// Keegan Calkins

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "WordList.hpp"

using std::cout; 
using std::string;
using std::ifstream; 

int main(int argc, char *argv[]) {
    if (argc != 2) { cout << "Include one text file\n"; return 0; }

    string fileName = argv[1];
    ifstream fileIn(fileName);

    WordList list;
    char c;
    string word = "";
    bool flag = false;  // flag for when current word is being read


    while (fileIn.get(c)) {
        if (isalnum(c)) {   // if character is alphanumeric,
            word += c;      // add char to word 
            flag = true;    // and set flag true
        } else if (flag) {      // if not alphanumeric and flag is true,
            list.addWord(word); // word is over and we add the word to the list
            flag = false;
            word = "";
        }
    }
    if (!word.empty()) {
        list.addWord(word);
    }

    list.print();
    fileIn.close();

    return 0;
}