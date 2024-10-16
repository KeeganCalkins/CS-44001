// Keegan Calkins

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


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

  // outputs the student's info
  void printOut() const {
    cout << firstName_ << " " << lastName_ << ": ";
    for (auto& courses : courseList_) { // adds each course string from list to student's string
      cout << courses << " ";
    }
    cout << endl;
  }

  // used to assign to a student list
  void setCourseList(list<string> courseList) {
    courseList_ = courseList;
  }

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
  list<string> courseList_;
};

// get the string list for the courses of a student
list<string> getCourseList(Student, vector <list<Student>>);
// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){
  
  if (argc <= 1){ cout << "usage: " << argv[0] 
    << " list of courses, dropouts last" << endl; exit(1);}

  // vector of courses of students
  vector <list<Student>> courseStudents; 

  for(int i=1; i < argc-1; ++i){
    list<Student> roster;
    readRoster(roster, argv[i]);  
    cout << "\n\n" << argv[i] << "\n";  
    // printRoster(roster);
    courseStudents.push_back(move(roster)); 
  }


  // reading in dropouts
  list<Student> dropouts; 
  readRoster(dropouts, argv[argc-1]); 
  // cout << "\n\n dropouts \n"; printRoster(dropouts);

  list<Student> allStudents;  // master list of students
 
  for(auto lst : courseStudents) {
    allStudents.splice(allStudents.end(), lst);
  }
  cout << "\n\n all students unsorted \n"; 
  // printRoster(allStudents);

  allStudents.sort(); // sorting master list
  // cout << "\n\n all students sorted \n"; printRoster(allStudents);

  allStudents.unique(); // eliminating duplicates
  // cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
  
  for (const auto& str : dropouts)  // removing individual dropouts
    allStudents.remove(str);
  cout << "\n\n all students, dropouts removed \n"; 
  for (auto& student : allStudents) {
    list<string> courseList = getCourseList(student, courseStudents);
    student.setCourseList(courseList);
  }
  printRoster(allStudents);
}

list<string> getCourseList(Student student, vector <list<Student>> courseStudents) {
  list<string> courseList;
  for(auto i = 0; i < courseStudents.size(); ++i) {         // traverse each list of each student
    list<Student> studentList = courseStudents[i];
    if (std::find(studentList.begin(),                      // check if student is in current course to assign
	      studentList.end(), student) != studentList.end()) {
      courseList.push_back("cs" + std::to_string(i + 1));   // if student is found push current course the list
    }
  }
  return courseList;
}

void readRoster(list<Student>& roster, string fileName){
  ifstream course(fileName);
  string first, last;
  while(course >> first >> last)             // read first and last name
    roster.push_back(Student(first, last));  // push each student to the roster
  course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
  cout << "\nall students, dropouts removed and sorted"
       << "\nfirst name last name: courses enrolled\n";
  for(const auto& student : roster) {
    student.printOut();
  }
}