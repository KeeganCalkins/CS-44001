// Keegan Calkins

#include <fstream>
#include <iostream>
#include <set>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::set;
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
void readRoster(set<Student>& courseStudentsSet, string fileName);  
// printing a list out
void printRoster(const set<Student>& roster); 
// removes students from set if in dropout list
void removeDropouts(set<Student>& courseStudentsSet, const set<Student>& dropouts);

int main(int argc, char* argv[]) {
  
    if (argc <= 1){ cout << "usage: " << argv[0] 
        << " list of courses, dropouts last" << endl; exit(1);}

    // vector of courses of students
    set<Student> courseStudentsSet;
    set<Student> dropouts;
    for(int i=1; i < argc-1; ++i){
        readRoster(courseStudentsSet, argv[i]); 
    }

    readRoster(dropouts, argv[argc-1]);
    removeDropouts(courseStudentsSet, dropouts);

    printRoster(courseStudentsSet);
}

void readRoster(set<Student>& courseStudentsSet, string fileName){
    ifstream course(fileName);
    string first, last;

    while(course >> first >> last) {            // read first and last name
        /*Student addedStudent(first, last);
        bool flag = true;                       // used to check if student is already in set 
        for (auto& student : courseStudentsSet) {
            if (addedStudent == student) {
                flag = false;
                break;
            }
        }
        // will only insert student if they are not a duplicate
        if (flag) {courseStudentsSet.insert(addedStudent);}*/
        courseStudentsSet.insert(Student(first, last));
    }
    course.close();
}

// printing a list out
void printRoster(const set<Student>& roster){
    cout << "\nCurrently Enrolled Students\n";
    // outputs return value from first being key, and
    // second being student courses string
    for(const auto student : roster) {
        cout << student.print() << endl;
    }
}

void removeDropouts(set<Student>& courseStudentsSet, const set<Student>& dropouts) {
    string first, last;
    for (const auto dropout : dropouts) {               // traverses set of dropouts
        for (const auto student : courseStudentsSet) {  // traverses set of all students
            if (dropout == student) {
                courseStudentsSet.erase(student);       // removes dropout from all students when found
                break;
            }
        }
    }
}