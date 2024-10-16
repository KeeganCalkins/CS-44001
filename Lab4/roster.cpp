// Keegan Calkins

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <iterator>
#include <algorithm>


using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector<list<string>>& roster, const string& fileName);  

// printing a list out
void printRoster(const vector<list<string>>& roster); 

// Custom comparator for lists of strings
bool compareList(const list<string>& lhs, const list<string>& rhs);

// Function to sort a vector of lists
void sortRoster(vector<list<string>>& roster);

int main(int argc, char* argv[]) {

    if (argc <= 1){ 
        cout << "usage: " << argv[0] 
        << " list of courses, dropouts last" 
        << endl; exit(1);
    }

    vector<list<string>> courseRoster, dropouts;
    for(int i=1; i < argc - 1; ++i) {   // reads all course txt files
        readRoster(courseRoster, argv[i]);  
    }
    readRoster(dropouts, argv[argc-1]); // reads dropout's txt file
    
    int i = 0;
    for (auto it = courseRoster.begin(); it != courseRoster.end(); ++it, ++i) {
        for (auto id = dropouts.begin(); id != dropouts.end(); ++id) {
            if (it->front() == id->front()) {   // if the names match, erase from course roster
                courseRoster.erase(courseRoster.begin() + i);
                break;  
            }
        }
    }
    sortRoster(courseRoster);
    printRoster(courseRoster);
}

// reading in a file of names into a list of strings
void readRoster(vector<list<string>>& roster, const string& fileName){
    ifstream course(fileName);
    string first, last;
    string courseName = fileName;
    bool flag = false;
    courseName = courseName.substr(0, courseName.size() - 4);    // take file name - .txt for coursename
    while(course >> first >> last){                              // read first and last name from students in file 
        string str= first + ' ' + last + ':';
        flag = true;
        for(auto& list : roster){
            if (list.front() == str) {                                // if a student already exists in 
                list.push_back(courseName);                           // roster it adds current courses
                flag = false;
                break;
            }
        }
        if (flag) {
            list<string> newStudent;                              // if no matching student is found it creates 
            newStudent.push_back(str);                            // a new student and adds it to roster
            newStudent.push_back(courseName);
            roster.push_back(newStudent);
        }
    }
    course.close();
}

// compare method for lists of strings
bool compareList(const list<string>& lhs, const list<string>& rhs) {
    return lhs < rhs;
}

// Function to sort a vector of lists
void sortRoster(vector<list<string>>& roster) {
    std::sort(roster.begin(), roster.end(), compareList);
}

// printing vector of string list
void printRoster(const vector<list<string>>& roster){
    cout << "\nall students, dropouts removed and sorted"
         << "\nfirst name last name: courses enrolled\n";
    for(auto it = roster.begin(); it != roster.end(); ++it) {   // iterate through entire roster
        for(auto& str : *it) { cout << str << " "; }            // dereference and print out first and last names
        cout << endl;
    }
    cout << endl;
}