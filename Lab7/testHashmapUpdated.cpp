// hashmap test file
// Mikhail Nesterenko,  Tsung-Heng Wu
// 3/6/2024

#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <cassert>

using std::string;

int main() {

   //
   // <int, int> hashmap test
   //
   hashmap<int, int> myHash;
   
   // test inserts
   pair<const pair<const int, int>*, bool> result;

   result = myHash.insert(make_pair(4, 40));
   //std::cout << result.second << ", " << result.first->first << ", " << result.first->second << "\n";
   assert(result.second);
   assert(result.first->first == 4);
   assert(result.first->second == 40);

   result = myHash.insert(make_pair(105, 1050));
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.insert(make_pair(6, 60));
   assert(result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);

   result = myHash.insert(make_pair(107, 1070));
   assert(result.second);
   assert(result.first->first == 107);
   assert(result.first->second == 1070);

   result = myHash.insert(make_pair(90, 900));
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.insert(make_pair(95, 950));
   assert(result.second);
   assert(result.first->first == 95);
   assert(result.first->second == 950);

   result = myHash.insert(make_pair(6, 70)); // insert with a duplicate key
   assert(!result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);


   // searching map
   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   assert(x != nullptr);
   assert(x->second == 40);

   x = myHash.find(5);
   assert(x == nullptr);


   // test deletes
   result = myHash.erase(4); // delete with next element in same bucket
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.erase(107); // delete the last element in a bucket
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(6);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(105);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(95); // erase the last element in the container
   assert(result.second);
   assert(result.first== nullptr);

   result = myHash.erase(90); // erased all elements in container
   assert(result.second);
   assert(result.first == nullptr);

   result = myHash.erase(5); // erase key not in container
   assert(!result.second);
   // first is unspecified


   //
   // <integer, string> hashmap test
   //
   hashmap<int, string> employees;
   

   // add tests for insert using the <integer, string> hashmap

   auto str_result = employees.insert(make_pair(101, "John"));
   assert(str_result.second);
   assert(str_result.first->first == 101);
   assert(str_result.first->second == "John");

   str_result = employees.insert(make_pair(102, "Bob"));
   assert(str_result.second);
   assert(str_result.first->first == 102);
   assert(str_result.first->second == "Bob");

   // duplicate
   str_result = employees.insert(make_pair(102, "Jordan"));
   assert(!str_result.second);
   assert(str_result.first->first == 102);
   assert(str_result.first->second == "Bob");

   str_result = employees.insert(make_pair(103, "Joe"));
   assert(str_result.second);
   assert(str_result.first->first == 103);
   assert(str_result.first->second == "Joe");

   // add tests for find using the <integer, string> hashmap

   auto emp = employees.find(101);
   assert(emp != nullptr);
   assert(emp->second == "John");

   emp = employees.find(105);
   assert(emp == nullptr);

   // add tests for erase using the <integer, string> hashmap

   str_result = employees.erase(101);
   assert(str_result.second);
   assert(str_result.first->first == 102);
   assert(str_result.first->second == "Bob");

   str_result = employees.erase(102);
   assert(str_result.second);
   assert(str_result.first->first == 103);
   assert(str_result.first->second == "Joe");

   // add tests for [] operator using the <integer, string> hashmap

   assert(employees[104] == "");
   employees[104] = "Keegan";
   assert(employees[104] == "Keegan");

   // add tests for rehash

   employees.rehash(50);

   assert(employees[103] == "Joe");

   assert(employees[104] == "Keegan");


   // check the hashmap is still correct and all operations still work after rehash

   str_result = employees.insert(make_pair(101, "Bob"));
   assert(str_result.second);
   assert(str_result.first->first == 101);
   assert(str_result.first->second == "Bob");

   employees[102] = "John";
   assert(employees[102] == "John");

   str_result = employees.erase(101);
   assert(str_result.second);
   assert(str_result.first->first == 102);
   assert(str_result.first->second == "John");

   str_result = employees.erase(103);
   assert(str_result.second);
   assert(str_result.first->first == 104);
   assert(str_result.first->second == "Keegan");

   std::cout << "Tests passed" << std::endl;
}