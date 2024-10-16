// Keegan Calkins

#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list;
using std::cout; using std::endl;
using std::move; using std::map;


class Student{
public:
  Student(string firstName, string lastName): 
    firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
  Student(Student && org) noexcept:
    firstName_(move(org.firstName_)),
    lastName_(move(org.lastName_))
  {}
  
   // force generation of default copy constructor
  Student(const Student & org) = default;
  
  string print() const {return firstName_ + ' ' + lastName_;}

  // needed for unique() and for remove()
  friend bool operator== (Student left, Student right){
    return  left.lastName_ == right.lastName_ &&
	          left.firstName_ == right.firstName_;
  }

   // needed for sort()
  friend bool operator< (Student left, Student right){
    return left.lastName_ < right.lastName_ ||
	    (left.lastName_ == right.lastName_ && 
	     left.firstName_ < right.firstName_);
  }
private:
  string firstName_;
  string lastName_;
};

// reading a list from a fileName
void readRoster(map<Student, list<string>>& courseStudentsMap, string fileName);  
// printing a list out
void printRoster(const map<Student, list<string>>& roster); 
// removes student from specific filename
void removeStudent(map<Student, list<string>>& courseStudentsMap, string file);

int main(int argc, char* argv[]){
  
  if (argc <= 1){ cout << "usage: " << argv[0] 
    << " list of courses, dropouts last" << endl; exit(1);}

  // vector of courses of students
  map<Student, list<string>> courseStudentsMap; 

  for(int i=1; i < argc-1; ++i) {
    readRoster(courseStudentsMap, argv[i]);
  }
  removeStudent(courseStudentsMap, argv[argc-1]); 
  // cout << "\n\n dropouts \n"; printRoster(dropouts);
  
  printRoster(courseStudentsMap);
}

void readRoster(map<Student, list<string>>& courseStudentsMap, string fileName){
  ifstream course(fileName);
  string first, last;
  while(course >> first >> last) {             // read first and last name
    string courseName = fileName.substr(0, fileName.length() - 4);
    // will construct new student object as new key if is a new student
    // in both cases the current course is pushed on string list for the key
    courseStudentsMap[Student(first, last)].push_back(courseName);
  }
  course.close();
}

// printing a list out
void printRoster(const map<Student, list<string>>& roster){
  cout << "\nall students, dropouts removed and sorted"
       << "\nfirst name last name: courses enrolled\n";
  // outputs return value from first being key, and 
  // second being student courses string
  for(auto it = roster.begin(); it != roster.end(); ++it) {
    cout << it->first.print() << ": ";
    for (auto course : it->second) {
      cout << course << " ";
    }
    cout << endl;
  }
}
void removeStudent(map<Student, list<string>>& courseStudentsMap, string fileName) {
    ifstream course(fileName);
    string first, last;
    while(course >> first >> last) {             // read first and last name
        // erase pair from map when in the specified roster
        courseStudentsMap.erase(Student(first, last));
    }
    course.close();
}